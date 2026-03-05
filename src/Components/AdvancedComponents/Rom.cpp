//
// Created by Noah on 02/03/2026.
//

#include "Components/AdvancedComponents/Rom.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"
#include "Utils/Utils.h++"
#include <fstream>
#include <vector>

namespace nts {
    Rom::Rom() : AComponent(24, Other) {
        std::ifstream file("./rom.bin", std::ios::binary);

        if (!file.is_open())
            throw NanoTekSpiceException(FileOpenException);
        std::vector<char> romData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        this->_romData = romData;
        file.close();
    }

    void Rom::simulate(size_t tick) {
        this->_lastSimulatedTick = tick;
    }

    void Rom::computeVal() {
        Tristate A10 = this->_connections[19].first->compute(this->_connections[19].second);
        Tristate A9 = this->_connections[22].first->compute(this->_connections[22].second);
        Tristate A8 = this->_connections[23].first->compute(this->_connections[23].second);
        Tristate A7 = this->_connections[1].first->compute(this->_connections[1].second);
        Tristate A6 = this->_connections[2].first->compute(this->_connections[2].second);
        Tristate A5 = this->_connections[3].first->compute(this->_connections[3].second);
        Tristate A4 = this->_connections[4].first->compute(this->_connections[4].second);
        Tristate A3 = this->_connections[5].first->compute(this->_connections[5].second);
        Tristate A2 = this->_connections[6].first->compute(this->_connections[6].second);
        Tristate A1 = this->_connections[7].first->compute(this->_connections[7].second);
        Tristate A0 = this->_connections[8].first->compute(this->_connections[8].second);
        size_t address = (A10 * 1024) + (A9 * 512) + (A8 * 256) + (A7 * 128) + (A6 * 64) + (A5 * 32) +
                         (A4 * 16) + (A3 * 8) + (A2 * 4) + (A1 * 2) + A0;

        if (A10 == Undefined || A9 == Undefined || A8 == Undefined || A7 == Undefined || A6 == Undefined ||
            A5 == Undefined || A4 == Undefined || A3 == Undefined || A2 == Undefined || A1 == Undefined ||
            A0 == Undefined) {
            this->_value = -1;
            return;
        }
        if (address >= this->_romData.size()) {
            this->_value = -1;
            return;
        }
        this->_value = static_cast<unsigned char>(this->_romData[address]);
    }

    Tristate Rom::compute(size_t pin) {
        if (pin > 24)
            throw NanoTekSpiceException(SyntaxFileException);
        Tristate CE = this->_connections[18].first->compute(this->_connections[18].second);
        Tristate OE = this->_connections[20].first->compute(this->_connections[20].second);

        if (CE == Undefined || OE == Undefined)
            return Undefined;
        if (CE == True || OE == True)
            return False;
        this->computeVal();
        if (this->_value == -1)
            return Undefined;
        if (pin >= 13 && pin <= 17)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(pin - 9, this->_value));
        if (pin >= 9 && pin <= 11)
            return static_cast<Tristate>(Utils::getBinaryValueIdx(pin - 8, this->_value));
        return Undefined;
    }
}
