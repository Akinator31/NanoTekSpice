
#include <criterion/criterion.h>

#include "IComponent.h++"
#include "Factory/Factory.h++"
#include "Components/SpecialComponents/Input.h++"

using namespace nts;

static Tristate testBinaryGate(const std::string& type, Tristate a, Tristate b) {
    Input inA, inB;
    inA.setValue(a);
    inA.simulate(1);
    inB.setValue(b);
    inB.simulate(1);

    Factory<> factory;
    auto gate = factory.createComponent(type);
    if (!gate)
        return Undefined;

    gate->setLink(1, inA, 1);
    gate->setLink(2, inB, 1);
    gate->simulate(1);
    return gate->compute(3);
}

static Tristate testNotGate(Tristate a) {
    Input inA;
    inA.setValue(a);
    inA.simulate(1);

    Factory<> factory;
    auto gate = factory.createComponent("not");

    gate->setLink(1, inA, 1);
    gate->simulate(1);
    return gate->compute(2);
}

Test(ElementaryAnd, true_and_true) {
    cr_assert_eq(testBinaryGate("and", True, True), True);
}

Test(ElementaryAnd, true_and_false) {
    cr_assert_eq(testBinaryGate("and", True, False), False);
}

Test(ElementaryAnd, false_and_true) {
    cr_assert_eq(testBinaryGate("and", False, True), False);
}

Test(ElementaryAnd, false_and_false) {
    cr_assert_eq(testBinaryGate("and", False, False), False);
}

Test(ElementaryAnd, true_and_undefined) {
    cr_assert_eq(testBinaryGate("and", True, Undefined), Undefined);
}

Test(ElementaryAnd, undefined_and_undefined) {
    cr_assert_eq(testBinaryGate("and", Undefined, Undefined), Undefined);
}

Test(ElementaryOr, true_or_true) {
    cr_assert_eq(testBinaryGate("or", True, True), True);
}

Test(ElementaryOr, true_or_false) {
    cr_assert_eq(testBinaryGate("or", True, False), True);
}

Test(ElementaryOr, false_or_true) {
    cr_assert_eq(testBinaryGate("or", False, True), True);
}

Test(ElementaryOr, false_or_false) {
    cr_assert_eq(testBinaryGate("or", False, False), False);
}

Test(ElementaryOr, false_or_undefined) {
    cr_assert_eq(testBinaryGate("or", False, Undefined), Undefined);
}

Test(ElementaryXor, true_xor_true) {
    cr_assert_eq(testBinaryGate("xor", True, True), False);
}

Test(ElementaryXor, true_xor_false) {
    cr_assert_eq(testBinaryGate("xor", True, False), True);
}

Test(ElementaryXor, false_xor_true) {
    cr_assert_eq(testBinaryGate("xor", False, True), True);
}

Test(ElementaryXor, false_xor_false) {
    cr_assert_eq(testBinaryGate("xor", False, False), False);
}

Test(ElementaryXor, undefined_xor) {
    cr_assert_eq(testBinaryGate("xor", True, Undefined), Undefined);
}

Test(ElementaryNot, not_true) {
    cr_assert_eq(testNotGate(True), False);
}

Test(ElementaryNot, not_false) {
    cr_assert_eq(testNotGate(False), True);
}

Test(ElementaryNot, not_undefined) {
    cr_assert_eq(testNotGate(Undefined), Undefined);
}

Test(ElementaryNor, true_nor_true) {
    cr_assert_eq(testBinaryGate("nor", True, True), False);
}

Test(ElementaryNor, true_nor_false) {
    cr_assert_eq(testBinaryGate("nor", True, False), False);
}

Test(ElementaryNor, false_nor_true) {
    cr_assert_eq(testBinaryGate("nor", False, True), False);
}

Test(ElementaryNor, false_nor_false) {
    cr_assert_eq(testBinaryGate("nor", False, False), True);
}

Test(ElementaryNor, undefined_nor) {
    cr_assert_eq(testBinaryGate("nor", Undefined, Undefined), Undefined);
}

Test(ElementaryNand, true_nand_true) {
    cr_assert_eq(testBinaryGate("nand", True, True), False);
}

Test(ElementaryNand, true_nand_false) {
    cr_assert_eq(testBinaryGate("nand", True, False), True);
}

Test(ElementaryNand, false_nand_true) {
    cr_assert_eq(testBinaryGate("nand", False, True), True);
}

Test(ElementaryNand, false_nand_false) {
    cr_assert_eq(testBinaryGate("nand", False, False), True);
}

Test(ElementaryNand, undefined_nand) {
    cr_assert_eq(testBinaryGate("nand", Undefined, Undefined), Undefined);
}

Test(ElementaryAnd, compute_wrong_pin_returns_undefined) {
    Input inA, inB;
    inA.setValue(True);
    inA.simulate(1);
    inB.setValue(True);
    inB.simulate(1);

    Factory<> factory;
    auto gate = factory.createComponent("and");
    gate->setLink(1, inA, 1);
    gate->setLink(2, inB, 1);
    gate->simulate(1);

    cr_assert_eq(gate->compute(1), Undefined);
}

Test(ElementaryNot, compute_wrong_pin_returns_undefined) {
    Input inA;
    inA.setValue(True);
    inA.simulate(1);

    Factory<> factory;
    auto gate = factory.createComponent("not");
    gate->setLink(1, inA, 1);
    gate->simulate(1);

    cr_assert_eq(gate->compute(1), Undefined);
}
