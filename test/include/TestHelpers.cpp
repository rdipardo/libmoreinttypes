#include <sstream>
#include <iomanip>
#include <moreinttypes/utils.h>
#include "TestHelpers.h"

int factorial_equals(int n, const char* szFactorial)
{
    const long double f = MATCH_ARCH(factorial_of)(n);
    std::stringstream buf;
    buf.setf(std::ios::fixed, std::ios::floatfield);
    buf.precision(0);
    buf << std::setfill('0') << f;
    return static_cast<int>(buf.str().compare(szFactorial) == 0);
}
