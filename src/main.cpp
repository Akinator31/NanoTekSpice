//
// Created by pavel on 06/02/2026.
//

#include <iostream>

#include "Circuit/Circuit.h++"
#include "Factory/Factory.h++"
#include "Parser/Parser.h++"

int main(const int argc, char** argv)
{
    try
    {
        nts::Parser parser;
        nts::Circuit circuit = parser.loadCircuit(argc, argv);

        circuit.startCli();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
