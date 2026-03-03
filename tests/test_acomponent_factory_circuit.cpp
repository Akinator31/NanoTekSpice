
#include <criterion/criterion.h>

#include "IComponent.h++"
#include "Components/AComponent.h++"
#include "Components/SpecialComponents/Input.h++"
#include "Components/SpecialComponents/Out.h++"
#include "Components/SpecialComponents/True.h++"
#include "Components/SpecialComponents/False.h++"
#include "Components/SpecialComponents/Clock.h++"
#include "Factory/Factory.h++"
#include "Circuit/Circuit.h++"
#include "Errors/NanoTekSpiceErrors.h++"

using namespace nts;

Test(AComponent, setLink_invalid_pin_zero) {
    Out o;
    class True t;
    cr_assert_throw(o.setLink(0, t, 1), NanoTekSpiceException);
}

Test(AComponent, setLink_invalid_pin_too_large) {
    Out o;
    class True t;
    cr_assert_throw(o.setLink(2, t, 1), NanoTekSpiceException);
}

Test(AComponent, setLink_valid) {
    Out o;
    class True t;
    cr_assert_no_throw(o.setLink(1, t, 1), NanoTekSpiceException);
}

Test(AComponent, getType_input) {
    Input i;
    cr_assert_eq(i.getType(), InputComponent);
}

Test(AComponent, getType_output) {
    Out o;
    cr_assert_eq(o.getType(), OutComponent);
}

Test(AComponent, getType_clock) {
    Clock c;
    cr_assert_eq(c.getType(), ClockComponent);
}

Test(AComponent, getType_other) {
    class True t;
    cr_assert_eq(t.getType(), Other);
}

Test(AComponent, compute_no_connection_returns_undefined) {
    Out o;
    o.simulate(1);
    cr_assert_eq(o.compute(1), Undefined);
}

Test(Factory, create_input) {
    Factory<> f;
    auto comp = f.createComponent("input");
    cr_assert_not_null(comp.get());
    cr_assert_eq(comp->getType(), InputComponent);
}

Test(Factory, create_output) {
    Factory<> f;
    auto comp = f.createComponent("output");
    cr_assert_not_null(comp.get());
    cr_assert_eq(comp->getType(), OutComponent);
}

Test(Factory, create_true) {
    Factory<> f;
    auto comp = f.createComponent("true");
    cr_assert_not_null(comp.get());
    cr_assert_eq(comp->compute(1), True);
}

Test(Factory, create_false) {
    Factory<> f;
    auto comp = f.createComponent("false");
    cr_assert_not_null(comp.get());
    cr_assert_eq(comp->compute(1), False);
}

Test(Factory, create_clock) {
    Factory<> f;
    auto comp = f.createComponent("clock");
    cr_assert_not_null(comp.get());
    cr_assert_eq(comp->getType(), ClockComponent);
}

Test(Factory, create_and_gate) {
    Factory<> f;
    auto comp = f.createComponent("and");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_or_gate) {
    Factory<> f;
    auto comp = f.createComponent("or");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_xor_gate) {
    Factory<> f;
    auto comp = f.createComponent("xor");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_not_gate) {
    Factory<> f;
    auto comp = f.createComponent("not");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_nor_gate) {
    Factory<> f;
    auto comp = f.createComponent("nor");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_nand_gate) {
    Factory<> f;
    auto comp = f.createComponent("nand");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4001) {
    Factory<> f;
    auto comp = f.createComponent("4001");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4011) {
    Factory<> f;
    auto comp = f.createComponent("4011");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4030) {
    Factory<> f;
    auto comp = f.createComponent("4030");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4069) {
    Factory<> f;
    auto comp = f.createComponent("4069");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4071) {
    Factory<> f;
    auto comp = f.createComponent("4071");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4081) {
    Factory<> f;
    auto comp = f.createComponent("4081");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4008) {
    Factory<> f;
    auto comp = f.createComponent("4008");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4013) {
    Factory<> f;
    auto comp = f.createComponent("4013");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4040) {
    Factory<> f;
    auto comp = f.createComponent("4040");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4017) {
    Factory<> f;
    auto comp = f.createComponent("4017");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4094) {
    Factory<> f;
    auto comp = f.createComponent("4094");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4512) {
    Factory<> f;
    auto comp = f.createComponent("4512");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_4514) {
    Factory<> f;
    auto comp = f.createComponent("4514");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_2716_throws_without_rom_file) {
    Factory<> f;

    cr_assert_throw(f.createComponent("2716"), NanoTekSpiceException);
}

