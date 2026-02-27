//
// Created by pavel on 26/02/2026.
//

#include "Logger.h++"
#include "Components/AComponent.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "Factory/Factory.h++"

namespace nts {
    Logger::Logger() : AComponent(10, Other), _logFile("log.bin", std::ios::binary | std::ios::app) {
        this->_clockPrevState = Undefined;
    }

    void Logger::simulate([[maybe_unused]] const size_t tick) {
        if (!this->_links.contains(CLOCK) || !this->_links.contains(INHIBIT))
            return;

        const Tristate clockNow = this->_links[CLOCK].first->compute(1);
        const Tristate inhibit = this->_links[INHIBIT].first->compute(1);

        if (this->_clockPrevState == False && clockNow == True && inhibit == False) {
            bool isValid = true;
            unsigned char result = 0;

            for (size_t i = 1; i < 9; i++) {
                if (!this->_links.contains(static_cast<int>(i))) {
                    isValid = false;
                    break;
                }

                const Tristate value = this->_links[static_cast<int>(i)].first->compute(1);

                if (value == Undefined) {
                    isValid = false;
                    break;
                }
                if (value == True)
                    result |= 1 << (i - 1);
            }

            if (isValid) {
                _logFile.put(static_cast<char>(result));
                _logFile.flush();
            }
        }

        this->_clockPrevState = clockNow;
    }

    Tristate Logger::compute([[maybe_unused]] const size_t pin) {
        throw NanoTekSpiceException(SyntaxFileException);
    }

    void Logger::setLink(const size_t pin, IComponent& other, const size_t otherPin) {
        this->_links[pin] = {&other, otherPin};
    }
}
