#include <iostream>
#include <moreinttypes/core.h>
using namespace std;

int main()
{
    Int32 i = integer(122333333);

    cout << i.value << endl;
    // i.value = 0;
    //
    // error: assignment of read-only member ‘value’
    //   i.value = 0;
    //           ^

    from_string(i, "10101010", 2);
    cout << "New value: " << i.value << endl;

    cout << as_binary(i) << endl;

    from_string(i, "6", 10);
    long double f = factorial(i);
    cout << i.value << "! = " << f << endl;

    int value = parse_int("10101010", 2);
    cout << value << endl;

    cout << "====================== FINISHED ======================" << endl;
    return 0;
}
