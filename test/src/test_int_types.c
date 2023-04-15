#include "suites.h"
#include "moreinttypes/core.h"

START_TEST(CallInt32Constructor)
{
    Int32 i = integer(122333333);
    ck_assert_int_eq(122333333, i.value);
}

START_TEST(CallInt64Constructor)
{
    Int64 i = integer64(0x200000000);
    ck_assert(0x200000000 == i.value);
}

START_TEST(ParseIntFromBinaryString)
{
    Int32 i = integer(0);
    from_string(i, "10101010", 2);
    ck_assert_int_eq(170, i.value);
}

START_TEST(ParseIntFromOctalString)
{
    Int32 i = integer(0);
    from_string(i, "252", 8);
    ck_assert_int_eq(170, i.value);
}

START_TEST(ParseIntFromDecimalString)
{
    Int32 i = integer(0);
    from_string(i, "170", 10);
    ck_assert_int_eq(170, i.value);
}

START_TEST(ParseIntFromHexString)
{
    Int32 i = integer(0);
    from_string(i, "Aa", 16);
    ck_assert_int_eq(170, i.value);
}

START_TEST(ParseInt64FromHexString)
{
    const int64_t value = 0xFFFFFFFFFFFFFFF;
    Int64 i = integer64(0);
    from_string(i, "FFFFFFFFFFFFFFF", 16);
    ck_assert(value == i.value);
}

START_TEST(ParseIntValidatesInput)
{
    Int32 i = integer(12);
    from_string(i, "", 2);
    ck_assert_int_eq(12, i.value);
}

START_TEST(ParseIntValidatesBase)
{
    Int32 i = integer(122);
    from_string(i, "abcd", 10);
    ck_assert_int_eq(122, i.value);
}

START_TEST(ParseIntChecksBounds)
{
    Int64 i = integer64(1);
    from_string(i, "FFFFFFFFFFFFFFFFFFFFFFFF", 16);
    ck_assert_int_eq(1, i.value);
}

START_TEST(FactorialOfZero)
{
    Int32 i = integer(0);
    const long double f = factorial(i);
    ck_assert_ldouble_eq_tol(1.0L, f, 0.1L);
}

START_TEST(FactorialOfSix)
{
    Int32 i = integer(6);
    const long double f = factorial(i);
    ck_assert_ldouble_eq_tol(720.0L, f, 0.1L);
}

START_TEST(FactorialOfChecksBounds)
{
    Int64 i = integer64(0x1000);
    const long double f = factorial(i);
    ck_assert_ldouble_eq_tol(0.0L, f, 0.1L);
}

START_TEST(FactorialOfChecksBoundsGivenNegativeInput)
{
    Int32 i = integer(-1);
    const long double f = factorial(i);
    ck_assert_ldouble_eq_tol(0.0L, f, 0.1L);
}

START_TEST(FactorialOf64ChecksBoundsGivenNegativeInput)
{
    Int64 i = integer64(-1);
    const long double f = factorial(i);
    ck_assert_ldouble_eq_tol(0.0L, f, 0.1L);
}

Suite* test_int_types(void)
{
    Suite* suite;
    TCase* tc_core;
    suite = suite_create("IntTypes");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, CallInt32Constructor);
    tcase_add_test(tc_core, CallInt64Constructor);
    tcase_add_test(tc_core, ParseIntFromBinaryString);
    tcase_add_test(tc_core, ParseIntFromOctalString);
    tcase_add_test(tc_core, ParseIntFromDecimalString);
    tcase_add_test(tc_core, ParseIntFromHexString);
    tcase_add_test(tc_core, ParseInt64FromHexString);
    tcase_add_test(tc_core, ParseIntValidatesInput);
    tcase_add_test(tc_core, ParseIntValidatesBase);
    tcase_add_test(tc_core, ParseIntChecksBounds);
    tcase_add_test(tc_core, FactorialOfZero);
    tcase_add_test(tc_core, FactorialOfSix);
#ifndef VALGRIND
    tcase_add_test(tc_core, FactorialOfChecksBounds);
    tcase_add_test(tc_core, FactorialOfChecksBoundsGivenNegativeInput);
    tcase_add_test(tc_core, FactorialOf64ChecksBoundsGivenNegativeInput);
#endif /* !VALGRIND */
    suite_add_tcase(suite, tc_core);
    return suite;
}
