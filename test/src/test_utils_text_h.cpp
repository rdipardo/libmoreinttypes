#include <cstring>
#include "CppUTest/TestHarness.h"
#include "moreinttypes/utils.h"

TEST_GROUP(Strings){};

TEST(Strings, ChompStripsDosEOLs)
{
    char text[] = "Raw input\r\n\r\n\r\n";
    chomp(text);
    STRCMP_EQUAL("Raw input", text);
}

TEST(Strings, ChompStripsUnixEOLs)
{
    char text[] = "Raw input\n\n\n";
    chomp(text);
    STRCMP_EQUAL("Raw input", text);
}

TEST(Strings, ChompStripsMacEOLs)
{
    char text[] = "Raw input\r\r\r";
    chomp(text);
    STRCMP_EQUAL("Raw input", text);
}

TEST(Strings, ChompStripsNewlinesFromOtherwiseEmptyStrings)
{
    char text[] = "\r\n\r\n\r\n";
    chomp(text);
    STRCMP_EQUAL("", text);
}

TEST(Strings, ChompLeavesEmptyStringsUnchanged)
{
    char text[] = "";
    chomp(text);
    STRCMP_EQUAL("", text);
}

TEST(Strings, ChompLeavesLeadingSpaceUnchanged)
{
    char text[] = "\r\n\t\t\r\n\t\r\n\t \tRaw input\r\n\r\n\r\n";
    chomp(text);
    STRCMP_EQUAL("\r\n\t\t\r\n\t\r\n\t \tRaw input", text);
}

TEST(Strings, RtrimRemovesRightEndSpaces)
{
    char text[] = "hello             ";
    rtrim(text);
    STRCMP_EQUAL("hello", text);
}

TEST(Strings, RtrimLeavesEmptyStringsUnchanged)
{
    char text[] = "";
    rtrim(text);
    STRCMP_EQUAL("", text);
}

TEST(Strings, RtrimLeavesStringUnchanged)
{
    char text[] = " a";
    rtrim(text);
    STRCMP_EQUAL(" a", text);
}

TEST(Strings, RtrimSingleCharString)
{
    char text[] = "a ";
    rtrim(text);
    STRCMP_EQUAL("a", text);
}

TEST(Strings, RtrimSingleSpaceString)
{
    char text[] = " ";
    rtrim(text);
    STRCMP_EQUAL("", text);
}

TEST(Strings, RtrimRORemovesRightEndSpaces)
{
    const char* text = "hello             ";
    char buf[128] = { 0 };
    rtrim_s(buf, text);
    STRCMP_EQUAL("hello             ", text);
    STRCMP_EQUAL("hello", buf);
}

TEST(Strings, RtrimROLeavesEmptyStringsUnchanged)
{
    const char* text = "";
    char buf[128] = { 0 };
    rtrim_s(buf, text);
    STRCMP_EQUAL("", text);
    STRCMP_EQUAL("", buf);
}

TEST(Strings, RtrimROLeavesStringUnchanged)
{
    const char* text = " a";
    char buf[128] = { 0 };
    rtrim_s(buf, text);
    STRCMP_EQUAL(" a", text);
    STRCMP_EQUAL(" a", buf);
}

TEST(Strings, RtrimROSingleCharString)
{
    const char* text = "a ";
    char buf[128] = { 0 };
    rtrim_s(buf, text);
    STRCMP_EQUAL("a ", text);
    STRCMP_EQUAL("a", buf);
}

TEST(Strings, RtrimROSingleSpaceString)
{
    const char* text = " ";
    char buf[128] = { 0 };
    rtrim_s(buf, text);
    STRCMP_EQUAL(" ", text);
    STRCMP_EQUAL("", buf);
}

TEST(Strings, LtrimRemovesLeftEndSpaces)
{
    char text[] = "             hello";
    ltrim(text);
    STRCMP_EQUAL("hello", text);
}

TEST(Strings, LtrimLeavesEmptyStringsUnchanged)
{
    char text[] = "";
    ltrim(text);
    STRCMP_EQUAL("", text);
}

TEST(Strings, LtrimLeavesStringUnchanged)
{
    char text[] = "a ";
    ltrim(text);
    STRCMP_EQUAL("a ", text);
}

TEST(Strings, LtrimSingleCharString)
{
    char text[] = " a";
    ltrim(text);
    STRCMP_EQUAL("a", text);
}

