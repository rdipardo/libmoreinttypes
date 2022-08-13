#include "suites.h"

int main(void)
{
    Suite* int_types_suite = test_int_types();
    Suite* math_lib_suite = test_math_lib();
    Suite* string_lib_suite = test_string_lib();
    SRunner* sr = srunner_create(int_types_suite);
    srunner_add_suite(sr, math_lib_suite);
    srunner_add_suite(sr, string_lib_suite);
    int verbosity = CK_NORMAL;
/*
 * https://libcheck.github.io/check/doc/check_html/check_4.html#Finding-Memory-Leaks
 */
#ifdef VALGRIND
    srunner_set_fork_status(sr, CK_NOFORK);
#endif
    srunner_run_all(sr, verbosity);
    int fail_count = srunner_ntests_failed(sr);
    srunner_free(sr);
    return fail_count;
}
