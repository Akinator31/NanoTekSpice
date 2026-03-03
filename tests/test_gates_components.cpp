
#include <criterion/criterion.h>

#include "IComponent.h++"
#include "Components/GatesComponents/GenericGatesComponents.h++"
#include "Components/SpecialComponents/True.h++"
#include "Components/SpecialComponents/False.h++"
#include "Components/SpecialComponents/Input.h++"

using namespace nts;

static void setupTwoInputGate(IComponent& gate, Input& a, Input& b,
                              size_t pinA, size_t pinB, Tristate valA, Tristate valB) {
    a.setValue(valA);
    a.simulate(1);
    b.setValue(valB);
    b.simulate(1);
    gate.setLink(pinA, a, 1);
    gate.setLink(pinB, b, 1);
    gate.simulate(1);
}

Test(Gate4081, gate0_true_and_true) {
    auto gate = CREATE_4081;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, True, True);
    cr_assert_eq(gate->compute(3), True);
}

Test(Gate4081, gate0_true_and_false) {
    auto gate = CREATE_4081;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, True, False);
    cr_assert_eq(gate->compute(3), False);
}

Test(Gate4081, gate0_false_and_false) {
    auto gate = CREATE_4081;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, False, False);
    cr_assert_eq(gate->compute(3), False);
}

Test(Gate4081, gate1_true_and_true) {
    auto gate = CREATE_4081;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 5, 6, True, True);
    cr_assert_eq(gate->compute(4), True);
}

Test(Gate4081, gate2_false_and_true) {
    auto gate = CREATE_4081;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 8, 9, False, True);
    cr_assert_eq(gate->compute(10), False);
}

Test(Gate4081, gate3_true_and_true) {
    auto gate = CREATE_4081;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 12, 13, True, True);
    cr_assert_eq(gate->compute(11), True);
}

Test(Gate4071, gate0_false_or_false) {
    auto gate = CREATE_4071;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, False, False);
    cr_assert_eq(gate->compute(3), False);
}

Test(Gate4071, gate0_true_or_false) {
    auto gate = CREATE_4071;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, True, False);
    cr_assert_eq(gate->compute(3), True);
}

Test(Gate4071, gate0_false_or_true) {
    auto gate = CREATE_4071;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, False, True);
    cr_assert_eq(gate->compute(3), True);
}

Test(Gate4071, gate0_true_or_true) {
    auto gate = CREATE_4071;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, True, True);
    cr_assert_eq(gate->compute(3), True);
}

Test(Gate4001, gate0_false_nor_false) {
    auto gate = CREATE_4001;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, False, False);
    cr_assert_eq(gate->compute(3), True);
}

Test(Gate4001, gate0_true_nor_false) {
    auto gate = CREATE_4001;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, True, False);
    cr_assert_eq(gate->compute(3), False);
}

Test(Gate4001, gate0_true_nor_true) {
    auto gate = CREATE_4001;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, True, True);
    cr_assert_eq(gate->compute(3), False);
}

Test(Gate4011, gate0_true_nand_true) {
    auto gate = CREATE_4011;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, True, True);
    cr_assert_eq(gate->compute(3), False);
}

Test(Gate4011, gate0_true_nand_false) {
    auto gate = CREATE_4011;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, True, False);
    cr_assert_eq(gate->compute(3), True);
}

Test(Gate4011, gate0_false_nand_false) {
    auto gate = CREATE_4011;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, False, False);
    cr_assert_eq(gate->compute(3), True);
}

Test(Gate4030, gate0_true_xor_true) {
    auto gate = CREATE_4030;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, True, True);
    cr_assert_eq(gate->compute(3), False);
}

Test(Gate4030, gate0_true_xor_false) {
    auto gate = CREATE_4030;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, True, False);
    cr_assert_eq(gate->compute(3), True);
}

Test(Gate4030, gate0_false_xor_true) {
    auto gate = CREATE_4030;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, False, True);
    cr_assert_eq(gate->compute(3), True);
}

Test(Gate4030, gate0_false_xor_false) {
    auto gate = CREATE_4030;
    Input a, b;
    setupTwoInputGate(*gate, a, b, 1, 2, False, False);
    cr_assert_eq(gate->compute(3), False);
}

Test(Gate4069, gate0_not_true) {
    auto gate = CREATE_4069;
    Input a;
    a.setValue(True);
    a.simulate(1);
    gate->setLink(1, a, 1);
    gate->simulate(1);
    cr_assert_eq(gate->compute(2), False);
}

Test(Gate4069, gate0_not_false) {
    auto gate = CREATE_4069;
    Input a;
    a.setValue(False);
    a.simulate(1);
    gate->setLink(1, a, 1);
    gate->simulate(1);
    cr_assert_eq(gate->compute(2), True);
}

Test(Gate4069, gate1_not_true) {
    auto gate = CREATE_4069;
    Input a;
    a.setValue(True);
    a.simulate(1);
    gate->setLink(3, a, 1);
    gate->simulate(1);
    cr_assert_eq(gate->compute(4), False);
}

Test(Gate4069, gate2_not_false) {
    auto gate = CREATE_4069;
    Input a;
    a.setValue(False);
    a.simulate(1);
    gate->setLink(5, a, 1);
    gate->simulate(1);
    cr_assert_eq(gate->compute(6), True);
}

Test(Gate4081, all_four_gates) {
    auto gate = CREATE_4081;
    Input a1, b1, a2, b2, a3, b3, a4, b4;

    a1.setValue(True);
    b1.setValue(True);
    a2.setValue(True);
    b2.setValue(False);
    a3.setValue(False);
    b3.setValue(True);
    a4.setValue(False);
    b4.setValue(False);

    a1.simulate(1);
    b1.simulate(1);
    a2.simulate(1);
    b2.simulate(1);
    a3.simulate(1);
    b3.simulate(1);
    a4.simulate(1);
    b4.simulate(1);

    gate->setLink(1, a1, 1);
    gate->setLink(2, b1, 1);
    gate->setLink(5, a2, 1);
    gate->setLink(6, b2, 1);
    gate->setLink(8, a3, 1);
    gate->setLink(9, b3, 1);
    gate->setLink(12, a4, 1);
    gate->setLink(13, b4, 1);

    gate->simulate(1);

    cr_assert_eq(gate->compute(3), True);
    cr_assert_eq(gate->compute(4), False);
    cr_assert_eq(gate->compute(10), False);
    cr_assert_eq(gate->compute(11), False);
}

Test(Gate4081, simulate_updates_tick) {
    auto gate = CREATE_4081;
    Input a, b;
    a.setValue(True);
    b.setValue(True);
    a.simulate(1);
    b.simulate(1);
    gate->setLink(1, a, 1);
    gate->setLink(2, b, 1);
    gate->simulate(1);
    cr_assert_eq(gate->compute(3), True);

    a.setValue(False);
    a.simulate(2);
    gate->simulate(2);
    cr_assert_eq(gate->compute(3), False);
}

