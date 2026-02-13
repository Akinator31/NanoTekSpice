//
// Created by pavel on 10/02/2026.
//

#include "GenericGatesComponents.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "Factory/Factory.h++"

namespace nts
{
    GenericGatesComponents::GenericGatesComponents(size_t _numberOfPins, const std::string& type, const size_t count,
                                                   const std::map<int, ComponentMapping>& mapping) :
        AComponent(_numberOfPins, Other)
    {
        Factory factory;

        for (size_t i = 0; i < count; i++)
        {
            this->_gates.push_back(factory.createComponent(type));
        }
        this->_mapping = mapping;
    }

    std::function<Tristate(IComponent*, size_t)> GenericGatesComponents::createFunc(size_t pin)
    {
        return [this, pin](IComponent* component, const size_t otherPin)
        {
            const auto info = this->_mapping.find(static_cast<int>(pin));
            if (info == this->_mapping.end())
                throw NanoTekSpiceException(SyntaxFileException);

            const int gateIndex = info->second.gateIndex;
            const int internalPin = info->second.internalPin;

            if (component)
            {
                this->_gates[gateIndex]->setLink(internalPin, *component, otherPin);

                if (dynamic_cast<class True*>(component) || dynamic_cast<class False*>(component))
                    this->compute(internalPin);
                return Undefined;
            }
            return this->_gates[gateIndex]->compute(internalPin);
        };
    }

    Tristate GenericGatesComponents::compute(const std::size_t pin)
    {
        return this->createFunc(pin)(nullptr, 0);
    }

    void GenericGatesComponents::setLink(const std::size_t pin, IComponent& other, const std::size_t otherPin)
    {
        this->createFunc(pin)(&other, otherPin);
    }

    void GenericGatesComponents::simulate(const std::size_t tick)
    {
        for (const auto& gate : this->_gates)
        {
            gate->simulate(tick);
        }
    }
}