TEST(Strings, LtrimSingleSpaceString)
{
    char text[] = " ";
    ltrim(text);
    STRCMP_EQUAL("", text);
}

TEST(Strings, LtrimRORemovesLeftEndSpaces)
{
    const char* text = "             hello";
    char buf[128] = { 0 };
    ltrim_s(buf, text);
    STRCMP_EQUAL("             hello", text);
    STRCMP_EQUAL("hello", buf);
}

TEST(Strings, LtrimROLeavesEmptyStringsUnchanged)
{
    const char* text = "";
    char buf[128] = { 0 };
    ltrim_s(buf, text);
    STRCMP_EQUAL("", text);
    STRCMP_EQUAL("", buf);
}

TEST(Strings, LtrimROLeavesStringUnchanged)
{
    const char* text = "a ";
    char buf[128] = { 0 };
    ltrim_s(buf, text);
    STRCMP_EQUAL("a ", text);
    STRCMP_EQUAL("a ", buf);
}

TEST(Strings, LtrimROSingleCharString)
{
    const char* text = " a";
    char buf[128] = { 0 };
    ltrim_s(buf, text);
    STRCMP_EQUAL(" a", text);
    STRCMP_EQUAL("a", buf);
}

TEST(Strings, LtrimROSingleSpaceString)
{
    const char* text = " ";
    char buf[128] = { 0 };
    ltrim_s(buf, text);
    STRCMP_EQUAL(" ", text);
    STRCMP_EQUAL("", buf);
}

TEST(Strings, TrimRemovesRightEndSpaces)
{
    char text[] = "hello             ";
    trim(text);
    STRCMP_EQUAL("hello", text);
}

TEST(Strings, TrimRemovesLeftEndSpaces)
{
    char text[] = "             hello";
    trim(text);
    STRCMP_EQUAL("hello", text);
}

TEST(Strings, TrimLeavesEmptyStringsUnchanged)
{
    char text[] = "";
    trim(text);
    STRCMP_EQUAL("", text);
}

TEST(Strings, TrimLeavesStringUnchanged)
{
    char text[] = "a";
    trim(text);
    STRCMP_EQUAL("a", text);
}

TEST(Strings, TrimSingleCharRightString)
{
    char text[] = "a ";
    trim(text);
    STRCMP_EQUAL("a", text);
}

TEST(Strings, TrimSingleCharLeftString)
{
    char text[] = " a";
    trim(text);
    STRCMP_EQUAL("a", text);
}

TEST(Strings, TrimSingleSpaceString)
{
    char text[] = " ";
    trim(text);
    STRCMP_EQUAL("", text);
}

TEST(Strings, TrimRORemovesRightEndSpaces)
{
    const char* text = "hello             ";
    char buf[128] = { 0 };
    trim_s(buf, text);
    STRCMP_EQUAL("hello             ", text);
    STRCMP_EQUAL("hello", buf);
}

TEST(Strings, TrimRORemovesLeftEndSpaces)
{
    const char* text = "             hello";
    char buf[128] = { 0 };
    trim_s(buf, text);
    STRCMP_EQUAL("             hello", text);
    STRCMP_EQUAL("hello", buf);
}

TEST(Strings, TrimROLeavesEmptyStringsUnchanged)
{
    const char* text = "";
    char buf[128] = { 0 };
    trim_s(buf, text);
    STRCMP_EQUAL("", text);
    STRCMP_EQUAL("", buf);
}

TEST(Strings, TrimROLeavesStringUnchanged)
{
    const char* text = "a";
    char buf[128] = { 0 };
    trim_s(buf, text);
    STRCMP_EQUAL("a", text);
    STRCMP_EQUAL("a", buf);
}

TEST(Strings, TrimROSingleCharRightString)
{
    const char* text = "a ";
    char buf[128] = { 0 };
    trim_s(buf, text);
    STRCMP_EQUAL("a ", text);
    STRCMP_EQUAL("a", buf);
}

TEST(Strings, TrimROSingleCharLeftString)
{
    const char* text = " a";
    char buf[128] = { 0 };
    trim_s(buf, text);
    STRCMP_EQUAL(" a", text);
    STRCMP_EQUAL("a", buf);
}

TEST(Strings, TrimROSingleSpaceString)
{
    const char* text = " ";
    char buf[128] = { 0 };
    trim_s(buf, text);
    STRCMP_EQUAL(" ", text);
    STRCMP_EQUAL("", buf);
}