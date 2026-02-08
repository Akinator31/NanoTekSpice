//
// Created by pavel on 08/02/2026.
//

#include "Utils.h++"

namespace nts
{
    std::string Utils::trim(const std::string& to_clean)
    {
        const auto start = to_clean.find_first_not_of(" \n\t");

        if (start == std::string::npos)
            return "";
        const auto end = to_clean.find_last_not_of(" \n\t");
        return to_clean.substr(start, end - start + 1);
    }

    bool Utils::is_valid_whitespace(const std::string& to_check)
    {
        for (const char c : to_check)
        {
            if (std::isspace(c) && (c == '\n' || c == '\t' || c == ' '))
            {
                continue;
            }
            if (!std::isspace(c))
                continue;
            return false;
        }
        return true;
    }
}
