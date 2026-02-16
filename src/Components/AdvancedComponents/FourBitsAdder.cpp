//
// Created by pavel on 07/02/2026.
//

#include "FourBitsAdder.h++"

#include "Errors/NanoTekSpiceErrors.h++"
#include "Factory/Factory.h++"

namespace nts {
    FourBitsAdder::FourBitsAdder() : AComponent(13, Other) {
        Factory factory;

        this->_halfBitsAdder = factory.createComponent("halfBitsAdder");
        this->_fullBitsAdder1 = factory.createComponent("fullBitsAdder");
        this->_fullBitsAdder2 = factory.createComponent("fullBitsAdder");
        this->_fullBitsAdder3 = factory.createComponent("fullBitsAdder");

        this->_computeFuncs = {
            {
                9, [this] {
                    return this->_halfBitsAdder->compute(3);
                }
            },
            {
                10, [this] {
                    return this->_fullBitsAdder1->compute(4);
                }
            },
            {
                11, [this] {
                    return this->_fullBitsAdder2->compute(4);
                }
            },
            {
                12, [this] {
                    return this->_fullBitsAdder3->compute(4);
                }
            },
            {
                13, [this] {
                    return this->_fullBitsAdder3->compute(5);
                }
            }
        };

        this->_setLinksFuncs = {
            {
                1, [this](IComponent& other, const size_t otherPin) {
                    this->_halfBitsAdder->setLink(1, other, otherPin);
                }
            },
            {
                2, [this](IComponent& other, const size_t otherPin) {
                    this->_halfBitsAdder->setLink(2, other, otherPin);
                }
            },
            {
                3, [this](IComponent& other, const size_t otherPin) {
                    this->_fullBitsAdder1->setLink(1, other, otherPin);
                }
            },
            {
                4, [this](IComponent& other, const size_t otherPin) {
                    this->_fullBitsAdder1->setLink(2, other, otherPin);
                }
            },
            {
                5, [this](IComponent& other, const size_t otherPin) {
                    this->_fullBitsAdder2->setLink(1, other, otherPin);
                }
            },
            {
                6, [this](IComponent& other, const size_t otherPin) {
                    this->_fullBitsAdder2->setLink(2, other, otherPin);
                }
            },
            {
                7, [this](IComponent& other, const size_t otherPin) {
                    this->_fullBitsAdder3->setLink(1, other, otherPin);
                }
            },
            {
                8, [this](IComponent& other, const size_t otherPin) {
                    this->_fullBitsAdder3->setLink(2, other, otherPin);
                }
            },
            {
                9, [this](IComponent& other, const size_t otherPin) {
                    this->_halfBitsAdder->setLink(3, other, otherPin);
                }
            },
            {
                10, [this](IComponent& other, const size_t otherPin) {
                    this->_fullBitsAdder1->setLink(4, other, otherPin);
                }
            },
            {
                11, [this](IComponent& other, const size_t otherPin) {
                    this->_fullBitsAdder2->setLink(4, other, otherPin);
                }
            },
            {
                12, [this](IComponent& other, const size_t otherPin) {
                    this->_fullBitsAdder3->setLink(4, other, otherPin);
                }
            },
            {
                13, [this](IComponent& other, const size_t otherPin) {
                    this->_fullBitsAdder3->setLink(5, other, otherPin);
                }
            },
        };

        this->_fullBitsAdder1->setLink(3, *this->_halfBitsAdder, 4);
        this->_fullBitsAdder2->setLink(3, *this->_fullBitsAdder1, 5);
        this->_fullBitsAdder3->setLink(3, *this->_fullBitsAdder2, 5);
    }

    void FourBitsAdder::simulate(const size_t tick) {
        this->_halfBitsAdder->simulate(tick);
        this->_fullBitsAdder1->simulate(tick);
        this->_fullBitsAdder2->simulate(tick);
        this->_fullBitsAdder3->simulate(tick);
    }

    Tristate FourBitsAdder::compute(const size_t pin) {
        if (this->_computeFuncs.contains(pin))
            return this->_computeFuncs[pin]();
        throw NanoTekSpiceException(SyntaxFileException);
    }

    void FourBitsAdder::setLink(const size_t pin, IComponent& other, const size_t otherPin) {
        if (this->_setLinksFuncs.contains(pin))
            this->_setLinksFuncs[pin](other, otherPin);
        else
            throw NanoTekSpiceException(SyntaxFileException);
    }
}
