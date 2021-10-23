#include "CppUTest/TestHarness.h"
#include "moreinttypes/core.h"

TEST_GROUP(TestMoreinttypesCoreH){};

TEST(TestMoreinttypesCoreH, ConstructInt32)
{
    Int32 i = integer(122333333);
    CHECK_EQUAL(122333333, i.value);
}

TEST(TestMoreinttypesCoreH, ConstructInt64)
{
    Int64 i = integer64(0x200000000);
    CHECK_EQUAL(0x200000000, i.value);
}

TEST(TestMoreinttypesCoreH, ParseIntFromBinaryString)
{
    Int32 i = integer(0);
    from_string(i, "10101010", 2);
    CHECK_EQUAL(170, i.value);
}

TEST(TestMoreinttypesCoreH, ParseIntFromOctalString)
{
    Int32 i = integer(0);
    from_string(i, "252", 8);
    CHECK_EQUAL(170, i.value);
}

TEST(TestMoreinttypesCoreH, ParseIntFromDecimalString)
{
    Int32 i = integer(0);
    from_string(i, "170", 10);
    CHECK_EQUAL(170, i.value);
}

TEST(TestMoreinttypesCoreH, ParseIntFromHexString)
{
    Int32 i = integer(0);
    from_string(i, "Aa", 16);
    CHECK_EQUAL(170, i.value);
}

TEST(TestMoreinttypesCoreH, ParseInt64FromHexString)
{
    const uint64_t value = 0xFFFFFFFFFFFFFFF;
    Int64 i = integer64(0);
    from_string(i, "FFFFFFFFFFFFFFF", 16);
    CHECK_EQUAL(value, i.value);
}

TEST(TestMoreinttypesCoreH, ParseIntValidatesInput)
{
    Int32 i = integer(12);
    from_string(i, "", 2);
    CHECK_EQUAL(12, i.value);
}

TEST(TestMoreinttypesCoreH, ParseIntValidatesBase)
{
    Int32 i = integer(122);
    from_string(i, "abcd", 10);
    CHECK_EQUAL(122, i.value);
}

TEST(TestMoreinttypesCoreH, ParseIntChecksBounds)
{
    Int64 i = integer64(1);
    from_string(i, "FFFFFFFFFFFFFFFFFFFFFFFF", 16);
    CHECK_EQUAL(1, i.value);
}

TEST(TestMoreinttypesCoreH, FactorialOfZero)
{
    Int32 i = integer(0);
    const double f = (double)factorial(i);
    DOUBLES_EQUAL(1.0, f, 0.1);
}

TEST(TestMoreinttypesCoreH, FactorialOfSix)
{
    Int32 i = integer(6);
    const double f = (double)factorial(i);
    DOUBLES_EQUAL(720.0, f, 0.1);
}

TEST(TestMoreinttypesCoreH, FactorialOfChecksBounds)
{
    Int32 i = integer(0x1000);
    const double f = factorial(i);
    DOUBLES_EQUAL(0.0, f, 0.1);
}

TEST(TestMoreinttypesCoreH, FactorialChecksBoundsGivenNegativeInput)
{
    Int32 i = integer(-1);
    const double f = factorial(i);
    DOUBLES_EQUAL(0.0, f, 0.1);
}

TEST(TestMoreinttypesCoreH, Factorial64ChecksBoundsGivenNegativeInput)
{
    Int64 i = integer64(-1);
    const double f = factorial(i);
    DOUBLES_EQUAL(0.0, f, 0.1);
}
