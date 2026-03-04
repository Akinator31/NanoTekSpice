//
// Created by pavel on 03/03/2026.
//

#include "Ram.h++"

#include <iostream>
#include <ranges>

#include "Components/SpecialComponents/Input.h++"
#include "Components/SpecialComponents/Out.h++"
#include "Errors/NanoTekSpiceErrors.h++"

namespace nts {
    Ram::Ram() : AComponent(24, Other) {
        this->_memory.assign(1024, {
                                 Undefined, Undefined, Undefined, Undefined,
                                 Undefined, Undefined, Undefined, Undefined
                             });

        this->_links = {};
    }

    Tristate Ram::getInputOnPin(const size_t pin) {
        for (auto& [component, componentPin] : this->_links[pin]) {
            if (component->getType() != OutComponent)
                return component->compute(componentPin);
        }
        return Undefined;
    }

    int Ram::getAddress() {
        constexpr std::array<int, 10> addr_pins = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};
        int address = 0;

        address = getInputOnPin(addr_pins[0]) * 512 + getInputOnPin(addr_pins[1]) * 256 +
            getInputOnPin(addr_pins[2]) * 128 + getInputOnPin(addr_pins[3])
            * 64 + getInputOnPin(addr_pins[4]) * 32 +
            getInputOnPin(addr_pins[5]) * 16 + getInputOnPin(addr_pins[6]) * 8 + getInputOnPin(addr_pins[7]) * 4 +
            getInputOnPin(addr_pins[8]) * 2 + getInputOnPin(addr_pins[9]);

        return address;
    }

    void Ram::writeToMemory(const int address) {
        const std::vector inputs = {
            this->getInputOnPin(DQ0),
            this->getInputOnPin(DQ1),
            this->getInputOnPin(DQ2),
            this->getInputOnPin(DQ3),
            this->getInputOnPin(DQ4),
            this->getInputOnPin(DQ5),
            this->getInputOnPin(DQ6),
            this->getInputOnPin(DQ7),
        };

        const std::array value = {
            inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6], inputs[7]
        };

        this->_memory[address] = value;
    }

    void Ram::simulate(const size_t tick) {
        this->_lastSimulatedTick = tick;

        for (size_t i = 0; i < 24; i++) {
            if (this->_links.contains(i)) {
                for (const auto& key : this->_links[i] | std::views::keys)
                    key->simulate(tick);
            }
        }

        const Tristate notCE = this->getInputOnPin(NOT_CE);
        const Tristate notWE = this->getInputOnPin(NOT_WE);

        if (const int address = this->getAddress(); notCE == False && notWE == False && address >= 0 && address <
            1024) {
            writeToMemory(address);
        }
    }

    Tristate Ram::compute(const size_t pin) {
        if (!(pin >= DQ0 && pin <= DQ2) && !(pin >= DQ3 && pin <= DQ7))
            throw NanoTekSpiceException(SyntaxFileException);

        const Tristate notCE = this->getInputOnPin(NOT_CE);
        const Tristate notOE = this->getInputOnPin(NOT_OE);
        const Tristate notWE = this->getInputOnPin(NOT_WE);
        const int address = this->getAddress();

        if (notCE == False && notOE == False && notWE == True && address >= 0 && address <= 1024) {
            if (pin <= DQ2)
                return this->_memory[address][pin - 9];
            return this->_memory[address][pin - 10];
        }
        return Undefined;
    }

    void Ram::setLink(const size_t pin, IComponent& other, size_t otherPin) {
        if (pin == 0 || pin > _maxPins)
            throw NanoTekSpiceException(SyntaxFileException);
        this->_links[pin].emplace_back(&other, otherPin);
    }
}
