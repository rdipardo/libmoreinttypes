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