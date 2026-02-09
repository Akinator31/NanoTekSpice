//
// Created by pavel on 09/02/2026.
//

#include "Clock.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "Utils/Utils.h++"

namespace nts
{
    Tristate Clock::getValue() const
    {
        return this->_currentState;
    }

    void Clock::setValue(const Tristate value)
    {
        this->_nextState = value;
    }

    void Clock::simulate([[maybe_unused]] size_t tick)
    {
        // Quand on doit set la value d'une clock, on invert aussi ou on fait juste le set ?
        if (this->_currentState == this->_nextState)
        {
            this->_currentState = !this->_currentState;
            return;
        }
        this->_currentState = _nextState;
    }

    Tristate Clock::compute([[maybe_unused]] size_t pin)
    {
        return this->_currentState;
    }

    void Clock::setLink(const size_t pin, [[maybe_unused]] IComponent& other,
                        [[maybe_unused]] size_t otherPin)
    {
        if (pin != 1)
            throw NanoTekSpiceException(SyntaxFileException);
    }
}
