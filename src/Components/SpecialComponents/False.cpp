//
// Created by pavel on 09/02/2026.
//

#include "False.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"

namespace nts
{
    False::False() : AComponent(1, Other)
    {
    }

    Tristate False::compute([[maybe_unused]] size_t pin)
    {
        return Tristate::False;
    }
}
