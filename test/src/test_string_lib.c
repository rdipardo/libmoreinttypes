#include "suites.h"
#include "moreinttypes/utils.h"

START_TEST(ChompStripsDosEOLs)
{
    char text[] = "Raw input\r\n\r\n\r\n";
    chomp(text);
    ck_assert_str_eq("Raw input", text);
}

START_TEST(ChompStripsUnixEOLs)
{
    char text[] = "Raw input\n\n\n";
    chomp(text);
    ck_assert_str_eq("Raw input", text);
}

START_TEST(ChompStripsMacEOLs)
{
    char text[] = "Raw input\r\r\r";
    chomp(text);
    ck_assert_str_eq("Raw input", text);
}

START_TEST(ChompStripsNewlinesFromOtherwiseEmptyStrings)
{
    char text[] = "\r\n\r\n\r\n";
    chomp(text);
    ck_assert_str_eq("", text);
}

START_TEST(ChompLeavesEmptyStringsUnchanged)
{
    char text[] = "";
    chomp(text);
    ck_assert_str_eq("", text);
}

START_TEST(ChompLeavesLeadingSpaceUnchanged)
{
    char text[] = "\r\n\t\t\r\n\t\r\n\t \tRaw input\r\n\r\n\r\n";
    chomp(text);
    ck_assert_str_eq("\r\n\t\t\r\n\t\r\n\t \tRaw input", text);
}

START_TEST(RtrimRemovesRightEndSpaces)
{
    char text[] = "hello             ";
    rtrim(text);
    ck_assert_str_eq("hello", text);
}

START_TEST(RtrimTrimsASingleCharString)
{
    char text[] = "a ";
    rtrim(text);
    ck_assert_str_eq("a", text);
}

START_TEST(RtrimLeavesEmptyStringsUnchanged)
{
    char text[] = "";
    rtrim(text);
    ck_assert_str_eq("", text);
}

START_TEST(RtrimLeavesStringUnchanged)
{
    char text[] = " a";
    rtrim(text);
    ck_assert_str_eq(" a", text);
}

START_TEST(RtrimSingleSpaceString)
{
    char text[] = " ";
    rtrim(text);
    ck_assert_str_eq("", text);
}

START_TEST(RtrimRORemovesRightEndSpaces)
{
    const char* text = "hello             ";
    char buf[128] = { 0 };
    rtrim_s(buf, text);
    ck_assert_str_eq("hello             ", text);
    ck_assert_str_eq("hello", buf);
}

START_TEST(RtrimROLeavesEmptyStringsUnchanged)
{
    const char* text = "";
    char buf[128] = { 0 };
    rtrim_s(buf, text);
    ck_assert_str_eq("", text);
    ck_assert_str_eq("", buf);
}

START_TEST(RtrimROLeavesStringUnchanged)
{
    const char* text = " a";
    char buf[128] = { 0 };
    rtrim_s(buf, text);
    ck_assert_str_eq(" a", text);
    ck_assert_str_eq(" a", buf);
}

START_TEST(RtrimROSingleCharString)
{
    const char* text = "a ";
    char buf[128] = { 0 };
    rtrim_s(buf, text);
    ck_assert_str_eq("a ", text);
    ck_assert_str_eq("a", buf);
}

START_TEST(RtrimROSingleSpaceString)
{
    const char* text = " ";
    char buf[128] = { 0 };
    rtrim_s(buf, text);
    ck_assert_str_eq(" ", text);
    ck_assert_str_eq("", buf);
}

START_TEST(LtrimRemovesLeftEndSpaces)
{
    char text[] = "             hello";
    ltrim(text);
    ck_assert_str_eq("hello", text);
}

START_TEST(LtrimLeavesEmptyStringsUnchanged)
{
    char text[] = "";
    ltrim(text);
    ck_assert_str_eq("", text);
}

START_TEST(LtrimLeavesStringUnchanged)
{
    char text[] = "a ";
    ltrim(text);
    ck_assert_str_eq("a ", text);
}

