#include <iomanip>
#include "TestHelpers.h"
#include "moreinttypes/utils.h"

void TestHelpers::factorial_to_string(int n, std::stringstream& buf)
{
    long double f = MATCH_ARCH(factorial_of)(n);
    buf.setf(std::ios::fixed, std::ios::floatfield);
    buf.precision(0);
    buf << std::setfill('0') << f;
}
