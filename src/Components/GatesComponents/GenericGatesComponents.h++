//
// Created by pavel on 10/02/2026.
//

#pragma once
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "IComponent.h++"
#include "Components/AComponent.h++"

namespace nts {
    /**
     * Structure that describe information for a specific pin in a component
     * @see GenericGatesComponents
     */
    struct ComponentMapping {
        int gateIndex;
        int internalPin;
    };

    /**
     * Generic class for create GatesComponent
     */
    class GenericGatesComponents : public AComponent {
        std::vector<std::unique_ptr<IComponent>> _gates; ///< Vector that stored gates of a component.
        std::map<int, ComponentMapping> _mapping; ///< Map that describe "pinout" of a component.

    public:
        /**
         * Constructor for generic Gates Components
         * @param _numberOfPins The component's number of pins
         * @param type The gate type you want in the component ("and" for component 4081 for
         * example).
         * @param count The number of gate you want in the component (4 for component 4081 for
         * example).
         * @param mapping The mapping for reference Pin, Gate index and internal pin of the
         * component.
         */
        GenericGatesComponents(size_t _numberOfPins, const std::string& type, size_t count,
                               const std::map<int, ComponentMapping>& mapping);

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
         * Function that generates a function allowing you to perform a setLink() or a compute() on
         * the component.
         * @details To perform a setLink() with the generated function, specify the component you
         * want to link and its pin.
         * @details To perform a compute() with the generated function, specify `null_ptr` for the
         * component and 0 for the pin (parameters doesn't matter in this case).
         * @param pin
         * @return
         */
        [[nodiscard]] std::function<Tristate(IComponent*, size_t)> createFunc(size_t pin);
    };
}

static const std::map<int, nts::ComponentMapping> FOUR_THREE_COMPONENT_GATES{
    {1, {0, 2}}, {2, {0, 1}}, {3, {0, 3}}, {4, {1, 3}}, {5, {1, 2}}, {6, {1, 1}},
    {8, {2, 2}}, {9, {2, 1}}, {10, {2, 3}}, {11, {3, 3}}, {12, {3, 2}}, {13, {3, 1}},
};

static const std::map<int, nts::ComponentMapping> SIX_TWO_COMPONENT_GATES{
    {1, {0, 1}}, {2, {0, 2}}, {3, {1, 1}}, {4, {1, 2}}, {5, {2, 1}}, {6, {2, 2}},
    {8, {5, 2}}, {9, {5, 1}}, {10, {4, 2}}, {11, {4, 1}}, {12, {3, 2}}, {13, {3, 1}},
};

///< Macros that allow you to create gates component easily
#define CREATE_4001 std::make_unique<GenericGatesComponents>(14, "nor", 4, FOUR_THREE_COMPONENT_GATES)
#define CREATE_4011 std::make_unique<GenericGatesComponents>(14, "nand", 4, FOUR_THREE_COMPONENT_GATES)
#define CREATE_4030 std::make_unique<GenericGatesComponents>(14, "xor", 4, FOUR_THREE_COMPONENT_GATES)
#define CREATE_4069 std::make_unique<GenericGatesComponents>(14, "not", 6, SIX_TWO_COMPONENT_GATES)
#define CREATE_4071 std::make_unique<GenericGatesComponents>(14, "or", 4, FOUR_THREE_COMPONENT_GATES)
#define CREATE_4081 std::make_unique<GenericGatesComponents>(14, "and", 4, FOUR_THREE_COMPONENT_GATES)
