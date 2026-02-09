//
// Created by pavel on 08/02/2026.
//

#include "Parser.h++"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Errors/NanoTekSpiceErrors.h++"
#include "Factory/Factory.h++"
#include "Utils/Utils.h++"

namespace nts
{
    void Parser::parseChipsets(Circuit& circuit, const std::string& line)
    {
        const std::string trimmedString = Utils::trim(line);
        std::stringstream lineStream(trimmedString);

        std::string extractedWord;
        std::string chipsetType;
        std::string chipsetName;

        if (!Utils::is_valid_whitespace(trimmedString))
            throw NanoTekSpiceException(SyntaxFileException);

        while (lineStream >> extractedWord)
        {
            if (chipsetType.empty())
            {
                chipsetType = extractedWord;
                continue;
            }
            if (chipsetName.empty())
            {
                chipsetName = extractedWord;
                continue;
            }

            if (extractedWord.starts_with("#"))
                break;

            if (!chipsetType.empty() && !chipsetName.empty())
                throw NanoTekSpiceException(SyntaxFileException);
        }

        Factory factory;
        std::unique_ptr<IComponent> component = factory.createComponent(chipsetType);

        if (component == nullptr)
            throw NanoTekSpiceException(ComponentTypeException);

        if (!circuit.addComponent(chipsetName, std::move(component)))
            throw NanoTekSpiceException(ComponentAlreadyExistException);
    }
}
