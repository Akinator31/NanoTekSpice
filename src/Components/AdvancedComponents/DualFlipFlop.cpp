//
// Created by Noah on 15/02/2026.
//

#include "Components/AdvancedComponents/DualFlipFlop.h++"
#include "Components/AComponent.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "Factory/Factory.h++"
#include "IComponent.h++"
#include <cstddef>

namespace nts {
    DualFlipFlop::DualFlipFlop() : AComponent(14, Other) {
        Factory factory;

        this->_flipflop1 = factory.createComponent("flipflop");
        this->_flipflop2 = factory.createComponent("flipflop");
    }

    void DualFlipFlop::setLink(size_t pin, IComponent& other, size_t otherPin) {
        if (pin == 0 || pin == 7 || pin > 13)
            throw NanoTekSpiceException(SyntaxFileException);
        if (pin < 8) {
            this->_flipflop1->setLink(pin, other, otherPin);
            return;
        }
        if (pin == 8)
            this->_flipflop2->setLink(6, other, otherPin);
        if (pin == 9)
            this->_flipflop2->setLink(5, other, otherPin);
        if (pin == 10)
            this->_flipflop2->setLink(4, other, otherPin);
        if (pin == 11)
            this->_flipflop2->setLink(3, other, otherPin);
        if (pin == 12)
            this->_flipflop2->setLink(2, other, otherPin);
        if (pin == 13)
            this->_flipflop2->setLink(1, other, otherPin);
    }

    void DualFlipFlop::simulate(size_t tick) {
        this->_flipflop1->simulate(tick);
        this->_flipflop2->simulate(tick);
    }

    Tristate DualFlipFlop::compute(size_t pin) {
        if (pin != 1 && pin != 2 && pin != 12 && pin != 13)
            throw NanoTekSpiceException(SyntaxFileException);
        if (pin > 2) {
            if (pin == 12)
                return this->_flipflop2->compute(2);
            else if (pin == 13)
                return this->_flipflop2->compute(1);
        }
        return this->_flipflop1->compute(pin);
    }
}