Test(Factory, create_4801) {
    Factory<> f;
    auto comp = f.createComponent("4801");
    cr_assert_not_null(comp.get());
}

Test(Factory, create_unknown_returns_nullptr) {
    Factory<> f;
    auto comp = f.createComponent("unknown_component");
    cr_assert_null(comp.get());
}

Test(Factory, create_empty_string_returns_nullptr) {
    Factory<> f;
    auto comp = f.createComponent("");
    cr_assert_null(comp.get());
}

Test(Circuit, add_component) {
    Circuit c;
    auto input = std::make_unique<Input>();
    cr_assert(c.addComponent("in1", std::move(input)));
    cr_assert_eq(c.getNumberOfComponents(), 1);
}

Test(Circuit, add_duplicate_component_fails) {
    Circuit c;
    auto input1 = std::make_unique<Input>();
    auto input2 = std::make_unique<Input>();
    cr_assert(c.addComponent("in1", std::move(input1)));
    cr_assert_not(c.addComponent("in1", std::move(input2)));
    cr_assert_eq(c.getNumberOfComponents(), 1);
}

Test(Circuit, add_link_valid) {
    Circuit c;
    auto input = std::make_unique<Input>();
    auto output = std::make_unique<Out>();
    c.addComponent("in1", std::move(input));
    c.addComponent("out1", std::move(output));
    cr_assert_no_throw(c.addLink("in1", 1, "out1", 1), NanoTekSpiceException);
}

Test(Circuit, add_link_unknown_component) {
    Circuit c;
    auto input = std::make_unique<Input>();
    c.addComponent("in1", std::move(input));
    cr_assert_throw(c.addLink("in1", 1, "unknown", 1), NanoTekSpiceException);
}

Test(Circuit, simulate_and_compute) {
    Circuit c;
    auto input = std::make_unique<Input>();
    auto output = std::make_unique<Out>();

    Input* inPtr = input.get();

    c.addComponent("in1", std::move(input));
    c.addComponent("out1", std::move(output));
    c.addLink("in1", 1, "out1", 1);

    inPtr->setValue(True);

    std::string cmd = "simulate";
    c.simulate(cmd);

    cr_assert_eq(c.getNumberOfComponents(), 2);
}

Test(Errors, exception_what) {
    NanoTekSpiceException e(NoFileException);
    cr_assert_str_eq(e.what(), "No file was given as parameter!");
}

Test(Errors, too_much_arguments) {
    NanoTekSpiceException e(TooMuchArgumentsException);
    cr_assert_str_eq(e.what(), "Too much arguments was given as parameters!");
}

Test(Errors, file_open) {
    NanoTekSpiceException e(FileOpenException);
    cr_assert_str_eq(e.what(), "Impossible to open the given file!");
}

Test(Errors, syntax_error) {
    NanoTekSpiceException e(SyntaxFileException);
    cr_assert_str_eq(e.what(), "The circuit file includes one or several lexical or syntactic errors!");
}

Test(Errors, component_type) {
    NanoTekSpiceException e(ComponentTypeException);
    cr_assert_str_eq(e.what(), "A component type is unknown!");
}

Test(Errors, component_already_exist) {
    NanoTekSpiceException e(ComponentAlreadyExistException);
    cr_assert_str_eq(e.what(), "Several components share the same name!");
}

Test(Errors, component_name) {
    NanoTekSpiceException e(ComponentNameException);
    cr_assert_str_eq(e.what(), "A component name is unknown!");
}

Test(Errors, invalid_value) {
    NanoTekSpiceException e(InvalidValue);
    cr_assert_str_eq(e.what(), "Invalid value when using input=value command!");
}

