//
// Created by pavel on 08/02/2026.
//

#include "NanoTekSpiceErrors.h++"

namespace nts {
    NanoTekSpiceException::NanoTekSpiceException(const ErrorType type) {
        this->_error = this->_error_map[type];
    }

    const char* NanoTekSpiceException::what() const noexcept {
        return this->_error.c_str();
    }
}
