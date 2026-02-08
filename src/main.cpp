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
        nts::Circuit new_circuit = parser.loadCircuit(argc, argv);

        new_circuit.display();
        new_circuit.simulate();
        new_circuit.display();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
