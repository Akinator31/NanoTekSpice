//
// Created by pavel on 11/02/2026.
//

#include <utility>

#include "ElementaryComponents.h++"

#include "Factory/Factory.h++"

namespace nts {
    ElementaryComponents::ElementaryComponents(
        const size_t _numberOfPins,
        std::function<Tristate(Tristate first, Tristate second)> operationFunc) :
        AComponent(_numberOfPins, Other) {
        this->_operationFunc = std::move(operationFunc);
        this->_numberOfPins = _numberOfPins;
    }

    Tristate ElementaryComponents::compute(const std::size_t pin) {
        if (this->_lastComputedTick == this->_lastSimulatedTick)
            return this->_currentValue;
        if (this->_numberOfPins == 3) {
            if (pin == 3) {
                const Tristate value1 = this->_connections[1].first->compute(this->_connections[1].second);
                const Tristate value2 = this->_connections[2].first->compute(this->_connections[2].second);

                this->_currentValue = this->_operationFunc(value1, value2);

                this->_lastComputedTick = this->_lastSimulatedTick;
                return this->_currentValue;
            }
            return Undefined;
        }
        if (pin == 2) {
            const Tristate value1 = this->_connections[1].first->compute(this->_connections[1].second);

            this->_currentValue = this->_operationFunc(value1, Undefined);

            this->_lastComputedTick = this->_lastSimulatedTick;
            return this->_currentValue;
        }
        return Undefined;
    }
}
