//
// Created by pavel on 07/02/2026.
//

#include "AndGate.h++"

#include <iostream>

namespace nts
{
    void AndGate::simulate(const size_t tick)
    {
        this->_lastSimulatedTick = tick;
    }

    Tristate AndGate::compute([[maybe_unused]] size_t pin)
    {
        if (this->_lastComputedTick == this->_lastSimulatedTick)
            return this->_prevValue;

        if (pin == 3)
        {
            const Tristate value1 = this->_input[1].component->compute(this->_input[1].pin);
            const Tristate value2 = this->_input[2].component->compute(this->_input[2].pin);

            this->_prevValue = computeAndOperation(value1, value2);

            this->_lastComputedTick = this->_lastSimulatedTick;
            return this->_prevValue;
        }
        return Undefined;
    }

    void AndGate::setLink(const size_t pin, IComponent& other, const size_t otherPin)
    {
        if (pin == 1 || pin == 2 || pin == 3)
        {
            this->_input[pin].component = &other;
            this->_input[pin].pin = otherPin;
        }
    }

    Tristate AndGate::computeAndOperation(const Tristate first, const Tristate second)
    {
        if (first == true && second == true)
            return True;
        if (first == Undefined && second == Undefined)
            return Undefined;
        if (first == true || second == true)
        {
            if (first == Undefined || second == Undefined)
            {
                return Undefined;
            }
            return False;
        }
        return False;
    }
}

