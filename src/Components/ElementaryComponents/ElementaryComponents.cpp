//
// Created by pavel on 11/02/2026.
//

#include <utility>

#include "ElementaryComponents.h++"

#include "Factory/Factory.h++"

namespace nts
{
    ElementaryComponents::ElementaryComponents(size_t numberOfValueToCompute,
                                               std::function<Tristate (
                                                   Tristate first,
                                                   Tristate second)> operationFunc)
    {
        this->_operationFunc = std::move(operationFunc);
        this->_numberOfValueToCompute = numberOfValueToCompute;
    }

    void ElementaryComponents::simulate(const std::size_t tick)
    {
        this->_lastSimulatedTick = tick;
    }

    Tristate ElementaryComponents::compute(const std::size_t pin)
    {
        if (this->_lastComputedTick == this->_lastSimulatedTick)
            return this->_prevValue;
        if (this->_numberOfValueToCompute == 2)
        {
            if (pin == 3)
            {
                const Tristate value1 = this->_input[1].component->compute(this->_input[1].pin);
                const Tristate value2 = this->_input[2].component->compute(this->_input[2].pin);

                this->_prevValue = this->_operationFunc(value1, value2);

                this->_lastComputedTick = this->_lastSimulatedTick;
                return this->_prevValue;
            }
            return Undefined;
        }
        if (pin == 2)
        {
            const Tristate value1 = this->_input[1].component->compute(this->_input[1].pin);

            this->_prevValue = this->_operationFunc(value1, Undefined);

            this->_lastComputedTick = this->_lastSimulatedTick;
            return this->_prevValue;
        }
        return Undefined;
    }

    void ElementaryComponents::setLink(const std::size_t pin, IComponent& other, const std::size_t otherPin)
    {
        if ((this->_numberOfValueToCompute == 2 && (pin == 1 || pin == 2 || pin == 3)) || (this->_numberOfValueToCompute
            == 1 && (pin == 1 || pin == 2)))
        {
            this->_input[pin].component = &other;
            this->_input[pin].pin = otherPin;
        }
    }
}
