//
// Created by pavel on 08/02/2026.
//

#include "Utils.h++"

#include <iostream>

#include "Errors/NanoTekSpiceErrors.h++"

namespace nts {
    std::string Utils::trim(const std::string& to_clean) {
        const auto start = to_clean.find_first_not_of(" \n\t");

        if (start == std::string::npos)
            return "";
        const auto end = to_clean.find_last_not_of(" \n\t");
        return to_clean.substr(start, end - start + 1);
    }

    bool Utils::is_valid_whitespace(const std::string& to_check) {
        for (const char c : to_check) {
            if (std::isspace(c) && (c == '\n' || c == '\t' || c == ' ')) {
                continue;
            }
            if (!std::isspace(c))
                continue;
            return false;
        }
        return true;
    }

    Tristate Utils::stringToTristate(const std::string& value) {
        std::map<std::string, Tristate> tristateString = {
            {"0", False},
            {"1", True},
            {"U", Undefined},
        };

        if (!tristateString.contains(value))
            throw NanoTekSpiceException(InvalidValue);
        return tristateString[value];
    }

    Tristate operator!(const Tristate value) {
        if (value == False)
            return True;
        if (value == True)
            return False;
        return Undefined;
    }

    Tristate operator&&(const Tristate first, const Tristate second) {
        if (first == true && second == true)
            return True;
        if (first == Undefined && second == Undefined)
            return Undefined;
        if (first == true || second == true) {
            if (first == Undefined || second == Undefined) {
                return Undefined;
            }
            return False;
        }
        return False;
    }

    Tristate operator||(const Tristate first, const Tristate second) {
        if (first == False && second == False)
            return False;
        if (first == Undefined && second == Undefined)
            return Undefined;
        if (first == Undefined && second == False)
            return Undefined;
        if (first == False && second == Undefined)
            return Undefined;
        return True;
    }

    Tristate operator^(Tristate first, Tristate second) {
        if (first == True && second == False)
            return True;
        if (first == False && second == True)
            return True;
        if (first == Undefined || second == Undefined)
            return Undefined;
        return False;
    }

    std::ostream& operator<<(std::ostream& stream, const Tristate value) {
        if (value == Undefined)
            return stream << "U";
        if (value == True)
            return stream << 1;
        return stream << 0;
    }
}
