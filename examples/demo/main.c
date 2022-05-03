#ifdef _MSC_VER
#pragma comment(lib, "moreinttypes.lib")
#endif

#define USE_64_BITS 1
#include <stdio.h>
#include <moreinttypes/core.h>

void test_data_types();
void test_string_lib();
void test_math_lib();

int main()
{
    test_data_types();
    test_string_lib();
    test_math_lib();

    printf("\n====================== FINISHED ======================\n");
    printf("\nPress RETURN to continue . . . ");
    getchar();
    return 0;
}

void test_data_types()
{
    Int32 an_int = integer(122333333);
    Int64 an_int_64 = integer64(0x77F9FE);
    UInt32 ui32 = uinteger(0xFFFFFFFF);
    UInt64 ui64 = uinteger64(0);

    if (sizeof(uint64_t) == 4)
        from_string(ui64, "0xFFFFFFFF", 16);
    else
        from_string(ui64, "0xEFFFFFFFFFFFFFFF", 16);

    printf("\n---------------- (U)Int32 ----------------\n");
    puts("------------------------------------------");
    puts("------------- Bounds Checking ------------");
    puts("------------------------------------------");
    from_string(an_int, "abcd", 10);
    from_string(an_int, "three", 2);
    from_string(an_int, "", 2);
    from_string(an_int, "FFFFFFFFFFFFFF", 16);
    from_string(ui32, "-12", 10);
    from_string(ui32, "-eff", 16);

    printf("\nCurrent value of Int32 %d\n", an_int.value);
    printf("Current value of UInt32 %u \n", ui32.value);

    from_string(ui32, "7FFFFFFFFFFFFFFF", 16);
    from_string(an_int, "7FFFFFFF", 16);

    printf("\nValue of Int32 now %d.\n", an_int.value);
    printf("Value of UInt32 now %u.\n", ui32.value);

    printf("%d in base-2:\t%40s\n", an_int.value, as_binary(an_int));
    printf("%u in base-2:\t%40s\n", ui32.value, as_binary(ui32));

    from_string(an_int, "6", 10);
    printf("\nValue now %d \n", an_int.value);
    printf("%d! = %.0Lf\n", an_int.value, factorial(an_int));

    from_string(an_int, "10101010", 2);
    printf("New value: %d \n", an_int.value);
    printf("%d! = %.0Lf\n", an_int.value, factorial(an_int));

    printf("\n---------------- (U)Int64 ----------------\n");
    puts("------------------------------------------");
    puts("------------- Bounds Checking ------------");
    puts("------------------------------------------");
    from_string(an_int_64, "abcd", 10);
    from_string(an_int_64, "three", 2);
    from_string(an_int_64, "", 2);
    from_string(an_int_64, "FFFFFFFFFFFFFFFFFFFFFFFF", 16);
    from_string(ui64, "-24", 10);
    from_string(ui64, "-ff7f", 16);

    printf("\nCurrent value of Int64 " INT64_PTR_FMT "\n", an_int_64.value);
    printf("Current value of UInt64 " SIZE_T_FMT "\n", ui64.value);

    from_string(an_int_64, "7FFFFFFFFFFFFFFF", 16);
    from_string(ui64, "FFFFFFFFFFFFFFFF", 16);

    printf("\nValue of Int64 now " INT64_PTR_FMT "\n", an_int_64.value);
    printf("Value of UInt64 now " SIZE_T_FMT "\n", ui64.value);

    printf(INT64_PTR_FMT " in base-2:\t%80s\n", an_int_64.value,
           as_binary(an_int_64));
    printf(SIZE_T_FMT " in base-2:\t%80s\n", ui64.value, as_binary(ui64));

    from_string(an_int_64, "6", 10);
    printf("\nNew value " INT64_PTR_FMT "\n", an_int_64.value);
    printf("" INT64_PTR_FMT "! = %.0Lf\n", an_int_64.value,
           factorial(an_int_64));

    from_string(an_int_64, "11101010", 2);
    printf("New value " INT64_PTR_FMT "\n", an_int_64.value);
    printf("" INT64_PTR_FMT "! = %.0Lf\n", an_int_64.value,
           factorial(an_int_64));
}

void test_math_lib()
{
    printf("\n------------------ Templates -----------------\n");
#ifdef USE_64_BITS
    puts("Using 64-bit versions");
#define FMT INT64_PTR_FMT
#else
    puts("Using 32-bit versions");
#define FMT "%d"
#endif

    printf(FMT "\n", MATCH_ARCH(parse_int)("7FFFFFFF", 16));
    printf(FMT "\n", MATCH_ARCH(parse_int)("7FFFFFFFFFFFFFFF", 16));
    printf("-1! = %.0Lf\n", MATCH_ARCH(factorial_of)(-1));
    printf("0! = %.0Lf\n", MATCH_ARCH(factorial_of)(0));
    printf("170! = %.0Lf\n", MATCH_ARCH(factorial_of)(170));
    printf("1754! = %.0Lf\n", MATCH_ARCH(factorial_of)(1754));
}

void test_string_lib()
{
    char nl[] = "Raw input\n\n";
    char blank[] = "";
    printf("\n----------------- chomp() ----------------\n");

    printf("\nBefore: '%s'\n", nl);
    chomp(nl);
    printf("\n. . . after: '%s'\n", nl);

    printf("\nBefore: '%s'\n", blank);
    chomp(blank);
    printf("\n. . . after: '%s'\n", blank);
}