START_TEST(LtrimSingleCharString)
{
    char text[] = " a";
    ltrim(text);
    ck_assert_str_eq("a", text);
}

START_TEST(LtrimSingleSpaceString)
{
    char text[] = " ";
    ltrim(text);
    ck_assert_str_eq("", text);
}

START_TEST(LtrimRORemovesLeftEndSpaces)
{
    const char* text = "             hello";
    char buf[128] = { 0 };
    ltrim_s(buf, text);
    ck_assert_str_eq("             hello", text);
    ck_assert_str_eq("hello", buf);
}

START_TEST(LtrimROLeavesEmptyStringsUnchanged)
{
    const char* text = "";
    char buf[128] = { 0 };
    ltrim_s(buf, text);
    ck_assert_str_eq("", text);
    ck_assert_str_eq("", buf);
}

START_TEST(LtrimROLeavesStringUnchanged)
{
    const char* text = "a ";
    char buf[128] = { 0 };
    ltrim_s(buf, text);
    ck_assert_str_eq("a ", text);
    ck_assert_str_eq("a ", buf);
}

START_TEST(LtrimROSingleCharString)
{
    const char* text = " a";
    char buf[128] = { 0 };
    ltrim_s(buf, text);
    ck_assert_str_eq(" a", text);
    ck_assert_str_eq("a", buf);
}

START_TEST(LtrimROSingleSpaceString)
{
    const char* text = " ";
    char buf[128] = { 0 };
    ltrim_s(buf, text);
    ck_assert_str_eq(" ", text);
    ck_assert_str_eq("", buf);
}

START_TEST(TrimRemovesRightEndSpaces)
{
    char text[] = "hello             ";
    trim(text);
    ck_assert_str_eq("hello", text);
}

START_TEST(TrimRemovesLeftEndSpaces)
{
    char text[] = "             hello";
    trim(text);
    ck_assert_str_eq("hello", text);
}

START_TEST(TrimLeavesEmptyStringsUnchanged)
{
    char text[] = "";
    trim(text);
    ck_assert_str_eq("", text);
}

START_TEST(TrimLeavesStringUnchanged)
{
    char text[] = "a";
    trim(text);
    ck_assert_str_eq("a", text);
}

START_TEST(TrimSingleCharRightString)
{
    char text[] = "a ";
    trim(text);
    ck_assert_str_eq("a", text);
}

START_TEST(TrimSingleCharLeftString)
{
    char text[] = " a";
    trim(text);
    ck_assert_str_eq("a", text);
}

START_TEST(TrimSingleSpaceString)
{
    char text[] = " ";
    trim(text);
    ck_assert_str_eq("", text);
}

START_TEST(TrimRORemovesRightEndSpaces)
{
    const char* text = "hello             ";
    char buf[128] = { 0 };
    trim_s(buf, text);
    ck_assert_str_eq("hello             ", text);
    ck_assert_str_eq("hello", buf);
}

START_TEST(TrimRORemovesLeftEndSpaces)
{
    const char* text = "             hello";
    char buf[128] = { 0 };
    trim_s(buf, text);
    ck_assert_str_eq("             hello", text);
    ck_assert_str_eq("hello", buf);
}

START_TEST(TrimROLeavesEmptyStringsUnchanged)
{
    const char* text = "";
    char buf[128] = { 0 };
    trim_s(buf, text);
    ck_assert_str_eq("", text);
    ck_assert_str_eq("", buf);
}

START_TEST(TrimROLeavesStringUnchanged)
{
    const char* text = "a";
    char buf[128] = { 0 };
    trim_s(buf, text);
    ck_assert_str_eq("a", text);
    ck_assert_str_eq("a", buf);
}

START_TEST(TrimROSingleCharRightString)
{
    const char* text = "a ";
    char buf[128] = { 0 };
    trim_s(buf, text);
    ck_assert_str_eq("a ", text);
    ck_assert_str_eq("a", buf);
}

