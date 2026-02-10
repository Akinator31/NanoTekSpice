//
// Created by Noah on 09/02/2026.
//

#include "NotGate.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"

namespace nts {
    void NotGate::simulate(const size_t tick) {
        this->_lastSimulatedTick = tick;
    }

    Tristate NotGate::compute([[maybe_unused]] size_t pin) {
        if (this->_lastComputedTick == this->_lastSimulatedTick)
            return this->_prevValue;

        if (pin == 2) {
            const Tristate value = this->_input[1].component->compute(this->_input[1].pin);

            this->_prevValue = computeNotOperation(value);

            this->_lastComputedTick = this->_lastSimulatedTick;
            return this->_prevValue;
        }
        return Undefined;
    }

    void NotGate::setLink(const size_t pin, IComponent& other, size_t otherPin) {
        if (pin != 1 && pin != 2)
            throw NanoTekSpiceException(SyntaxFileException);
        this->_input[pin].component = &other;
        this->_input[pin].pin = otherPin;
    }

    Tristate NotGate::computeNotOperation(const Tristate value) {
        if (value == Undefined)
            return Undefined;
        if (value == True)
            return False;
        return True;
    }
}
