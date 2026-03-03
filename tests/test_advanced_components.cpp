
#include <criterion/criterion.h>

#include "IComponent.h++"
#include "Components/AdvancedComponents/HalfBitsAdder.h++"
#include "Components/AdvancedComponents/FullBitsAdder.h++"
#include "Components/AdvancedComponents/FourBitsAdder.h++"
#include "Components/AdvancedComponents/FlipFlop.h++"
#include "Components/AdvancedComponents/DualFlipFlop.h++"
#include "Components/AdvancedComponents/BitBinaryCounter.h++"
#include "Components/AdvancedComponents/JohnsonDecade.h++"
#include "Components/AdvancedComponents/HeightBitShifter.h++"
#include "Components/AdvancedComponents/HeightChannelDataSelector.h++"
#include "Components/AdvancedComponents/FourBitsDecoder.h++"
#include "Components/SpecialComponents/True.h++"
#include "Components/SpecialComponents/False.h++"
#include "Components/SpecialComponents/Input.h++"
#include "Errors/NanoTekSpiceErrors.h++"

using namespace nts;

Test(HalfBitsAdder, zero_plus_zero) {
    HalfBitsAdder hba;
    Input a, b;
    a.setValue(False);
    b.setValue(False);
    a.simulate(1);
    b.simulate(1);
    hba.setLink(1, a, 1);
    hba.setLink(2, b, 1);
    hba.simulate(1);
    cr_assert_eq(hba.compute(3), False);
    cr_assert_eq(hba.compute(4), False);
}

Test(HalfBitsAdder, one_plus_zero) {
    HalfBitsAdder hba;
    Input a, b;
    a.setValue(True);
    b.setValue(False);
    a.simulate(1);
    b.simulate(1);
    hba.setLink(1, a, 1);
    hba.setLink(2, b, 1);
    hba.simulate(1);
    cr_assert_eq(hba.compute(3), True);
    cr_assert_eq(hba.compute(4), False);
}

Test(HalfBitsAdder, zero_plus_one) {
    HalfBitsAdder hba;
    Input a, b;
    a.setValue(False);
    b.setValue(True);
    a.simulate(1);
    b.simulate(1);
    hba.setLink(1, a, 1);
    hba.setLink(2, b, 1);
    hba.simulate(1);
    cr_assert_eq(hba.compute(3), True);
    cr_assert_eq(hba.compute(4), False);
}

Test(HalfBitsAdder, one_plus_one) {
    HalfBitsAdder hba;
    Input a, b;
    a.setValue(True);
    b.setValue(True);
    a.simulate(1);
    b.simulate(1);
    hba.setLink(1, a, 1);
    hba.setLink(2, b, 1);
    hba.simulate(1);
    cr_assert_eq(hba.compute(3), False);
    cr_assert_eq(hba.compute(4), True);
}

Test(HalfBitsAdder, invalid_pin_throws) {
    HalfBitsAdder hba;
    cr_assert_throw(hba.compute(1), NanoTekSpiceException);
    cr_assert_throw(hba.compute(2), NanoTekSpiceException);
    cr_assert_throw(hba.compute(5), NanoTekSpiceException);
}

Test(HalfBitsAdder, invalid_link_throws) {
    HalfBitsAdder hba;
    Input a;
    cr_assert_throw(hba.setLink(5, a, 1), NanoTekSpiceException);
    cr_assert_throw(hba.setLink(0, a, 1), NanoTekSpiceException);
}

Test(FullBitsAdder, zero_plus_zero_cin_zero) {
    FullBitsAdder fba;
    Input a, b, cin;
    a.setValue(False);
    b.setValue(False);
    cin.setValue(False);
    a.simulate(1);
    b.simulate(1);
    cin.simulate(1);
    fba.setLink(1, a, 1);
    fba.setLink(2, b, 1);
    fba.setLink(3, cin, 1);
    fba.simulate(1);
    cr_assert_eq(fba.compute(4), False);
    cr_assert_eq(fba.compute(5), False);
}

