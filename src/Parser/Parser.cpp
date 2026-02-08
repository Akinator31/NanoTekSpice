//
// Created by pavel on 08/02/2026.
//

#include "Parser.h++"

#include "Errors/NanoTekSpiceErrors.h++"

namespace nts
{
    Circuit Parser::loadCircuit(const int argc, [[maybe_unused]] char** argv)
    {
        if (argc < 2)
            throw NanoTekSpiceException(NoFileException);
        if (argc > 2)
            throw NanoTekSpiceException(TooMuchArguments);
        return Circuit {};
    }
}
