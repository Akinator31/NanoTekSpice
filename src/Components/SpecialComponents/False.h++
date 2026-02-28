//
// Created by pavel on 09/02/2026.
//

#pragma once
#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
    /**
     * Class for the False component
     */
    class False : public AComponent {
    public:
        /**
         * False constructor
         */
        False();

        /**
         * @brief Compute the result on the selected pin. Here, we always return Tristate::False;
         * @param pin Pin to know which 'interior component' computes the result. Useless here because False component has only one pin.
         * @return nts::Tristate The computed result, so here, just Tristate::False.
         */
        Tristate compute(size_t pin) override;
    };
}

///< Macro used for create a False easily
#define CREATE_FALSE std::make_unique<class False>();
