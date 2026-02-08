//
// Created by pavel on 08/02/2026.
//

#pragma once
#include <exception>
#include <string>

namespace nts
{
    class NoFileException : public std::exception
    {
        std::string _message;

    public:
        NoFileException();
        [[nodiscard]] const char* what() const noexcept override;
    };

    class TooMuchArgumentsException : public std::exception
    {
        std::string _message;

    public:
        TooMuchArgumentsException();
        [[nodiscard]] const char* what() const noexcept override;
    };
}
