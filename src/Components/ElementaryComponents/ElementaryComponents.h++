//
// Created by pavel on 11/02/2026.
//

#pragma once
#include <cstddef>
#include <functional>
#include <map>

#include "IComponent.h++"

namespace nts {
    /**
     * Generic class for create GatesComponent
     */
    class ElementaryComponents : public IComponent {
        std::map<std::size_t, ComponentLink> _input; ///< Map that stored linked component.
        Tristate _prevValue = Undefined;             ///< Previously computed value to avoid recomputation.

        std::size_t _lastComputedTick = -1; ///< Last computed tick for compare if the value has already been computed.
        std::size_t _lastSimulatedTick = 0; ///< Last simulated tick.

        std::function<Tristate(Tristate first, Tristate second)> _operationFunc; ///< Tristate operation func
        size_t _numberOfValueToCompute;                                          ///< Number of values taken in input

    public:
        /**
         * Constructor for generic Elementary Components
         * @param _numberOfValueToCompute Number of values taken in input
         * @param operationFunc Func that compute operation on Tristate
         */
        ElementaryComponents(size_t _numberOfValueToCompute, std::function<Tristate(Tristate first, Tristate second)> operationFunc);

        /**
         * @brief Simulate a tick of a component
         * @param tick The global tick of the circuit
         * @see nts::Circuit
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Compute the result on the selected pin.
         * @param pin Pin to know which 'interior component' computes the result.
         * @return nts::Tristate The computed result.
         */
        Tristate compute(std::size_t pin) override;

        /**
         * @brief Link a pin of another component.
         * @param pin Pin of the AndGate component.
         * @param other Component to linked
         * @param otherPin Pin of the component to linked
         */
        void setLink(std::size_t pin, IComponent& other, std::size_t otherPin) override;
    };
} // namespace nts

///< Macros that allow you to create elementary component easily
#define CREATE_AND std::make_unique<ElementaryComponents>(2, operator&&);
#define CREATE_OR std::make_unique<ElementaryComponents>(2, operator||);
#define CREATE_XOR std::make_unique<ElementaryComponents>(2, operator^);
#define CREATE_NOT std::make_unique<ElementaryComponents>(1, [](const Tristate first, [[maybe_unused]] Tristate second) { return !first; });
#define CREATE_NOR                                                                                                                                   \
    std::make_unique<ElementaryComponents>(2, [](const Tristate first, [[maybe_unused]] Tristate second) {                                           \
        if (first == False && second == False)                                                                                                       \
            return nts::True;                                                                                                                        \
        if (first == nts::Undefined || second == nts::Undefined)                                                                                     \
            return nts::Undefined;                                                                                                                   \
        return nts::False;                                                                                                                           \
    });
#define CREATE_NAND                                                                                                                                  \
    std::make_unique<ElementaryComponents>(2, [](const Tristate first, [[maybe_unused]] Tristate second) {                                           \
        if (first == True && second == True)                                                                                                         \
            return nts::False;                                                                                                                       \
        if (first == nts::Undefined || second == nts::Undefined)                                                                                     \
            return nts::Undefined;                                                                                                                   \
        return nts::True;                                                                                                                            \
    });