START_TEST(TrimROSingleCharLeftString)
{
    const char* text = " a";
    char buf[128] = { 0 };
    trim_s(buf, text);
    ck_assert_str_eq(" a", text);
    ck_assert_str_eq("a", buf);
}

START_TEST(TrimROSingleSpaceString)
{
    const char* text = " ";
    char buf[128] = { 0 };
    trim_s(buf, text);
    ck_assert_str_eq(" ", text);
    ck_assert_str_eq("", buf);
}

Suite* test_string_lib(void)
{
    Suite* suite;
    TCase* tc_utils;
    suite = suite_create("Strings");
    tc_utils = tcase_create("Utils");

    /* chomp() */
    tcase_add_test(tc_utils, ChompStripsDosEOLs);
    tcase_add_test(tc_utils, ChompStripsUnixEOLs);
    tcase_add_test(tc_utils, ChompStripsMacEOLs);
    tcase_add_test(tc_utils, ChompStripsNewlinesFromOtherwiseEmptyStrings);
    tcase_add_test(tc_utils, ChompLeavesEmptyStringsUnchanged);
    tcase_add_test(tc_utils, ChompLeavesLeadingSpaceUnchanged);

    /* rtrim() */
    tcase_add_test(tc_utils, RtrimRemovesRightEndSpaces);
    tcase_add_test(tc_utils, RtrimTrimsASingleCharString);
    tcase_add_test(tc_utils, RtrimLeavesEmptyStringsUnchanged);
    tcase_add_test(tc_utils, RtrimLeavesStringUnchanged);
    tcase_add_test(tc_utils, RtrimSingleSpaceString);
    tcase_add_test(tc_utils, RtrimRORemovesRightEndSpaces);
    tcase_add_test(tc_utils, RtrimROLeavesEmptyStringsUnchanged);
    tcase_add_test(tc_utils, RtrimROLeavesStringUnchanged);
    tcase_add_test(tc_utils, RtrimROSingleCharString);
    tcase_add_test(tc_utils, RtrimROSingleSpaceString);

    /*  ltrim() */
    tcase_add_test(tc_utils, LtrimRemovesLeftEndSpaces);
    tcase_add_test(tc_utils, LtrimLeavesEmptyStringsUnchanged);
    tcase_add_test(tc_utils, LtrimLeavesStringUnchanged);
    tcase_add_test(tc_utils, LtrimSingleCharString);
    tcase_add_test(tc_utils, LtrimSingleSpaceString);
    tcase_add_test(tc_utils, LtrimRORemovesLeftEndSpaces);
    tcase_add_test(tc_utils, LtrimROLeavesEmptyStringsUnchanged);
    tcase_add_test(tc_utils, LtrimROLeavesStringUnchanged);
    tcase_add_test(tc_utils, LtrimROSingleCharString);
    tcase_add_test(tc_utils, LtrimROSingleSpaceString);

    /* trim() */
    tcase_add_test(tc_utils, TrimRemovesRightEndSpaces);
    tcase_add_test(tc_utils, TrimRemovesLeftEndSpaces);
    tcase_add_test(tc_utils, TrimLeavesEmptyStringsUnchanged);
    tcase_add_test(tc_utils, TrimLeavesStringUnchanged);
    tcase_add_test(tc_utils, TrimSingleCharRightString);
    tcase_add_test(tc_utils, TrimSingleCharLeftString);
    tcase_add_test(tc_utils, TrimSingleSpaceString);
    tcase_add_test(tc_utils, TrimRORemovesRightEndSpaces);
    tcase_add_test(tc_utils, TrimRORemovesLeftEndSpaces);
    tcase_add_test(tc_utils, TrimROLeavesEmptyStringsUnchanged);
    tcase_add_test(tc_utils, TrimROLeavesStringUnchanged);
    tcase_add_test(tc_utils, TrimROSingleCharRightString);
    tcase_add_test(tc_utils, TrimROSingleCharLeftString);
    tcase_add_test(tc_utils, TrimROSingleSpaceString);

    suite_add_tcase(suite, tc_utils);
    return suite;
}
