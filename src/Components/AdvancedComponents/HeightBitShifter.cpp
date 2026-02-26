//
// Created by Noah on 19/02/2026.
//

#include "Components/AdvancedComponents/HeightBitShifter.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"
#include "Utils/Utils.h++"

namespace nts {
    HeightBitShifter::HeightBitShifter() : AComponent(16, Other) {}

    void HeightBitShifter::simulate(const size_t tick) {
        if (this->_lastSimulatedTick == tick)
            return;
        this->_lastSimulatedTick = tick;
    }

    void HeightBitShifter::shiftValue() {
        const Tristate clk = this->_connections[3].first->compute(this->_connections[3].second);
        const Tristate data = this->_connections[2].first->compute(this->_connections[2].second);

        if (data == Undefined)
            this->_value = -1;
        else if (this->_value == -1)
            this->_value = 0;
        if (this->_prevClk == False && clk == True && this->_value != -1) {
            this->_value = (this->_value << 1) | data;
            this->_Q = static_cast<Tristate>(Utils::getBinaryValueIdx(7, this->_value));
        }
        if (this->_prevClk == True && clk == False)
            this->_QS = static_cast<Tristate>(Utils::getBinaryValueIdx(7, this->_value));
        this->_prevClk = clk;
    }

    Tristate HeightBitShifter::compute(const size_t pin) {
        int value = this->_memValue;
        Tristate strobe = this->_connections[1].first->compute(this->_connections[1].second);
        Tristate OE = this->_connections[15].first->compute(this->_connections[15].second);

        if (pin >= 15 || (pin >= 1 && pin <= 3) || pin == 8)
            throw NanoTekSpiceException(SyntaxFileException);
        if (strobe == Undefined || OE == Undefined || OE == False)
            return Undefined;
        this->shiftValue();
        if (strobe == True) {
            value = this->_value;
            this->_memValue = value;
        }
        if (pin >= 4 && pin <= 7)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(pin - 3, value));
        if (pin == 14)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(5, value));
        if (pin == 13)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(6, value));
        if (pin == 12)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(7, value));
        if (pin == 11)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(8, value));
        if (pin == 9)
            return this->_QS;
        if (pin == 10)
            return this->_Q;
        return Undefined;
    }
}
