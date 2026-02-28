//
// Created by pavel on 26/02/2026.
//

#pragma once
#include <fstream>

#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
    /**
     * Enum for better understanding of the component behavior
     */
    enum LoggerComponent {
        INPUT1 = 1,
        INPUT2 = 2,
        INPUT3 = 3,
        INPUT4 = 4,
        INPUT5 = 5,
        INPUT6 = 6,
        INPUT7 = 7,
        INPUT8 = 8,
        CLOCK = 9,
        INHIBIT = 10,
    };

    /**
     * Class for the logger component
     */
    class Logger : public AComponent {
        Tristate _clockPrevState = Undefined; ///< Internal clock for detect positive going-edge of the internal clock

        std::map<int, std::pair<IComponent*, size_t>> _links; ///< Stored links of inputs of the component

        std::ofstream _logFile; ///< Stream for writing the log into the log.bin file

    public:
        /**
         * Logger constructor
         */
        Logger();

        /**
         * Simulate a tick for the Logger component
         * @param tick Actual tick of the circuit
         */
        void simulate(size_t tick) override;

        /**
         * Compute a specific pin of the Logger component
         * @param pin Pin of the Logger component
         * @return The value of the selected pin of the Logger component
         */
        Tristate compute(size_t pin) override;

        /**
         * Link a component to a specific pin of the Logger component
         * @param pin Pin of the Logger component
         * @param other The other component you want to link to the Logger pin
         * @param otherPin The other component pin
         */
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}

///< Macro used for create a Logger easily
#define CREATE_LOGGER std::make_unique<Logger>();
