//
// Created by Noah on 17/02/2026.
//

#include "Components/AdvancedComponents/JohnsonDecade.h++"
#include "Components/AComponent.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"

namespace nts {
    JohnsonDecade::JohnsonDecade() : AComponent(16, Other) {}

    void JohnsonDecade::simulate(const size_t tick) {
        if (this->_lastSimulatedTick == tick)
            return;
        this->_lastSimulatedTick = tick;
    }

    Tristate JohnsonDecade::compute(const size_t pin) {
        if (pin > 12 || pin == 8)
            throw NanoTekSpiceException(SyntaxFileException);
        const Tristate clk = this->_connections[14].first->compute(this->_connections[14].second);
        const Tristate ci = this->_connections[13].first->compute(this->_connections[13].second);
        const Tristate reset = this->_connections[15].first->compute(this->_connections[15].second);

        if ((ci == False && this->_prevClk == False && clk == True) ||
            (this->_prevCi == True && ci == False)) {
            this->_qOn++;
            if (this->_qOn >= 10)
                this->_qOn = 0;
        }
        if (reset == True)
            this->_qOn = 0;
        this->_prevClk = clk;
        this->_prevCi = ci;
        if (clk == Undefined || reset == Undefined || ci == Undefined)
            return Undefined;
        if (pin == 12) {
            if (this->_qOn < 5)
                return True;
            return False;
        }
        // Q5
        if (pin == 1 && this->_qOn == 5)
            return True;
        // Q1
        if (pin == 2 && this->_qOn == 1)
            return True;
        // Q0
        if (pin == 3 && this->_qOn == 0)
            return True;
        // Q2
        if (pin == 4 && this->_qOn == 2)
            return True;
        // Q6
        if (pin == 5 && this->_qOn == 6)
            return True;
        // Q7
        if (pin == 6 && this->_qOn == 7)
            return True;
        // Q3
        if (pin == 7 && this->_qOn == 3)
            return True;
        // Q8
        if (pin == 9 && this->_qOn == 8)
            return True;
        // Q4
        if (pin == 10 && this->_qOn == 4)
            return True;
        // Q9
        if (pin == 11 && this->_qOn == 9)
            return True;
        return False;
    }
}
