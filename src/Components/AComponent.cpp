//
// Created by pavel on 12/02/2026.
//

#include "AComponent.h++"

#include "Errors/NanoTekSpiceErrors.h++"

namespace nts {
    void AComponent::setLink(const size_t pin, IComponent& other, size_t otherPin) {
        if (pin == 0 || pin > _maxPins)
            throw NanoTekSpiceException(SyntaxFileException);
        this->_connections[pin] = {&other, otherPin};
    }

    Tristate AComponent::compute(const size_t pin) {
        if (this->_lastComputedTick == this->_lastSimulatedTick)
            return this->_currentValue;
        if (this->_connections.empty())
            return Undefined;
        this->_lastComputedTick = this->_lastSimulatedTick;
        this->_currentValue = this->_connections[pin].first->compute(this->_connections[pin].second);
        return this->_currentValue;
    }

    void AComponent::simulate(const size_t tick) {
        this->_lastSimulatedTick = tick;
    }

    componentType AComponent::getType() {
        return this->_typeComponent;
    }
}