Test(FullBitsAdder, one_plus_zero_cin_zero) {
    FullBitsAdder fba;
    Input a, b, cin;
    a.setValue(True);
    b.setValue(False);
    cin.setValue(False);
    a.simulate(1);
    b.simulate(1);
    cin.simulate(1);
    fba.setLink(1, a, 1);
    fba.setLink(2, b, 1);
    fba.setLink(3, cin, 1);
    fba.simulate(1);
    cr_assert_eq(fba.compute(4), True);
    cr_assert_eq(fba.compute(5), False);
}

Test(FullBitsAdder, one_plus_one_cin_zero) {
    FullBitsAdder fba;
    Input a, b, cin;
    a.setValue(True);
    b.setValue(True);
    cin.setValue(False);
    a.simulate(1);
    b.simulate(1);
    cin.simulate(1);
    fba.setLink(1, a, 1);
    fba.setLink(2, b, 1);
    fba.setLink(3, cin, 1);
    fba.simulate(1);
    cr_assert_eq(fba.compute(4), False);
    cr_assert_eq(fba.compute(5), True);
}

Test(FullBitsAdder, one_plus_one_cin_one) {
    FullBitsAdder fba;
    Input a, b, cin;
    a.setValue(True);
    b.setValue(True);
    cin.setValue(True);
    a.simulate(1);
    b.simulate(1);
    cin.simulate(1);
    fba.setLink(1, a, 1);
    fba.setLink(2, b, 1);
    fba.setLink(3, cin, 1);
    fba.simulate(1);
    cr_assert_eq(fba.compute(4), True);
    cr_assert_eq(fba.compute(5), True);
}

Test(FullBitsAdder, zero_plus_one_cin_one) {
    FullBitsAdder fba;
    Input a, b, cin;
    a.setValue(False);
    b.setValue(True);
    cin.setValue(True);
    a.simulate(1);
    b.simulate(1);
    cin.simulate(1);
    fba.setLink(1, a, 1);
    fba.setLink(2, b, 1);
    fba.setLink(3, cin, 1);
    fba.simulate(1);
    cr_assert_eq(fba.compute(4), False);
    cr_assert_eq(fba.compute(5), True);
}

Test(FullBitsAdder, invalid_pin_throws) {
    FullBitsAdder fba;
    cr_assert_throw(fba.compute(1), NanoTekSpiceException);
    cr_assert_throw(fba.compute(6), NanoTekSpiceException);
}

Test(FullBitsAdder, invalid_link_throws) {
    FullBitsAdder fba;
    Input a;
    cr_assert_throw(fba.setLink(6, a, 1), NanoTekSpiceException);
}

Test(FourBitsAdder, zero_plus_zero) {
    auto adder = CREATE_4008;
    class False f;

    adder->setLink(7, f, 1);
    adder->setLink(6, f, 1);
    adder->setLink(5, f, 1);
    adder->setLink(4, f, 1);
    adder->setLink(3, f, 1);
    adder->setLink(2, f, 1);
    adder->setLink(1, f, 1);
    adder->setLink(15, f, 1);
    adder->setLink(9, f, 1);

    adder->simulate(1);

    cr_assert_eq(adder->compute(10), False);
    cr_assert_eq(adder->compute(11), False);
    cr_assert_eq(adder->compute(12), False);
    cr_assert_eq(adder->compute(13), False);
    cr_assert_eq(adder->compute(14), False);
}

Test(FourBitsAdder, one_plus_one) {
    auto adder = CREATE_4008;
    class True t;
    class False f;

    adder->setLink(7, t, 1);
    adder->setLink(6, t, 1);
    adder->setLink(5, f, 1);
    adder->setLink(4, f, 1);
    adder->setLink(3, f, 1);
    adder->setLink(2, f, 1);
    adder->setLink(1, f, 1);
    adder->setLink(15, f, 1);
    adder->setLink(9, f, 1);

    adder->simulate(1);

    cr_assert_eq(adder->compute(10), False);
    cr_assert_eq(adder->compute(11), True);
    cr_assert_eq(adder->compute(12), False);
    cr_assert_eq(adder->compute(13), False);
    cr_assert_eq(adder->compute(14), False);
}

