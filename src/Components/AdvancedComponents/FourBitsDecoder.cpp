//
// Created by Noah on 01/03/2026.
//

#include "Components/AdvancedComponents/FourBitsDecoder.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"
#include "Utils/Utils.h++"

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
            this->_value = 0;
            return;
        }
        if (strobe == False)
            return;
        if (A == Undefined || B == Undefined || C == Undefined || D == Undefined) {
            this->_value = -1;
            return;
        }
        this->_value = (A * 8) + (B * 4) + (C * 2) + D;
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
        if (pin == 4)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(8, this->_value));
        if (pin == 5)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(7, this->_value));
        if (pin == 6)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(6, this->_value));
        if (pin == 7)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(5, this->_value));
        if (pin == 8)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(4, this->_value));
        if (pin == 9)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(3, this->_value));
        if (pin == 10)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(2, this->_value));
        if (pin == 11)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(1, this->_value));
        if (pin == 13)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(14, this->_value));
        if (pin == 14)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(13, this->_value));
        if (pin == 15)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(16, this->_value));
        if (pin == 16)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(15, this->_value));
        if (pin == 17)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(10, this->_value));
        if (pin == 18)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(9, this->_value));
        if (pin == 19)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(12, this->_value));
        if (pin == 20)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(11, this->_value));
        return Undefined;
    }
}
