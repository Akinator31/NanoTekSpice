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
    FourAndGates::FourAndGates()
    {
        this->_andGates[3] = AndGate();
        this->_andGates[6] = AndGate();
        this->_andGates[10] = AndGate();
        this->_andGates[13] = AndGate();
    }

    std::function<Tristate (IComponent *, size_t)> FourAndGates::createFunc(size_t pin)
    {
        if (pin == 1 || pin == 6 || pin == 9 || pin == 12)
        {
            return [realPin = 2, this, pin](IComponent *component, const size_t otherPin)
            {
                const auto comp = this->_andGates.lower_bound(static_cast<int>(pin));

                if (comp != this->_andGates.end() && component)
                {
                    comp->second.setLink(realPin, *component, otherPin);
                    return Undefined;
                }
                if (comp != this->_andGates.end() && !component) {
                    return comp->second.compute(realPin);
                }
                throw NanoTekSpiceException(SyntaxFileException);
            };
        }

        if (pin == 2 || pin == 5 || pin == 8 || pin == 13)
        {
            return [realPin = 1, this, pin](IComponent *component, const size_t otherPin)
            {
                const auto comp = this->_andGates.lower_bound(static_cast<int>(pin));

                if (comp != this->_andGates.end() && component)
                {
                    comp->second.setLink(realPin, *component, otherPin);
                    return Undefined;
                }
                if (comp != this->_andGates.end() && !component) {
                    return comp->second.compute(realPin);
                }
                throw NanoTekSpiceException(SyntaxFileException);
            };
        }

        if (pin == 3 || pin == 4 || pin == 10 || pin == 11)
        {
            return [realPin = 3, this, pin](IComponent *component, const size_t otherPin)
            {
                const auto comp = this->_andGates.lower_bound(static_cast<int>(pin));

                if (comp != this->_andGates.end() && component)
                {
                    comp->second.setLink(realPin, *component, otherPin);
                    return Undefined;
                }
                if (comp != this->_andGates.end() && !component) {
                    return comp->second.compute(realPin);
                }
                throw NanoTekSpiceException(SyntaxFileException);
            };
        }
        throw NanoTekSpiceException(SyntaxFileException);
    }

    Tristate FourAndGates::compute(std::size_t pin)
    {
        return this->createFunc(pin)(nullptr, 0);
    }

    void FourAndGates::setLink(std::size_t pin, IComponent& other, std::size_t otherPin)
    {
        this->createFunc(pin)(&other, otherPin);
    }

    void FourAndGates::simulate([[maybe_unused]] std::size_t tick)
    {
    }
}
