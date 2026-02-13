//
// Created by pavel on 07/02/2026.
//

#include "Input.h++"
#include "Errors/NanoTekSpiceErrors.h++"

namespace nts
{
    Input::Input() : AComponent(1, InputComponent)
    {
    }

    void Input::setValue(const Tristate value)
    {
        this->_nextState = value;
    }

    void Input::simulate([[maybe_unused]] size_t tick)
    {
        this->_currentState = _nextState;
    }

    Tristate Input::compute([[maybe_unused]] size_t pin)
    {
        return this->_currentState;
    }
}
