//
// Created by pavel on 10/02/2026.
//

#pragma once
#include <functional>
#include <map>

#include "IComponent.h++"
#include "Components/ElementaryComponents/AndGate.h++"

namespace nts
{
    class FourAndGates : public IComponent
    {
        std::vector<std::unique_ptr<IComponent>> _andGates;

    public:
        /**
         * 4081 gate constructor
         */
        FourAndGates();

        /**
         * @brief Simulate a tick of an AndGate component
         * @param tick The global tick of the circuit
         * @see nts::Circuit
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Compute the result on the selected pin.
         * @param pin Pin to know which 'interior component' computes the result.
         * @return nts::Tristate The computed result.
         */
        Tristate compute(std::size_t pin) override;

        /**
         * @brief Link a pin of another component.
         * @param pin Pin of the AndGate component.
         * @param other Component to linked
         * @param otherPin Pin of the component to linked
         */
        void setLink(std::size_t pin, IComponent& other, std::size_t otherPin) override;

        [[nodiscard]] std::function<Tristate (IComponent*, size_t)> createFunc(size_t pin) const;
    };
}