Test(FourBitsAdder, max_plus_one) {
    auto adder = CREATE_4008;
    class True t;
    class False f;

    adder->setLink(7, t, 1);
    adder->setLink(6, t, 1);
    adder->setLink(5, t, 1);
    adder->setLink(4, f, 1);
    adder->setLink(3, t, 1);
    adder->setLink(2, f, 1);
    adder->setLink(1, t, 1);
    adder->setLink(15, f, 1);
    adder->setLink(9, f, 1);

    adder->simulate(1);

    cr_assert_eq(adder->compute(10), False);
    cr_assert_eq(adder->compute(11), False);
    cr_assert_eq(adder->compute(12), False);
    cr_assert_eq(adder->compute(13), False);
    cr_assert_eq(adder->compute(14), True);
}

Test(FourBitsAdder, invalid_compute_pin_throws) {
    auto adder = CREATE_4008;
    cr_assert_throw(adder->compute(1), NanoTekSpiceException);
    cr_assert_throw(adder->compute(7), NanoTekSpiceException);
}

Test(FourBitsAdder, invalid_setlink_pin_throws) {
    auto adder = CREATE_4008;
    Input a;
    cr_assert_throw(adder->setLink(16, a, 1), NanoTekSpiceException);
}

Test(FlipFlop, set_overrides) {
    FlipFlop ff;
    Input clk, reset, data, set;
    clk.setValue(False);
    reset.setValue(False);
    data.setValue(False);
    set.setValue(True);
    clk.simulate(1);
    reset.simulate(1);
    data.simulate(1);
    set.simulate(1);

    ff.setLink(3, clk, 1);
    ff.setLink(4, reset, 1);
    ff.setLink(5, data, 1);
    ff.setLink(6, set, 1);
    ff.simulate(1);

    cr_assert_eq(ff.compute(1), True);
    cr_assert_eq(ff.compute(2), False);
}

Test(FlipFlop, reset_overrides) {
    FlipFlop ff;
    Input clk, reset, data, set;
    clk.setValue(False);
    reset.setValue(True);
    data.setValue(False);
    set.setValue(False);
    clk.simulate(1);
    reset.simulate(1);
    data.simulate(1);
    set.simulate(1);

    ff.setLink(3, clk, 1);
    ff.setLink(4, reset, 1);
    ff.setLink(5, data, 1);
    ff.setLink(6, set, 1);
    ff.simulate(1);

    cr_assert_eq(ff.compute(1), False);
    cr_assert_eq(ff.compute(2), True);
}

Test(FlipFlop, rising_edge_data_true) {
    FlipFlop ff;
    Input clk, reset, data, set;
    clk.setValue(False);
    reset.setValue(False);
    data.setValue(True);
    set.setValue(False);
    clk.simulate(1);
    reset.simulate(1);
    data.simulate(1);
    set.simulate(1);

    ff.setLink(3, clk, 1);
    ff.setLink(4, reset, 1);
    ff.setLink(5, data, 1);
    ff.setLink(6, set, 1);

    ff.simulate(1);
    ff.compute(1);

    clk.setValue(True);
    clk.simulate(2);
    ff.simulate(2);

    cr_assert_eq(ff.compute(1), True);
    cr_assert_eq(ff.compute(2), False);
}

