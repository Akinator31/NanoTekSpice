//
// Created by pavel on 12/02/2026.
//

#include "Half4bitsAdder.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "Factory/Factory.h++"

namespace nts {
    Half4bitsAdder::Half4bitsAdder() : AComponent(4, Other) {
        Factory factory;

        this->_xor_gate = factory.createComponent("xor");
        this->_and_gate = factory.createComponent("and");
    }

    void Half4bitsAdder::simulate(const size_t tick) {
        this->_xor_gate->simulate(tick);
        this->_and_gate->simulate(tick);
    }

    Tristate Half4bitsAdder::compute(size_t pin) {
        if (pin == 3)
            return this->_xor_gate->compute(3);
        if (pin == 4)
            return this->_and_gate->compute(3);
        throw NanoTekSpiceException(SyntaxFileException);
    }

    void Half4bitsAdder::setLink(size_t pin, IComponent& other, size_t otherPin) {
        if (pin == 1) {
            this->_xor_gate->setLink(2, other, otherPin);
            this->_and_gate->setLink(2, other, otherPin);
        }
        else if (pin == 2) {
            this->_xor_gate->setLink(1, other, otherPin);
            this->_and_gate->setLink(1, other, otherPin);
        }
        else if (pin == 3) {
            this->_xor_gate->setLink(3, other, otherPin);
        }
        else if (pin == 4) {
            this->_and_gate->setLink(3, other, otherPin);
        }
        else {
            throw NanoTekSpiceException(SyntaxFileException);
        }
    }
}
