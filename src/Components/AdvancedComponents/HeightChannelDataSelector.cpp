//
// Created by Noah on 22/02/2026.
//

#include "Components/AdvancedComponents/HeightChannelDataSelector.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"
#include <cstddef>
namespace nts {
    HeightChannelDataSelector::HeightChannelDataSelector() : AComponent(16, Other) {
    }

    void HeightChannelDataSelector::simulate(size_t tick) {
        if (this->_lastSimulatedTick == tick)
            return;
        this->_lastSimulatedTick = tick;
    }

    Tristate HeightChannelDataSelector::compute(size_t pin) {
        if (pin != 14)
            throw NanoTekSpiceException(SyntaxFileException);
        Tristate inhibit = this->_connections[10].first->compute(this->_connections[10].second);
        Tristate OE = this->_connections[15].first->compute(this->_connections[15].second);
        Tristate A = this->_connections[11].first->compute(this->_connections[11].second);
        Tristate B = this->_connections[12].first->compute(this->_connections[12].second);
        Tristate C = this->_connections[13].first->compute(this->_connections[13].second);
        int i = (C == True) * 4 + (B == True) * 2 + (A == True);

        if (OE == True || OE == Undefined || inhibit == Undefined || A == Undefined || B == Undefined ||
            C == Undefined)
            return Undefined;
        if (inhibit == True)
            return False;
        if (i == 7)
            return this->_connections[9].first->compute(this->_connections[9].second);
        return this->_connections[i + 1].first->compute(this->_connections[i + 1].second);
    }
}
