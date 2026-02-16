//
// Created by pavel on 13/02/2026.
//

#include "Full4BitsAdder.h++"

#include "Errors/NanoTekSpiceErrors.h++"
#include "Factory/Factory.h++"

namespace nts {
    Full4BitsAdder::Full4BitsAdder() : AComponent(4, Other) {
        Factory factory;

        this->_xor_gate1 = factory.createComponent("xor");
        this->_xor_gate2 = factory.createComponent("xor");
        this->_and_gate1 = factory.createComponent("and");
        this->_and_gate2 = factory.createComponent("and");
        this->_or_gate = factory.createComponent("or");

        this->_xor_gate1->setLink(3, *this->_xor_gate2, 2);
        this->_xor_gate2->setLink(2, *this->_xor_gate1, 3);
        this->_and_gate2->setLink(1, *this->_xor_gate1, 3);
        this->_or_gate->setLink(1, *this->_and_gate1, 3);
        this->_or_gate->setLink(2, *this->_and_gate2, 3);
    }

    void Full4BitsAdder::simulate(const size_t tick) {
        this->_xor_gate1->simulate(tick);
        this->_xor_gate2->simulate(tick);
        this->_and_gate1->simulate(tick);
        this->_and_gate2->simulate(tick);
        this->_or_gate->simulate(tick);
    }

    Tristate Full4BitsAdder::compute(const size_t pin) {
        if (pin == 4) {
            return this->_xor_gate2->compute(3);
        }
        if (pin == 5)
            return this->_or_gate->compute(3);
        throw NanoTekSpiceException(SyntaxFileException);
    }

    void Full4BitsAdder::setLink(const size_t pin, IComponent& other, const size_t otherPin) {
        if (pin == 1) {
            this->_xor_gate1->setLink(2, other, otherPin);
            this->_and_gate1->setLink(1, other, otherPin);
        }
        else if (pin == 2) {
            this->_xor_gate1->setLink(1, other, otherPin);
            this->_and_gate1->setLink(2, other, otherPin);
        }
        else if (pin == 3) {
            this->_xor_gate2->setLink(1, other, otherPin);
            this->_and_gate2->setLink(2, other, otherPin);
        }
        else if (pin == 4) {
            this->_xor_gate2->setLink(3, other, otherPin);
        }
        else if (pin == 5) {
            this->_or_gate->setLink(3, other, otherPin);
        }
        else {
            throw NanoTekSpiceException(SyntaxFileException);
        }
    }
}
