//
// Created by pavel on 09/02/2026.
//

#pragma once
#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
    class False : public AComponent {
    public:
        False();

        Tristate compute(size_t pin) override;
    };
}

#define CREATE_FALSE std::make_unique<class False>();
