//
// Created by pavel on 09/02/2026.
//

#pragma once
#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts
{
    class True : public AComponent
    {
    public:
        True() : AComponent(1, Other)
        {
        };

        /**
         * @brief Compute the result on the selected pin. Here, we always return Tristate::True;
         * @param pin Pin to know which 'interior component' computes the result. Useless here because True component has only one pin.
         * @return nts::Tristate The computed result, so here, just Tristate::True.
         */
        Tristate compute(size_t pin) override;
    };
}
