//
// Created by pavel on 08/02/2026.
//

#pragma once
#include <map>
#include <string>

#include "IComponent.h++"


namespace nts
{
    /**
     * Utils class used for group all functions that we use often in the program.
     */
    class Utils
    {
    public:
        /**
         * Remove spaces, line breaks or tabs from a string.
         * @param to_clean The string to clean
         * @return The string cleaned
         */
        static std::string trim(const std::string& to_clean);

        /**
         * Check if a string is only composed of \\n or \\t or spaces.
         * @param to_check The string to check.
         * @return bool The result of the check.
         */
        static bool is_valid_whitespace(const std::string& to_check);

        /**
         * Convert a string tristate to real tristate
         * @param value String that contain the tristate to be parsed
         * @return The parsed tristate
         */
        static Tristate stringToTristate(const std::string& value);
    };
}