Test(FlipFlop, rising_edge_data_false) {
    FlipFlop ff;
    Input clk, reset, data, set;
    clk.setValue(False);
    reset.setValue(False);
    data.setValue(False);
    set.setValue(False);
    clk.simulate(1);
    reset.simulate(1);
    data.simulate(1);
    set.simulate(1);

    ff.setLink(3, clk, 1);
    ff.setLink(4, reset, 1);
    ff.setLink(5, data, 1);
    ff.setLink(6, set, 1);

    ff.simulate(1);
    ff.compute(1);

    clk.setValue(True);
    clk.simulate(2);
    ff.simulate(2);

    cr_assert_eq(ff.compute(1), False);
    cr_assert_eq(ff.compute(2), True);
}

Test(FlipFlop, invalid_pin_throws) {
    FlipFlop ff;
    Input clk, reset, data, set;
    clk.setValue(False);
    reset.setValue(False);
    data.setValue(False);
    set.setValue(False);
    clk.simulate(1);
    reset.simulate(1);
    data.simulate(1);
    set.simulate(1);

    ff.setLink(3, clk, 1);
    ff.setLink(4, reset, 1);
    ff.setLink(5, data, 1);
    ff.setLink(6, set, 1);
    ff.simulate(1);

    cr_assert_throw(ff.compute(3), NanoTekSpiceException);
}

Test(DualFlipFlop, ff1_set) {
    DualFlipFlop dff;
    Input clk, reset, data, set;
    clk.setValue(False);
    reset.setValue(False);
    data.setValue(False);
    set.setValue(True);
    clk.simulate(1);
    reset.simulate(1);
    data.simulate(1);
    set.simulate(1);

    dff.setLink(3, clk, 1);
    dff.setLink(4, reset, 1);
    dff.setLink(5, data, 1);
    dff.setLink(6, set, 1);
    dff.simulate(1);

    cr_assert_eq(dff.compute(1), True);
    cr_assert_eq(dff.compute(2), False);
}

Test(DualFlipFlop, ff2_set) {
    DualFlipFlop dff;
    Input clk, reset, data, set;
    clk.setValue(False);
    reset.setValue(False);
    data.setValue(False);
    set.setValue(True);
    clk.simulate(1);
    reset.simulate(1);
    data.simulate(1);
    set.simulate(1);

    dff.setLink(11, clk, 1);
    dff.setLink(10, reset, 1);
    dff.setLink(9, data, 1);
    dff.setLink(8, set, 1);
    dff.simulate(1);

    cr_assert_eq(dff.compute(13), True);
    cr_assert_eq(dff.compute(12), False);
}

Test(DualFlipFlop, invalid_pin_throws) {
    DualFlipFlop dff;
    Input a;
    cr_assert_throw(dff.setLink(0, a, 1), NanoTekSpiceException);
    cr_assert_throw(dff.setLink(7, a, 1), NanoTekSpiceException);
    cr_assert_throw(dff.setLink(14, a, 1), NanoTekSpiceException);
}

Test(DualFlipFlop, invalid_compute_pin_throws) {
    DualFlipFlop dff;
    cr_assert_throw(dff.compute(3), NanoTekSpiceException);
    cr_assert_throw(dff.compute(5), NanoTekSpiceException);
}

Test(BitBinaryCounter, reset) {
    BitBinaryCounter bbc;
    Input clk, reset;
    clk.setValue(False);
    reset.setValue(True);
    clk.simulate(1);
    reset.simulate(1);

    bbc.setLink(10, clk, 1);
    bbc.setLink(11, reset, 1);
    bbc.simulate(1);

    cr_assert_eq(bbc.compute(9), False);
    cr_assert_eq(bbc.compute(7), False);
    cr_assert_eq(bbc.compute(1), False);
}

Test(BitBinaryCounter, count_one) {
    BitBinaryCounter bbc;
    Input clk, reset;

    clk.setValue(False);
    reset.setValue(True);
    clk.simulate(1);
    reset.simulate(1);
    bbc.setLink(10, clk, 1);
    bbc.setLink(11, reset, 1);
    bbc.simulate(1);
    bbc.compute(9);

    reset.setValue(False);
    reset.simulate(2);

    clk.setValue(True);
    clk.simulate(2);
    bbc.simulate(2);
    bbc.compute(9);

    clk.setValue(False);
    clk.simulate(3);
    bbc.simulate(3);

    cr_assert_eq(bbc.compute(9), True);
    cr_assert_eq(bbc.compute(7), False);
}

