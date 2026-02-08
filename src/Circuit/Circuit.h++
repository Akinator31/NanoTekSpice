//
// Created by pavel on 07/02/2026.
//

#pragma once

#include <map>

#include "IComponent.h++"

namespace nts
{
    /**
     * @brief Circuit class to orchestrate all components
     */
    class Circuit
    {
        size_t _tick = 0; ///< Global tick of the circuit.
        std::pmr::map<std::string, std::unique_ptr<IComponent>> componentList= {}; ///< Map that stored all components of the circuit.

    public:
        /**
         * @brief Simulate a tick of the circuit.
         */
        void simulate();

        /**
         * @brief Prints the current tick and the value of all inputs and outputs on the standard output, each sorted by name in ASCII order.
         */
        void display() const;

        /**
         * @brief Add a component into the circuit.
         * @param name Name of the added component.
         * @param component The component to add.
         */
        void add_component(const std::string& name, std::unique_ptr<IComponent> component);
    };
}