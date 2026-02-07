//
// Created by pavel on 07/02/2026. Le mec est out.
//

#pragma once
#include "IComponent.h++"

namespace nts
{
    class Out: public IComponent
    {
        size_t _pin = 0;
        Tristate _currentState = Undefined;
        ComponentLink _link;

    public:
        void simulate(size_t tick) override;
        Tristate compute(size_t pin) override;
        void setLink(size_t pin, IComponent& other, size_t otherPin) override;
        [[nodiscard]] ComponentLink getLink() const;
        [[nodiscard]] Tristate getValue() const;
    };
}
