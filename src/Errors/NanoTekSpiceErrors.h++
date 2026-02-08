//
// Created by pavel on 08/02/2026.
//

#pragma once
#include <exception>
#include <map>
#include <string>

namespace nts
{
    enum ErrorType
    {
        NoFileException,
        TooMuchArguments,
    };

    class NanoTekSpiceException : public std::exception
    {
        std::map<ErrorType, std::string> _error_map = {
            { NoFileException, "No file was given as parameter!" },
            { TooMuchArguments, "Too much arguments was given as parameters!" },
        };

        std::string _error;

    public:
        explicit NanoTekSpiceException(ErrorType type);
        [[nodiscard]] const char* what() const noexcept override;
    };
}
