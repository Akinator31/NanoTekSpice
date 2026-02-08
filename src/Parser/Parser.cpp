//
// Created by pavel on 08/02/2026.
//

#include "Parser.h++"

#include <fstream>
#include <iostream>

#include "Errors/NanoTekSpiceErrors.h++"
#include "Factory/Factory.h++"
#include "Utils/Utils.h++"

namespace nts
{
    Circuit Parser::loadCircuit(const int argc, char** argv)
    {
        if (argc < 2)
            throw NanoTekSpiceException(NoFileException);
        if (argc > 2)
            throw NanoTekSpiceException(TooMuchArgumentsException);

        std::string line;
        std::ifstream ntsFile(argv[1]);

        if (!ntsFile.is_open())
            throw NanoTekSpiceException(FileOpenException);

        ParserMode mode = UNDEFINED;
        Circuit circuit;

        while (getline(ntsFile, line))
        {
            std::string trimmed_line = Utils::trim(line);

            if (trimmed_line.starts_with("#"))
                continue;
            if (trimmed_line.empty())
                continue;
            if (trimmed_line.starts_with(".chipsets:"))
            {
                mode = CHIPSET;
                continue;
            }
            if (trimmed_line.starts_with(".links:"))
            {
                mode = LINKS;
                continue;
            }
            this->_parseFunctions[mode](circuit, line);
        }

        ntsFile.close();

        if (mode == UNDEFINED || mode == CHIPSET)
            throw NanoTekSpiceException(SyntaxFileException);

        return circuit;
    }

    void Parser::handleUndefinedParserMode([[maybe_unused]] Circuit& circuit, [[maybe_unused]] std::string& line)
    {
        throw NanoTekSpiceException(SyntaxFileException);
    }
}
