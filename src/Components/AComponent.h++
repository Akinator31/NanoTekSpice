//
// Created by pavel on 12/02/2026.
//

#pragma once
#include "IComponent.h++"

#include <map>
#include <utility>

namespace nts {
    /**
     * Abstract class of IComponent interface used for most components.
     */
    class AComponent : public IComponent {
        size_t _maxPins; ///< Max pin of a component
        componentType _typeComponent; ///< Type of component @see componentType

    public:
        std::size_t _lastComputedTick = -1; ///< Last computed tick for compare if the value has already been computed.
        std::size_t _lastSimulatedTick = 0; ///< Last simulated tick.
        Tristate _currentValue = Undefined; ///< Current value on a component (use for component like Input, Output...)
        std::map<size_t, std::pair<IComponent*, size_t>> _connections; ///< Component connections

        /**
         * Create a component
         * @param maxPin Number of pin of the component
         * @param type Type of component
         */
        AComponent(const size_t maxPin, const componentType type) : _maxPins(maxPin), _typeComponent(type) {};

        /**
         * Link a component to a specific pin of the component
         * @param pin Pin of the component
         * @param other The other component you want to link to the Logger pin
         * @param otherPin The other component pin
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;

        /**
         * Simulate a tick for the component
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Set the value of a component (Input, Output, Clock)
         * @param value The value to be set
         */
        void setValue([[maybe_unused]] Tristate value) override {};

        /**
         * Compute a specific pin of the component
         * @param pin Pin of the component
         * @return The value of the selected pin of the component
         */
        Tristate compute(size_t pin) override;

        /**
         * Get the type of the component
         * @return The type of component
         */
        componentType getType() override;
    };
}
