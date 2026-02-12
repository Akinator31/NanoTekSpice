//
// Created by pavel on 08/02/2026.
//

#pragma once

#include <functional>

#include "Circuit/Circuit.h++"

namespace nts {
    /**
     * @brief Parser class that extract chipsets and links from NTS file.
     */
    class Parser {
    public:
        /**
         * Enum that define available parser modes.
         */
        enum ParserMode { UNDEFINED, CHIPSET, LINKS };

        /**
         * @brief Default constructor for Parser class.
         */
        Parser() = default;

        /**
         * Retrieve all chipsets and links from NTS file.
         * @param argc Number of arguments
         * @param argv List of arguments
         * @return The circuit with all chipsets and links extracted from NTS file.
         */
        Circuit loadCircuit(int argc, char** argv);

    private:
        /**
         * Parse all chipsets from NTS file.
         * @param circuit The circuit where the extracted chipsets will be stored.
         * @param line The line to parse.
         */
        static void parseChipsets(Circuit& circuit, const std::string& line);

        /**
         * Parse all links from NTS file.
         * @param circuit The circuit where the extracted links will be stored.
         * @param line The line to parse.
         */
        static void parseLinks(Circuit& circuit, std::string& line);

        /**
         * Handle an undefined parser mode. IN other words, if the parser mode is undefined, there is an error in the NTS file.
         * @param circuit The circuit where the extracted links will be stored.
         * @param line The line to parse.
         */
        static void handleUndefinedParserMode(Circuit& circuit, std::string& line);

        ///< Map for store parsing function
        std::map<ParserMode, std::function<void(Circuit&, std::string&)>> _parseFunctions = {
            { CHIPSET, parseChipsets },
            { LINKS, parseLinks },
            { UNDEFINED, handleUndefinedParserMode },
        };
    };
}
