//
// Created by pavel on 08/02/2026.
//

#include "Parser.h++"

#include <fstream>

#include "Errors/NanoTekSpiceErrors.h++"

namespace nts
{
    Circuit Parser::loadCircuit(const int argc, char** argv)
    {
        if (argc < 2)
            throw NanoTekSpiceException(NoFileException);
        if (argc > 2)
            throw NanoTekSpiceException(TooMuchArgumentsException);

        std::string line;
        std::ifstream configurationFile(argv[1]);

        if (!configurationFile.is_open())
            throw NanoTekSpiceException(FileOpenException);

        return Circuit{};
    }
}
