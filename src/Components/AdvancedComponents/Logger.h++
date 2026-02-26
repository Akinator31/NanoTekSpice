//
// Created by pavel on 26/02/2026.
//

#pragma once
#include <fstream>

#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
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

    class Logger : public AComponent {
        Tristate _clockPrevState = Undefined;

        std::map<int, std::pair<IComponent*, size_t>> _links;

        std::ofstream _logFile;

    public:
        Logger();

        void simulate(size_t tick) override;

        Tristate compute(size_t pin) override;
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
    };
}

#define CREATE_LOGGER std::make_unique<Logger>();
