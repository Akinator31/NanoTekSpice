//
// Created by Noah on 15/02/2026.
//

#include "Components/AdvancedComponents/BitBinaryCounter.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"
#include <cstddef>

static uint getBinaryValueIdx(size_t idx, int value) {
    return (value >> (idx - 1)) % 2;
}

namespace nts {
    BitBinaryCounter::BitBinaryCounter() : AComponent(16, Other) {
    }

    void BitBinaryCounter::computeVal() {
        Tristate clk = this->_connections[10].first->compute(this->_connections[10].second);
        Tristate r = this->_connections[11].first->compute(this->_connections[11].second);

        if (r == True || clk == Undefined) {
            this->_value = 0;
            this->_lastClk = clk;
            return;
        }
        if (!(this->_lastClk == True && clk == False)) {
            this->_lastClk = clk;
            return;
        }
        this->_lastClk = clk;
        this->_value += 1;
        if (this->_value == 4096)
            this->_value = 0;
    }

    void BitBinaryCounter::simulate(size_t tick) {
        this->_lastSimulatedTick = tick;
    }

    Tristate BitBinaryCounter::compute(size_t pin) {
        if (pin > 15 || pin == 8)
            throw NanoTekSpiceException(SyntaxFileException);
        this->computeVal();
        Tristate r = this->_connections[11].first->compute(this->_connections[11].second);

        if (r == True) {
            this->_value = 0;
            return False;
        }
        if (pin == 1)
            return (Tristate)getBinaryValueIdx(12, this->_value);
        if (pin == 2)
            return (Tristate)getBinaryValueIdx(6, this->_value);
        if (pin == 3)
            return (Tristate)getBinaryValueIdx(5, this->_value);
        if (pin == 4)
            return (Tristate)getBinaryValueIdx(7, this->_value);
        if (pin == 5)
            return (Tristate)getBinaryValueIdx(4, this->_value);
        if (pin == 6)
            return (Tristate)getBinaryValueIdx(3, this->_value);
        if (pin == 7)
            return (Tristate)getBinaryValueIdx(2, this->_value);
        if (pin == 15)
            return (Tristate)getBinaryValueIdx(11, this->_value);
        if (pin == 14)
            return (Tristate)getBinaryValueIdx(10, this->_value);
        if (pin == 13)
            return (Tristate)getBinaryValueIdx(8, this->_value);
        if (pin == 12)
            return (Tristate)getBinaryValueIdx(9, this->_value);
        if (pin == 9)
            return (Tristate)getBinaryValueIdx(1, this->_value);
        return Undefined;
    }
};
