//
// Created by Noah on 15/02/2026.
//

#include "Components/AdvancedComponents/BitBinaryCounter.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"
#include "Utils/Utils.h++"

namespace nts {
    BitBinaryCounter::BitBinaryCounter() : AComponent(16, Other) {}

    void BitBinaryCounter::_computeVal() {
        Tristate clk;
        Tristate r;

        if (this->_lastComputedTick == this->_lastSimulatedTick) {
            clk = this->cachedClk;
            r = this->cachedReset;
        }
        else {
            this->cachedClk = this->_connections[10].first->compute(this->_connections[10].second);
            this->cachedReset = this->_connections[11].first->compute(this->_connections[11].second);
            clk = this->cachedClk;
            r = this->cachedReset;
        }

        if (r == True || clk == Undefined) {
            this->_value = 0;
            if (clk == Undefined)
                this->_value = -1;
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

    void BitBinaryCounter::simulate(const size_t tick) {
        this->_lastSimulatedTick = tick;
    }

    Tristate BitBinaryCounter::compute(const size_t pin) {
        if (pin > 15 || pin == 8)
            throw NanoTekSpiceException(SyntaxFileException);
        this->_computeVal();
        const Tristate r = this->cachedReset;

        this->_lastComputedTick = this->_lastSimulatedTick;


        if (r == True) {
            this->_value = 0;
            return False;
        }
        if (pin == 1)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(12, this->_value));
        if (pin == 2)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(6, this->_value));
        if (pin == 3)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(5, this->_value));
        if (pin == 4)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(7, this->_value));
        if (pin == 5)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(4, this->_value));
        if (pin == 6)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(3, this->_value));
        if (pin == 7)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(2, this->_value));
        if (pin == 15)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(11, this->_value));
        if (pin == 14)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(10, this->_value));
        if (pin == 13)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(8, this->_value));
        if (pin == 12)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(9, this->_value));
        if (pin == 9)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(1, this->_value));
        return Undefined;
    }
};
