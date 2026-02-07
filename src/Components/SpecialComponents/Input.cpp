//
// Created by pavel on 07/02/2026.
//

#include "Input.h++"

namespace nts
{
    Tristate Input::getValue() const
    {
        return this->_currentState;
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

    void Input::setLink([[maybe_unused]] size_t pin, [[maybe_unused]] IComponent& other, [[maybe_unused]] size_t otherPin)
    {

    }
}
