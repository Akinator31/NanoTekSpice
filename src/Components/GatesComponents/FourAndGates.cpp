//
// Created by pavel on 10/02/2026.
//

#include "FourAndGates.h++"

#include <iostream>
#include <ostream>

#include "Errors/NanoTekSpiceErrors.h++"
#include "Factory/Factory.h++"

namespace nts
{
    std::function<Tristate (IComponent*, size_t)> FourAndGates::createFunc(size_t pin) const
    {
        return [this, pin](IComponent* component, const size_t otherPin)
        {
            size_t realPin = 0;
            int gateIndex = 0;

            if (pin == 1 || pin == 2 || pin == 3)
            {
                gateIndex = 0;
                realPin = (pin == 3) ? 3 : pin;
            }
            else if (pin == 4 || pin == 5 || pin == 6)
            {
                gateIndex = 1;
                realPin = (pin == 4) ? 3 : (pin == 5) ? 1 : 2;
            }
            else if (pin == 8 || pin == 9 || pin == 10)
            {
                gateIndex = 2;
                realPin = (pin == 10) ? 3 : (pin == 8) ? 1 : 2;
            }
            else if (pin == 11 || pin == 12 || pin == 13)
            {
                gateIndex = 3;
                realPin = (pin == 11) ? 3 : (pin == 13) ? 1 : 2;
            }
            else
                throw NanoTekSpiceException(SyntaxFileException);

            if (component)
            {
                this->_andGates[gateIndex]->setLink(realPin, *component, otherPin);
                return Undefined;
            }
            return this->_andGates[gateIndex]->compute(realPin);
        };
    }

    FourAndGates::FourAndGates()
    {
        for (size_t i = 0; i < 4; i++)
        {
            Factory factory;

            this->_andGates.push_back(factory.createComponent("and"));
        }
    }

    Tristate FourAndGates::compute(const std::size_t pin)
    {
        return this->createFunc(pin)(nullptr, 0);
    }

    void FourAndGates::setLink(const std::size_t pin, IComponent& other, const std::size_t otherPin)
    {
        this->createFunc(pin)(&other, otherPin);
    }

    void FourAndGates::simulate(const std::size_t tick)
    {
        for (const auto& gate : this->_andGates)
        {
            gate->simulate(tick);
        }
    }
}
