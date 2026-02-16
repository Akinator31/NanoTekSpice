//
// Created by Noah on 14/02/2026.
//

#include "Components/AdvancedComponents/FlipFlop.h++"
#include "Components/AComponent.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"

namespace nts {
    FlipFlop::FlipFlop() : AComponent(6, Other) {
    }

    void FlipFlop::simulate(size_t tick) {
        this->_lastSimulatedTick = tick;
    }

    Tristate FlipFlop::compute(size_t pin) {
        bool isAsync = false;
        Tristate cl = this->_connections[3].first->compute(this->_connections[3].second);
        Tristate r = this->_connections[4].first->compute(this->_connections[4].second);
        Tristate d = this->_connections[5].first->compute(this->_connections[5].second);
        Tristate s = this->_connections[6].first->compute(this->_connections[6].second);

        if (s == True || r == True) {
            isAsync = true;
            this->_q = False;
            this->_qBar = False;
            if (s == True)
                this->_q = True;
            if (r == True)
                this->_qBar = True;
        }
        if (!isAsync && d != Undefined && cl != Undefined && this->_lastClk == False && cl == True) {
            if (d == True) {
                this->_q = True;
                this->_qBar = False;
            } else {
                this->_q = False;
                this->_qBar = True;
            }
        }
        this->_lastClk = cl;
        if (pin == 1)
            return this->_q;
        if (pin == 2)
            return this->_qBar;
        throw NanoTekSpiceException(SyntaxFileException);
    }
}
