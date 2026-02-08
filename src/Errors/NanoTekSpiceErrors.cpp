//
// Created by pavel on 08/02/2026.
//

#include "NanoTekSpiceErrors.h++"

namespace nts
{
    NoFileException::NoFileException()
    {
        this->_message = "No file was given as parameter!";
    }

    const char* NoFileException::what() const noexcept
    {
        return this->_message.c_str();
    }

    TooMuchArgumentsException::TooMuchArgumentsException()
    {
        this->_message = "Too much arguments was given as parameters!";
    }

    const char* TooMuchArgumentsException::what() const noexcept
    {
        return this->_message.c_str();
    }
}
