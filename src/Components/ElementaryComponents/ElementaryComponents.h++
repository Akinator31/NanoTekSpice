//
// Created by pavel on 11/02/2026.
//

#pragma once
#include <cstddef>
#include <functional>

#include "Components/AComponent.h++"
#include "IComponent.h++"

namespace nts {
    /**
     * Generic class for create GatesComponent
     */
    class ElementaryComponents : public AComponent {
        std::function<Tristate(Tristate first, Tristate second)> _operationFunc; ///< Tristate operation func
        size_t _numberOfPins;

    public:
        /**
         * Constructor for generic Elementary Components
         * @param _numberOfPins of values taken in input
         * @param operationFunc Func that compute operation on Tristate
         */
        ElementaryComponents(
            size_t _numberOfPins, std::function<Tristate(Tristate first, Tristate second)> operationFunc);

        /**
         * @brief Compute the result on the selected pin.
         * @param pin Pin to know which 'interior component' computes the result.
         * @return nts::Tristate The computed result.
         */
        Tristate compute(std::size_t pin) override;
    };
}

///< Macros that allow you to create elementary component easily
#define CREATE_AND std::make_unique<ElementaryComponents>(3, operator&&);
#define CREATE_OR std::make_unique<ElementaryComponents>(3, operator||);
#define CREATE_XOR std::make_unique<ElementaryComponents>(3, operator^);
#define CREATE_NOT                                                                                           \
    std::make_unique<ElementaryComponents>(                                                                  \
        2, [](const Tristate first, [[maybe_unused]] Tristate second) { return !first; });
#define CREATE_NOR                                                                                           \
    std::make_unique<ElementaryComponents>(                                                                  \
        3, [](const Tristate first, [[maybe_unused]] Tristate second) { return !(first || second); });
#define CREATE_NAND                                                                                          \
    std::make_unique<ElementaryComponents>(                                                                  \
        3, [](const Tristate first, [[maybe_unused]] Tristate second) { return !(first && second); });
