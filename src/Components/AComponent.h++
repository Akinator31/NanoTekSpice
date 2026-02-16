//
// Created by pavel on 12/02/2026.
//

#pragma once
#include "IComponent.h++"

#include <map>
#include <utility>

namespace nts {
    class AComponent : public IComponent {
        size_t _maxPins;
        componentType _typeComponent;

    public:
        std::size_t _lastComputedTick = -1; ///< Last computed tick for compare if the value has already been computed.
        std::size_t _lastSimulatedTick = 0; ///< Last simulated tick.
        Tristate _currentValue = Undefined;
        std::map<size_t, std::pair<IComponent*, size_t>> _connections;

        AComponent(const size_t maxPin, const componentType type) : _maxPins(maxPin), _typeComponent(type) {};

        void setLink(size_t pin, IComponent& other, size_t otherPin) override;

        void simulate(size_t tick) override;

        void setValue([[maybe_unused]] Tristate value) override {};

        Tristate compute(size_t pin) override;

        Tristate getInputValue(size_t pin);

        componentType getType() override;
    };
}
