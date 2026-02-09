//
// Created by Noah on 09/02/2026.
//

#include "IComponent.h++"
#include "OrGate.h++"

namespace nts {
    void OrGate::simulate(const size_t tick) {
        this->_lastSimulatedTick = tick;
    }

    Tristate OrGate::compute([[maybe_unused]] size_t pin) {
        if (this->_lastComputedTick == this->_lastSimulatedTick)
            return this->_prevValue;

        if (pin == 3) {
            const Tristate value1 = this->_input[1].component->compute(this->_input[1].pin);
            const Tristate value2 = this->_input[2].component->compute(this->_input[2].pin);

            this->_prevValue = computeOrOperation(value1, value2);

            this->_lastComputedTick = this->_lastSimulatedTick;
            return this->_prevValue;
        }
        return Undefined;
    }

    void OrGate::setLink(const size_t pin, IComponent& other, size_t otherPin) {
        this->_input[pin].component = &other;
        this->_input[pin].pin = otherPin;
    }

    Tristate OrGate::computeOrOperation(const Tristate first, const Tristate second) {
        if (first == False && second == False)
            return False;
        if (first == Undefined && second == Undefined)
            return Undefined;
        return True;
    }
}
