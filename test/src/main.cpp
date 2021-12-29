#include "CppUTest/CommandLineTestRunner.h"

int main(int argc, char** argv)
{
// https://github.com/cpputest/cpputest/issues/1073#issuecomment-701614494
#ifdef VALGRIND
    MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
#endif
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
