//
// Created by pavel on 09/02/2026.
//

#include "Clock.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "Utils/Utils.h++"

namespace nts {
    Clock::Clock() : AComponent(1, ClockComponent) {}

    void Clock::setValue(const Tristate value) {
        this->_nextState = value;
    }

    void Clock::simulate([[maybe_unused]] size_t tick) {
        this->_currentState = this->_nextState;
        this->_nextState = !this->_currentState;
    }

    Tristate Clock::compute([[maybe_unused]] size_t pin) {
        return this->_currentState;
    }
}
