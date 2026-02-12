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

namespace nts {
    std::vector<std::string> extractComponentNameAndPin(const std::string& component) {
        std::string segment;
        std::stringstream componentStream(component);
        std::vector<std::string> componentParts = {};

        while (getline(componentStream, segment, ':')) {
            if (componentStream.fail())
                throw NanoTekSpiceException(SyntaxFileException);
            componentParts.push_back(segment);
        }
        return componentParts;
    }

    void addLinks(Circuit& circuit, std::string& firstComponent, std::string& secondComponent) {
        std::stringstream firstStream(firstComponent);
        std::stringstream secondStream(secondComponent);

        std::vector firstComponentParts = extractComponentNameAndPin(firstComponent);
        std::vector secondComponentParts = extractComponentNameAndPin(secondComponent);

        if (firstComponentParts.size() > 2 || firstComponentParts.size() < 2 || secondComponentParts.size() > 2 || secondComponentParts.size() < 2)
            throw NanoTekSpiceException(SyntaxFileException);

        size_t firstComponentPin;
        size_t secondComponentPin;

        try {
            firstComponentPin = std::stoul(firstComponentParts[1]);
            secondComponentPin = std::stoul(secondComponentParts[1]);
        } catch ([[maybe_unused]] const std::invalid_argument& e) {
            throw NanoTekSpiceException(SyntaxFileException);
        } catch ([[maybe_unused]] const std::out_of_range& e) {
            throw NanoTekSpiceException(SyntaxFileException);
        }

        circuit.addLink(firstComponentParts[0], firstComponentPin, secondComponentParts[0], secondComponentPin);
    }

    void Parser::parseLinks([[maybe_unused]] Circuit& circuit, std::string& line) {
        const std::string trimmedString = Utils::trim(line);
        std::stringstream lineStream(trimmedString);

        std::string extractedWord;
        std::string firstComponent;
        std::string secondComponent;

        if (!Utils::is_valid_whitespace(trimmedString))
            throw NanoTekSpiceException(SyntaxFileException);

        while (lineStream >> extractedWord) {
            if (firstComponent.empty()) {
                firstComponent = extractedWord;
                continue;
            }
            if (secondComponent.empty()) {
                secondComponent = extractedWord;
                continue;
            }

            if (extractedWord.starts_with("#"))
                break;

            if (!firstComponent.empty() && !secondComponent.empty())
                throw NanoTekSpiceException(SyntaxFileException);
        }

        addLinks(circuit, firstComponent, secondComponent);
    }
}
