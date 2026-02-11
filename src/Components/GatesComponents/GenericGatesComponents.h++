//
// Created by pavel on 10/02/2026.
//

#pragma once
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "IComponent.h++"

namespace nts
{
    /**
     * Structure that describe information for a specific pin in a component
     * @see GenericGatesComponents
     */
    struct ComponentMapping
    {
        int gateIndex;
        int internalPin;
    };

    /**
     * Generic class for create GatesComponent
     */
    class GenericGatesComponents : public IComponent
    {
        std::vector<std::unique_ptr<IComponent>> _gates; ///< Vector that stored gates of a component.
        std::map<int, ComponentMapping> _mapping; ///< Map that describe "pinout" of a component.

    public:
        /**
         * Constructor for generic Gates Components
         * @param type The gate type you want in the component ("and" for component 4081 for example).
         * @param count The number of gate you want in the component (4 for compoment 4081 for example).
         * @param mapping The mapping for reference Pin, Gate index and internal pin of the component.
         */
        GenericGatesComponents(const std::string& type, size_t count, const std::map<int, ComponentMapping>& mapping);

        /**
         * @brief Simulate a tick of a component
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

        /**
         * Function that generates a function allowing you to perform a setLink() or a compute() on the component.
         * @details To perform a setLink() with the generated function, specify the component you want to link and its pin.
         * @details To perform a compute() with the generated function, specify `null_ptr` for the component and 0 for the pin (parameters doesn't matter in this case).
         * @param pin
         * @return
         */
        [[nodiscard]] std::function<Tristate (IComponent*, size_t)> createFunc(size_t pin);
    };
}

static const std::map<int, nts::ComponentMapping> FOUR_AND_GATES_MAPPING {
    {1, {0, 2}},
    {2, {0, 1}},
    {3, {0, 3}},
    {4, {1, 3}},
    {5, {1, 1}},
    {6, {1, 2}},
    {8, {2, 1}},
    {9, {2, 2}},
    {10, {2, 3}},
    {11, {3, 3}},
    {12, {3, 2}},
    {13, {3, 1}},
};

///< Macros that allow you to create gates component easily
#define CREATE_4081 std::make_unique<GenericGatesComponents>("and", 4, FOUR_AND_GATES_MAPPING)
