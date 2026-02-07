//
// Created by pavel on 07/02/2026.
//

#include "Out.h++"

#include <iostream>

namespace nts
{
    Tristate Out::getValue() const
    {
        return this->_currentState;
    }

    void Out::simulate([[maybe_unused]] size_t tick)
    {

    }

    Tristate Out::compute([[maybe_unused]] size_t pin)
    {
        this->_currentState = this->_link.component->compute(this->_link.pin);
        return this->_currentState;
    }

    void Out::setLink(const size_t pin, IComponent& other, const size_t otherPin)
    {
        this->_pin = pin;
        this->_link = {
            .component = &other,
            .pin = otherPin
        };
    }

    ComponentLink Out::getLink() const
    {
        return this->_link;
    }
}
