//
// Created by pavel on 09/02/2026.
//

#include "False.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"

namespace nts {
    void False::simulate([[maybe_unused]] size_t tick) {
    }

    Tristate False::compute([[maybe_unused]] size_t pin) {
        return this->_currentState;
    }

    void False::setLink(const size_t pin, [[maybe_unused]] IComponent& other, [[maybe_unused]] size_t otherPin) {
        if (pin != 1)
            throw NanoTekSpiceException(SyntaxFileException);
        other.compute(otherPin);
    }
} // namespace nts
