//
// Created by pavel on 08/02/2026.
//

#pragma once

#include "IComponent.h++"
#include "Circuit/Circuit.h++"

namespace nts
{
    class Parser
    {
    public:
        static Circuit loadCircuit(int argc, char **argv);
    };
}
