//
// Created by pavel on 08/02/2026.
//

#pragma once
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

    /**
     * Perform a NOT on a Tristate
     * @param value Value to invert
     * @return Result
     */
    Tristate operator!(Tristate value);

    /**
     * Perform an AND on two Tristate
     * @param first First value
     * @param second Second value
     * @return Result
     */
    Tristate operator&&(Tristate first, Tristate second);

    /**
     * Perform an OR on two Tristate
     * @param first First value
     * @param second Second value
     * @return Result
     */
    Tristate operator||(Tristate first, Tristate second);

    /**
     * Perform a XOR on two Tristate.
     * @param first First value
     * @param second Second value
     * @return Result
     */
    Tristate operator^(Tristate first, Tristate second);

    /**
     * Allow you to print a Tristate through an ostream
     * @param stream The stream
     * @param value The Tristate you want to print
     * @return Result
     */
    std::ostream& operator<<(std::ostream& stream, Tristate value);
}