Test(BitBinaryCounter, invalid_pin_throws) {
    BitBinaryCounter bbc;
    cr_assert_throw(bbc.compute(16), NanoTekSpiceException);
    cr_assert_throw(bbc.compute(8), NanoTekSpiceException);
}

Test(JohnsonDecade, initial_q0_active) {
    JohnsonDecade jd;
    Input clk, ci, mr;

    clk.setValue(False);
    ci.setValue(False);
    mr.setValue(False);
    clk.simulate(1);
    ci.simulate(1);
    mr.simulate(1);

    jd.setLink(14, clk, 1);
    jd.setLink(13, ci, 1);
    jd.setLink(15, mr, 1);
    jd.simulate(1);

    cr_assert_eq(jd.compute(3), True);
    cr_assert_eq(jd.compute(2), False);
    cr_assert_eq(jd.compute(12), True);
}

Test(JohnsonDecade, advance_on_rising_clock) {
    JohnsonDecade jd;
    Input clk, ci, mr;

    clk.setValue(False);
    ci.setValue(False);
    mr.setValue(False);
    clk.simulate(1);
    ci.simulate(1);
    mr.simulate(1);

    jd.setLink(14, clk, 1);
    jd.setLink(13, ci, 1);
    jd.setLink(15, mr, 1);
    jd.simulate(1);
    jd.compute(3);

    clk.setValue(True);
    clk.simulate(2);
    jd.simulate(2);

    cr_assert_eq(jd.compute(2), True);
    cr_assert_eq(jd.compute(3), False);
}

Test(JohnsonDecade, master_reset) {
    JohnsonDecade jd;
    Input clk, ci, mr;

    clk.setValue(False);
    ci.setValue(False);
    mr.setValue(False);
    clk.simulate(1);
    ci.simulate(1);
    mr.simulate(1);

    jd.setLink(14, clk, 1);
    jd.setLink(13, ci, 1);
    jd.setLink(15, mr, 1);
    jd.simulate(1);
    jd.compute(3);

    clk.setValue(True);
    clk.simulate(2);
    jd.simulate(2);
    jd.compute(3);

    clk.setValue(False);
    clk.simulate(3);
    jd.simulate(3);
    jd.compute(3);

    clk.setValue(True);
    clk.simulate(4);
    jd.simulate(4);
    jd.compute(3);

    mr.setValue(True);
    mr.simulate(5);
    jd.simulate(5);

    cr_assert_eq(jd.compute(3), True);
}

Test(JohnsonDecade, undefined_returns_undefined) {
    JohnsonDecade jd;
    Input clk, ci, mr;

    clk.setValue(Undefined);
    ci.setValue(False);
    mr.setValue(False);
    clk.simulate(1);
    ci.simulate(1);
    mr.simulate(1);

    jd.setLink(14, clk, 1);
    jd.setLink(13, ci, 1);
    jd.setLink(15, mr, 1);
    jd.simulate(1);

    cr_assert_eq(jd.compute(3), Undefined);
}

Test(JohnsonDecade, carry_out_behavior) {
    JohnsonDecade jd;
    Input clk, ci, mr;

    clk.setValue(False);
    ci.setValue(False);
    mr.setValue(False);
    clk.simulate(1);
    ci.simulate(1);
    mr.simulate(1);

    jd.setLink(14, clk, 1);
    jd.setLink(13, ci, 1);
    jd.setLink(15, mr, 1);
    jd.simulate(1);
    jd.compute(12);

    for (int i = 0; i < 5; i++) {
        clk.setValue(True);
        clk.simulate(2 + i * 2);
        jd.simulate(2 + i * 2);
        jd.compute(12);

        clk.setValue(False);
        clk.simulate(3 + i * 2);
        jd.simulate(3 + i * 2);
        jd.compute(12);
    }

    cr_assert_eq(jd.compute(12), False);
}

