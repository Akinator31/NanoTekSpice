
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "IComponent.h++"
#include "Components/SpecialComponents/Input.h++"
#include "Components/SpecialComponents/Out.h++"
#include "Components/SpecialComponents/True.h++"
#include "Components/SpecialComponents/False.h++"
#include "Components/SpecialComponents/Clock.h++"
#include "Components/AComponent.h++"

using namespace nts;

Test(TrueComponent, create) {
    class True t;
    cr_assert_eq(t.getType(), Other);
}

Test(TrueComponent, compute_always_returns_true) {
    class True t;
    cr_assert_eq(t.compute(1), Tristate::True);
}

Test(TrueComponent, compute_any_pin_returns_true) {
    class True t;
    cr_assert_eq(t.compute(0), Tristate::True);
    cr_assert_eq(t.compute(42), Tristate::True);
}

Test(FalseComponent, create) {
    class False f;
    cr_assert_eq(f.getType(), Other);
}

Test(FalseComponent, compute_always_returns_false) {
    class False f;
    cr_assert_eq(f.compute(1), Tristate::False);
}

Test(FalseComponent, compute_any_pin_returns_false) {
    class False f;
    cr_assert_eq(f.compute(0), Tristate::False);
    cr_assert_eq(f.compute(42), Tristate::False);
}

Test(InputComponent, create) {
    Input i;
    cr_assert_eq(i.getType(), InputComponent);
}

Test(InputComponent, default_value_is_undefined) {
    Input i;
    cr_assert_eq(i.compute(1), Tristate::Undefined);
}

Test(InputComponent, set_value_true) {
    Input i;
    i.setValue(Tristate::True);

    cr_assert_eq(i.compute(1), Tristate::Undefined);
    i.simulate(1);
    cr_assert_eq(i.compute(1), Tristate::True);
}

Test(InputComponent, set_value_false) {
    Input i;
    i.setValue(Tristate::False);
    i.simulate(1);
    cr_assert_eq(i.compute(1), Tristate::False);
}

Test(InputComponent, set_value_undefined) {
    Input i;
    i.setValue(Tristate::True);
    i.simulate(1);
    cr_assert_eq(i.compute(1), Tristate::True);
    i.setValue(Tristate::Undefined);
    i.simulate(2);
    cr_assert_eq(i.compute(1), Tristate::Undefined);
}

Test(InputComponent, simulate_applies_next_state) {
    Input i;
    i.setValue(Tristate::True);
    cr_assert_eq(i.compute(1), Tristate::Undefined);
    i.simulate(1);
    cr_assert_eq(i.compute(1), Tristate::True);
    i.setValue(Tristate::False);
    cr_assert_eq(i.compute(1), Tristate::True);
    i.simulate(2);
    cr_assert_eq(i.compute(1), Tristate::False);
}

Test(OutputComponent, create) {
    Out o;
    cr_assert_eq(o.getType(), OutComponent);
}

Test(OutputComponent, compute_with_true_linked) {
    Out o;
    class True t;
    o.setLink(1, t, 1);
    o.simulate(1);
    cr_assert_eq(o.compute(1), Tristate::True);
}

Test(OutputComponent, compute_with_false_linked) {
    Out o;
    class False f;
    o.setLink(1, f, 1);
    o.simulate(1);
    cr_assert_eq(o.compute(1), Tristate::False);
}

Test(OutputComponent, compute_with_input_linked) {
    Out o;
    Input i;
    i.setValue(Tristate::True);
    i.simulate(1);
    o.setLink(1, i, 1);
    o.simulate(1);
    cr_assert_eq(o.compute(1), Tristate::True);
}

Test(ClockComponent, create) {
    Clock c;
    cr_assert_eq(c.getType(), ClockComponent);
}

Test(ClockComponent, default_value_is_undefined) {
    Clock c;
    cr_assert_eq(c.compute(1), Tristate::Undefined);
}

Test(ClockComponent, set_value_and_simulate) {
    Clock c;
    c.setValue(Tristate::False);
    c.simulate(1);
    cr_assert_eq(c.compute(1), Tristate::False);
}

Test(ClockComponent, toggles_after_simulate) {
    Clock c;
    c.setValue(Tristate::False);
    c.simulate(1);
    cr_assert_eq(c.compute(1), Tristate::False);

    c.simulate(2);
    cr_assert_eq(c.compute(1), Tristate::True);

    c.simulate(3);
    cr_assert_eq(c.compute(1), Tristate::False);
}

Test(ClockComponent, set_value_overrides_toggle) {
    Clock c;
    c.setValue(Tristate::True);
    c.simulate(1);
    cr_assert_eq(c.compute(1), Tristate::True);

    c.setValue(Tristate::True);
    c.simulate(2);
    cr_assert_eq(c.compute(1), Tristate::True);
}

