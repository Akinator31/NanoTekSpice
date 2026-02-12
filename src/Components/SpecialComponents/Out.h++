//
// Created by pavel on 07/02/2026. Le mec est out.
//

#pragma once
#include "IComponent.h++"

namespace nts {
    /**
     * @class Out
     * @brief Class for Out Special Component
     * @details This class inherit from IComponent interface
     * @see IComponent
     */
    class Out : public IComponent {
        Tristate _currentState = Undefined; ///< Current state of the Out component (used by the compute function)
        ComponentLink _link;                ///< The component's pin linked to the output

    public:
        /**
         * @brief Simulate a tick of an Out component
         * @param tick The global tick of the circuit
         * @see nts::Circuit
         */
        void simulate(size_t tick) override;

        /**
         * @brief Compute the result on the selected pin. Here, we call the compute function of the linked component and so on.
         * @param pin Pin to know which 'interior component' computes the result. Useless here because Out component has only one pin.
         * @return nts::Tristate The computed result, so here, just this->_currentState.
         */
        Tristate compute(size_t pin) override;

        /**
         * @brief Link a pin of another component. Here, we link the Out component to the component that we want the result from.
         * @param pin Pin of the Out component. Useless here
         * @param other Component to linked
         * @param otherPin Pin of the component to linked
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;

        /**
         * @return The linked component (I think [[nodiscard]] is useless here but Clion like it).
         */
        [[nodiscard]] ComponentLink getLink() const;

        /**
         * @brief Get the actual value of the Out component
         * @return nts::Tristate The actual state (I think [[nodiscard]] is useless here but Clion like it)
         * @see nts::Tristate
         */
        [[nodiscard]] Tristate getValue() const;
    };
}
