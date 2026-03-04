//
// Created by Noah on 01/03/2026.
//

#include "Components/AdvancedComponents/FourBitsDecoder.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"

namespace nts {
    FourBitsDecoder::FourBitsDecoder() : AComponent(24, Other) {
    }

    void FourBitsDecoder::computeVal() {
        Tristate strobe = this->_connections[1].first->compute(this->_connections[1].second);
        Tristate inhib = this->_connections[23].first->compute(this->_connections[23].second);
        Tristate A = this->_connections[2].first->compute(this->_connections[2].second);
        Tristate B = this->_connections[3].first->compute(this->_connections[3].second);
        Tristate C = this->_connections[21].first->compute(this->_connections[21].second);
        Tristate D = this->_connections[22].first->compute(this->_connections[22].second);

        if (inhib == True) {
            this->_value = -2;
            return;
        }
        if (strobe == False)
            return;
        if (A == Undefined || B == Undefined || C == Undefined || D == Undefined) {
            this->_value = -1;
            return;
        }
        this->_value = (D * 8) + (C * 4) + (B * 2) + A;
    }

    void FourBitsDecoder::simulate(const size_t tick) {
        this->_lastSimulatedTick = tick;
    }

    Tristate FourBitsDecoder::compute(const size_t pin) {
        Tristate strobe = this->_connections[1].first->compute(this->_connections[1].second);
        Tristate inhib = this->_connections[23].first->compute(this->_connections[23].second);

        if (!(pin >= 4 && pin <= 11) && !(pin >= 13 && pin <= 20))
            throw NanoTekSpiceException(SyntaxFileException);
        if (strobe == Undefined || inhib == Undefined)
            return Undefined;
        this->computeVal();
        if (this->_value == -1)
            return Undefined;
        if (this->_value == -2)
            return False;
        if (pin == 4)
            return static_cast<Tristate>(this->_value == 7);
        if (pin == 5)
            return static_cast<Tristate>(this->_value == 6);
        if (pin == 6)
            return static_cast<Tristate>(this->_value == 5);
        if (pin == 7)
            return static_cast<Tristate>(this->_value == 4);
        if (pin == 8)
            return static_cast<Tristate>(this->_value == 3);
        if (pin == 9)
            return static_cast<Tristate>(this->_value == 1);
        if (pin == 10)
            return static_cast<Tristate>(this->_value == 2);
        if (pin == 11)
            return static_cast<Tristate>(this->_value == 0);
        if (pin == 13)
            return static_cast<Tristate>(this->_value == 13);
        if (pin == 14)
            return static_cast<Tristate>(this->_value == 12);
        if (pin == 15)
            return static_cast<Tristate>(this->_value == 15);
        if (pin == 16)
            return static_cast<Tristate>(this->_value == 14);
        if (pin == 17)
            return static_cast<Tristate>(this->_value == 9);
        if (pin == 18)
            return static_cast<Tristate>(this->_value == 8);
        if (pin == 19)
            return static_cast<Tristate>(this->_value == 11);
        if (pin == 20)
            return static_cast<Tristate>(this->_value == 10);
        return Undefined;
    }
}