Test(JohnsonDecade, invalid_pin_throws) {
    JohnsonDecade jd;
    Input clk, ci, mr;
    clk.setValue(False);
    ci.setValue(False);
    mr.setValue(False);
    clk.simulate(1);
    ci.simulate(1);
    mr.simulate(1);

    jd.setLink(14, clk, 1);
    jd.setLink(13, ci, 1);
    jd.setLink(15, mr, 1);
    jd.simulate(1);

    cr_assert_throw(jd.compute(13), NanoTekSpiceException);
    cr_assert_throw(jd.compute(8), NanoTekSpiceException);
}

Test(HeightChannelDataSelector, select_channel_0) {
    HeightChannelDataSelector hcds;
    Input x0, inhibit, a, b, c, oe;
    class False f;

    x0.setValue(True);
    x0.simulate(1);
    inhibit.setValue(False);
    inhibit.simulate(1);
    a.setValue(False);
    a.simulate(1);
    b.setValue(False);
    b.simulate(1);
    c.setValue(False);
    c.simulate(1);
    oe.setValue(False);
    oe.simulate(1);

    hcds.setLink(1, x0, 1);
    hcds.setLink(10, inhibit, 1);
    hcds.setLink(11, a, 1);
    hcds.setLink(12, b, 1);
    hcds.setLink(13, c, 1);
    hcds.setLink(15, oe, 1);
    hcds.simulate(1);

    cr_assert_eq(hcds.compute(14), True);
}

Test(HeightChannelDataSelector, select_channel_1) {
    HeightChannelDataSelector hcds;
    Input x0, x1, inhibit, a, b, c, oe;

    x0.setValue(False);
    x0.simulate(1);
    x1.setValue(True);
    x1.simulate(1);
    inhibit.setValue(False);
    inhibit.simulate(1);
    a.setValue(True);
    a.simulate(1);
    b.setValue(False);
    b.simulate(1);
    c.setValue(False);
    c.simulate(1);
    oe.setValue(False);
    oe.simulate(1);

    hcds.setLink(1, x0, 1);
    hcds.setLink(2, x1, 1);
    hcds.setLink(10, inhibit, 1);
    hcds.setLink(11, a, 1);
    hcds.setLink(12, b, 1);
    hcds.setLink(13, c, 1);
    hcds.setLink(15, oe, 1);
    hcds.simulate(1);

    cr_assert_eq(hcds.compute(14), True);
}

Test(HeightChannelDataSelector, inhibit_returns_false) {
    HeightChannelDataSelector hcds;
    Input x0, inhibit, a, b, c, oe;

    x0.setValue(True);
    x0.simulate(1);
    inhibit.setValue(True);
    inhibit.simulate(1);
    a.setValue(False);
    a.simulate(1);
    b.setValue(False);
    b.simulate(1);
    c.setValue(False);
    c.simulate(1);
    oe.setValue(False);
    oe.simulate(1);

    hcds.setLink(1, x0, 1);
    hcds.setLink(10, inhibit, 1);
    hcds.setLink(11, a, 1);
    hcds.setLink(12, b, 1);
    hcds.setLink(13, c, 1);
    hcds.setLink(15, oe, 1);
    hcds.simulate(1);

    cr_assert_eq(hcds.compute(14), False);
}

