//
// Created by pavel on 07/02/2026.
//

#include "Out.h++"

#include "Errors/NanoTekSpiceErrors.h++"
#include "False.h++"
#include "True.h++"

namespace nts {
    Tristate Out::getValue() const {
        return this->_currentState;
    }

    void Out::simulate([[maybe_unused]] size_t tick) {
    }

    Tristate Out::compute([[maybe_unused]] size_t pin) {
        this->_currentState = this->_link.component->compute(this->_link.pin);
        return this->_currentState;
    }

    void Out::setLink(const size_t pin, IComponent& other, const size_t otherPin) {
        IComponent* otherPtr = &other;

        if (pin != 1)
            throw NanoTekSpiceException(SyntaxFileException);

        this->_link = { .component = &other, .pin = otherPin };

        if (dynamic_cast<class True*>(otherPtr) || dynamic_cast<class False*>(otherPtr)) {
            this->compute(1);
        }
    }

    ComponentLink Out::getLink() const {
        return this->_link;
    }
}
