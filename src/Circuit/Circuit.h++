//
// Created by pavel on 07/02/2026.
//

#pragma once

#include <functional>
#include <map>
#include <typeindex>

#include "IComponent.h++"

namespace nts {
    /**
     * @brief Circuit class to orchestrate all components.
     */
    class Circuit {
    public:
        /**
         * Circuit constructor.
         */
        Circuit();

        /**
         * @brief Simulate a tick of the circuit.
         */
        void simulate(std::string& command);

        /**
         * @brief Prints the current tick and the value of all inputs and outputs on the standard output, each sorted by name in ASCII order.
         */
        void display(std::string& command);

        /**
         * Assign a value to an input.
         * @param command The command
         */
        void assign(const std::string& command);

        /**
         * @brief Exit the program.
         */
        void exit(std::string& command);

        /**
         * @brief Add a component into the circuit.
         * @param name Name of the added component.
         * @param component The component to add.
         * @return True if the component has been added. False otherwise.
         */
        bool addComponent(const std::string& name, std::unique_ptr<IComponent> component);

        /**
         * @brief Link a pin component to another.
         * @param componentName Name of the component.
         * @param componentPin The pin of the component.
         * @param componentToLink Name of the component to link.
         * @param componentToLinkPin The pin of the component to link.
         */
        void addLink(const std::string& componentName, size_t componentPin, const std::string& componentToLink, size_t componentToLinkPin);

        /**
         * Simulate in loop.
         */
        [[noreturn]] void loop(std::string& command);

        /**
         * Start the command line interface.
         */
        void startCli();

    private:
        size_t _tick = 0; ///< Global tick of the circuit.

        ///< Bool that tell the program to quit when exit cli function is called.
        bool _cliDoesExit = false;

        ///< Map that stored all components of the circuit.
        std::map<std::string, std::unique_ptr<IComponent>> _componentList = {};

        ///< Map that stored CLI functions.
        std::map<std::string, std::function<void(std::string&)>> _circuitFuncs = {};

        ///< Map that stored display functions.
        std::map<std::type_index, std::function<void(IComponent*, const std::string&)>> _displayFuncs;
    };
}
