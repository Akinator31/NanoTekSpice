//
// Created by pavel on 09/02/2026.
//

#include "True.h++"
#include "Errors/NanoTekSpiceErrors.h++"

namespace nts
{
    void True::simulate([[maybe_unused]] size_t tick)
    {
    }

    Tristate True::compute([[maybe_unused]] size_t pin)
    {
        return this->_currentState;
    }

    void True::setLink(const size_t pin, [[maybe_unused]] IComponent& other,
                       [[maybe_unused]] size_t otherPin)
    {
        if (pin != 1)
            throw NanoTekSpiceException(SyntaxFileException);
    }
}
