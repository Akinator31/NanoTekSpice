//
// Created by pavel on 08/02/2026.
//

#pragma once
#include <exception>
#include <map>
#include <string>

namespace nts {
    /**
     * @brief Enum that describe all possible exceptions for NanoTekSpice.
     */
    enum ErrorType {
        NoFileException,
        TooMuchArgumentsException,
        FileOpenException,
        SyntaxFileException,
        ComponentTypeException,
        ComponentAlreadyExistException,
        ComponentNameException,
        InvalidValue
    };

    /**
     * @brief NanoTekSpice Exceptions class.
     */
    class NanoTekSpiceException : public std::exception {
        ///< Error map for store all exception messages.
        std::map<ErrorType, std::string> _error_map = { { NoFileException, "No file was given as parameter!" },
                                                        { TooMuchArgumentsException, "Too much arguments was given as parameters!" },
                                                        { FileOpenException, "Impossible to open the given file!" },
                                                        { SyntaxFileException,
                                                          "The circuit file includes one or several lexical or syntactic errors!" },
                                                        { ComponentTypeException, "A component type is unknown!" },
                                                        { ComponentAlreadyExistException, "Several components share the same name!" },
                                                        { ComponentNameException, "A component name is unknown!" },
                                                        { InvalidValue, "Invalid value when using input=value command!" } };

        ///< String that represent the exception
        std::string _error;

    public:
        /**
         * NanoTekSpiceException constructor. Store the exception into the _error string for what() method.
         * @param type Error type
         */
        explicit NanoTekSpiceException(ErrorType type);
        [[nodiscard]] const char* what() const noexcept override;
    };
}