Test(HeightChannelDataSelector, oe_true_returns_undefined) {
    HeightChannelDataSelector hcds;
    Input x0, inhibit, a, b, c, oe;

    x0.setValue(True);
    x0.simulate(1);
    inhibit.setValue(False);
    inhibit.simulate(1);
    a.setValue(False);
    a.simulate(1);
    b.setValue(False);
    b.simulate(1);
    c.setValue(False);
    c.simulate(1);
    oe.setValue(True);
    oe.simulate(1);

    hcds.setLink(1, x0, 1);
    hcds.setLink(10, inhibit, 1);
    hcds.setLink(11, a, 1);
    hcds.setLink(12, b, 1);
    hcds.setLink(13, c, 1);
    hcds.setLink(15, oe, 1);
    hcds.simulate(1);

    cr_assert_eq(hcds.compute(14), Undefined);
}

Test(HeightChannelDataSelector, invalid_pin_throws) {
    HeightChannelDataSelector hcds;
    cr_assert_throw(hcds.compute(1), NanoTekSpiceException);
    cr_assert_throw(hcds.compute(10), NanoTekSpiceException);
}

Test(FourBitsDecoder, decode_value_0) {
    FourBitsDecoder fbd;
    Input strobe, a, b, c, d, inhib;

    strobe.setValue(True);
    strobe.simulate(1);
    a.setValue(False);
    a.simulate(1);
    b.setValue(False);
    b.simulate(1);
    c.setValue(False);
    c.simulate(1);
    d.setValue(False);
    d.simulate(1);
    inhib.setValue(False);
    inhib.simulate(1);

    fbd.setLink(1, strobe, 1);
    fbd.setLink(2, a, 1);
    fbd.setLink(3, b, 1);
    fbd.setLink(21, c, 1);
    fbd.setLink(22, d, 1);
    fbd.setLink(23, inhib, 1);
    fbd.simulate(1);

    cr_assert_eq(fbd.compute(11), True);
    cr_assert_eq(fbd.compute(9), False);
}

Test(FourBitsDecoder, decode_value_1) {
    FourBitsDecoder fbd;
    Input strobe, a, b, c, d, inhib;

    strobe.setValue(True);
    strobe.simulate(1);
    a.setValue(True);
    a.simulate(1);
    b.setValue(False);
    b.simulate(1);
    c.setValue(False);
    c.simulate(1);
    d.setValue(False);
    d.simulate(1);
    inhib.setValue(False);
    inhib.simulate(1);

    fbd.setLink(1, strobe, 1);
    fbd.setLink(2, a, 1);
    fbd.setLink(3, b, 1);
    fbd.setLink(21, c, 1);
    fbd.setLink(22, d, 1);
    fbd.setLink(23, inhib, 1);
    fbd.simulate(1);

    cr_assert_eq(fbd.compute(9), True);
    cr_assert_eq(fbd.compute(11), False);
}

Test(FourBitsDecoder, inhibit_all_false) {
    FourBitsDecoder fbd;
    Input strobe, a, b, c, d, inhib;

    strobe.setValue(True);
    strobe.simulate(1);
    a.setValue(False);
    a.simulate(1);
    b.setValue(False);
    b.simulate(1);
    c.setValue(False);
    c.simulate(1);
    d.setValue(False);
    d.simulate(1);
    inhib.setValue(True);
    inhib.simulate(1);

    fbd.setLink(1, strobe, 1);
    fbd.setLink(2, a, 1);
    fbd.setLink(3, b, 1);
    fbd.setLink(21, c, 1);
    fbd.setLink(22, d, 1);
    fbd.setLink(23, inhib, 1);
    fbd.simulate(1);

    cr_assert_eq(fbd.compute(11), False);
    cr_assert_eq(fbd.compute(9), False);
}

Test(FourBitsDecoder, strobe_false_all_false) {
    FourBitsDecoder fbd;
    Input strobe, a, b, c, d, inhib;

    strobe.setValue(False);
    strobe.simulate(1);
    a.setValue(True);
    a.simulate(1);
    b.setValue(True);
    b.simulate(1);
    c.setValue(True);
    c.simulate(1);
    d.setValue(True);
    d.simulate(1);
    inhib.setValue(False);
    inhib.simulate(1);

    fbd.setLink(1, strobe, 1);
    fbd.setLink(2, a, 1);
    fbd.setLink(3, b, 1);
    fbd.setLink(21, c, 1);
    fbd.setLink(22, d, 1);
    fbd.setLink(23, inhib, 1);
    fbd.simulate(1);

    cr_assert_eq(fbd.compute(15), False);
}

