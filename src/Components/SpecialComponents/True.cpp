//
// Created by pavel on 09/02/2026.
//

#include "True.h++"
#include "Errors/NanoTekSpiceErrors.h++"
#include "IComponent.h++"

namespace nts
{
    Tristate True::compute([[maybe_unused]] size_t pin)
    {
        return Tristate::True;
    }
}
