
#include <criterion/criterion.h>

#include "IComponent.h++"
#include "Utils/Utils.h++"
#include "Errors/NanoTekSpiceErrors.h++"

using namespace nts;

Test(TristateNot, not_true) {
    cr_assert_eq(!Tristate::True, Tristate::False);
}

Test(TristateNot, not_false) {
    cr_assert_eq(!Tristate::False, Tristate::True);
}

Test(TristateNot, not_undefined) {
    cr_assert_eq(!Tristate::Undefined, Tristate::Undefined);
}

Test(TristateAnd, true_and_true) {
    cr_assert_eq((Tristate::True && Tristate::True), Tristate::True);
}

Test(TristateAnd, true_and_false) {
    cr_assert_eq((Tristate::True && Tristate::False), Tristate::False);
}

Test(TristateAnd, false_and_true) {
    cr_assert_eq((Tristate::False && Tristate::True), Tristate::False);
}

Test(TristateAnd, false_and_false) {
    cr_assert_eq((Tristate::False && Tristate::False), Tristate::False);
}

Test(TristateAnd, true_and_undefined) {
    cr_assert_eq((Tristate::True && Tristate::Undefined), Tristate::Undefined);
}

Test(TristateAnd, undefined_and_true) {
    cr_assert_eq((Tristate::Undefined && Tristate::True), Tristate::Undefined);
}

Test(TristateAnd, false_and_undefined) {
    cr_assert_eq((Tristate::False && Tristate::Undefined), Tristate::False);
}

Test(TristateAnd, undefined_and_false) {
    cr_assert_eq((Tristate::Undefined && Tristate::False), Tristate::False);
}

Test(TristateAnd, undefined_and_undefined) {
    cr_assert_eq((Tristate::Undefined && Tristate::Undefined), Tristate::Undefined);
}

Test(TristateOr, true_or_true) {
    cr_assert_eq((Tristate::True || Tristate::True), Tristate::True);
}

Test(TristateOr, true_or_false) {
    cr_assert_eq((Tristate::True || Tristate::False), Tristate::True);
}

Test(TristateOr, false_or_true) {
    cr_assert_eq((Tristate::False || Tristate::True), Tristate::True);
}

Test(TristateOr, false_or_false) {
    cr_assert_eq((Tristate::False || Tristate::False), Tristate::False);
}

Test(TristateOr, true_or_undefined) {
    cr_assert_eq((Tristate::True || Tristate::Undefined), Tristate::True);
}

Test(TristateOr, undefined_or_true) {
    cr_assert_eq((Tristate::Undefined || Tristate::True), Tristate::True);
}

Test(TristateOr, false_or_undefined) {
    cr_assert_eq((Tristate::False || Tristate::Undefined), Tristate::Undefined);
}

Test(TristateOr, undefined_or_false) {
    cr_assert_eq((Tristate::Undefined || Tristate::False), Tristate::Undefined);
}

Test(TristateOr, undefined_or_undefined) {
    cr_assert_eq((Tristate::Undefined || Tristate::Undefined), Tristate::Undefined);
}

Test(TristateXor, true_xor_true) {
    cr_assert_eq((Tristate::True ^ Tristate::True), Tristate::False);
}

Test(TristateXor, true_xor_false) {
    cr_assert_eq((Tristate::True ^ Tristate::False), Tristate::True);
}

Test(TristateXor, false_xor_true) {
    cr_assert_eq((Tristate::False ^ Tristate::True), Tristate::True);
}

Test(TristateXor, false_xor_false) {
    cr_assert_eq((Tristate::False ^ Tristate::False), Tristate::False);
}

Test(TristateXor, true_xor_undefined) {
    cr_assert_eq((Tristate::True ^ Tristate::Undefined), Tristate::Undefined);
}

Test(TristateXor, undefined_xor_true) {
    cr_assert_eq((Tristate::Undefined ^ Tristate::True), Tristate::Undefined);
}

Test(TristateXor, false_xor_undefined) {
    cr_assert_eq((Tristate::False ^ Tristate::Undefined), Tristate::Undefined);
}

Test(TristateXor, undefined_xor_undefined) {
    cr_assert_eq((Tristate::Undefined ^ Tristate::Undefined), Tristate::Undefined);
}

Test(Utils, trim_simple) {
    cr_assert_str_eq(Utils::trim("  hello  ").c_str(), "hello");
}

Test(Utils, trim_tabs_and_newlines) {
    cr_assert_str_eq(Utils::trim("\t\nhello\t\n").c_str(), "hello");
}

Test(Utils, trim_empty_string) {
    cr_assert_str_eq(Utils::trim("   ").c_str(), "");
}

Test(Utils, trim_with_comment) {
    cr_assert_str_eq(Utils::trim("hello #world").c_str(), "hello ");
}

Test(Utils, trim_only_comment) {
    cr_assert_str_eq(Utils::trim("#comment").c_str(), "");
}

Test(Utils, valid_whitespace_spaces) {
    cr_assert(Utils::is_valid_whitespace("   "));
}

Test(Utils, valid_whitespace_tabs) {
    cr_assert(Utils::is_valid_whitespace("\t\t"));
}

Test(Utils, valid_whitespace_newlines) {
    cr_assert(Utils::is_valid_whitespace("\n\n"));
}

Test(Utils, valid_whitespace_mixed) {
    cr_assert(Utils::is_valid_whitespace(" \t\n "));
}

Test(Utils, valid_whitespace_with_text) {
    cr_assert(Utils::is_valid_whitespace("abc"));
}

Test(Utils, string_to_tristate_0) {
    cr_assert_eq(Utils::stringToTristate("0"), Tristate::False);
}

Test(Utils, string_to_tristate_1) {
    cr_assert_eq(Utils::stringToTristate("1"), Tristate::True);
}

Test(Utils, string_to_tristate_U) {
    cr_assert_eq(Utils::stringToTristate("U"), Tristate::Undefined);
}

Test(Utils, string_to_tristate_invalid) {
    cr_assert_throw(Utils::stringToTristate("X"), NanoTekSpiceException);
}

Test(Utils, string_to_tristate_invalid_number) {
    cr_assert_throw(Utils::stringToTristate("2"), NanoTekSpiceException);
}

Test(Utils, get_binary_value_idx_bit1_of_5) {

    cr_assert_eq(Utils::getBinaryValueIdx(1, 5), 1);
}

Test(Utils, get_binary_value_idx_bit2_of_5) {

    cr_assert_eq(Utils::getBinaryValueIdx(2, 5), 0);
}

Test(Utils, get_binary_value_idx_bit3_of_5) {

    cr_assert_eq(Utils::getBinaryValueIdx(3, 5), 1);
}

Test(Utils, get_binary_value_idx_negative_value) {
    cr_assert_eq(Utils::getBinaryValueIdx(1, -1), -1);
}

Test(Utils, get_binary_value_idx_zero) {
    cr_assert_eq(Utils::getBinaryValueIdx(1, 0), 0);
}

Test(Utils, get_binary_value_idx_all_bits_255) {

    for (size_t i = 1; i <= 8; i++)
        cr_assert_eq(Utils::getBinaryValueIdx(i, 255), 1);
}