Test(FourBitsDecoder, invalid_pin_throws) {
    FourBitsDecoder fbd;
    Input strobe, inhib;
    strobe.setValue(True);
    strobe.simulate(1);
    inhib.setValue(False);
    inhib.simulate(1);
    fbd.setLink(1, strobe, 1);
    fbd.setLink(23, inhib, 1);
    fbd.simulate(1);

    cr_assert_throw(fbd.compute(1), NanoTekSpiceException);
    cr_assert_throw(fbd.compute(2), NanoTekSpiceException);
    cr_assert_throw(fbd.compute(12), NanoTekSpiceException);
}

Test(HeightBitShifter, initial_undefined) {
    HeightBitShifter hbs;
    Input strobe, data, clk, oe;
    strobe.setValue(True);
    data.setValue(Undefined);
    clk.setValue(False);
    oe.setValue(True);
    strobe.simulate(1);
    data.simulate(1);
    clk.simulate(1);
    oe.simulate(1);

    hbs.setLink(1, strobe, 1);
    hbs.setLink(2, data, 1);
    hbs.setLink(3, clk, 1);
    hbs.setLink(15, oe, 1);
    hbs.simulate(1);

    cr_assert_eq(hbs.compute(4), Undefined);
}

Test(HeightBitShifter, shift_one_bit) {
    HeightBitShifter hbs;
    Input strobe, data, clk, oe;

    strobe.setValue(True);
    data.setValue(True);
    clk.setValue(False);
    oe.setValue(True);
    strobe.simulate(1);
    data.simulate(1);
    clk.simulate(1);
    oe.simulate(1);

    hbs.setLink(1, strobe, 1);
    hbs.setLink(2, data, 1);
    hbs.setLink(3, clk, 1);
    hbs.setLink(15, oe, 1);
    hbs.simulate(1);

    hbs.compute(4);

    clk.setValue(True);
    clk.simulate(2);
    hbs.simulate(2);

    cr_assert_eq(hbs.compute(4), True);
}

Test(HeightBitShifter, oe_false_returns_undefined) {
    HeightBitShifter hbs;
    Input strobe, data, clk, oe;

    strobe.setValue(True);
    data.setValue(True);
    clk.setValue(False);
    oe.setValue(False);
    strobe.simulate(1);
    data.simulate(1);
    clk.simulate(1);
    oe.simulate(1);

    hbs.setLink(1, strobe, 1);
    hbs.setLink(2, data, 1);
    hbs.setLink(3, clk, 1);
    hbs.setLink(15, oe, 1);
    hbs.simulate(1);

    cr_assert_eq(hbs.compute(4), Undefined);
}

Test(HeightBitShifter, invalid_pin_throws) {
    HeightBitShifter hbs;
    Input strobe, data, clk, oe;
    strobe.setValue(True);
    data.setValue(False);
    clk.setValue(False);
    oe.setValue(True);
    strobe.simulate(1);
    data.simulate(1);
    clk.simulate(1);
    oe.simulate(1);
    hbs.setLink(1, strobe, 1);
    hbs.setLink(2, data, 1);
    hbs.setLink(3, clk, 1);
    hbs.setLink(15, oe, 1);
    hbs.simulate(1);

    cr_assert_throw(hbs.compute(1), NanoTekSpiceException);
    cr_assert_throw(hbs.compute(2), NanoTekSpiceException);
    cr_assert_throw(hbs.compute(3), NanoTekSpiceException);
    cr_assert_throw(hbs.compute(15), NanoTekSpiceException);
}

