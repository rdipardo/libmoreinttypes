#include <iostream>
#include <cstring>
#include <moreinttypes/utils.h>
using namespace std;

int main()
{
    cout << "Calling rtrim() with a stack-allocated string -- char[]" << endl;
    cout << "-------------------------------------------------------" << endl;

    char text[] = "hello             ";
    cout << "Before: "
         << "\"" << text << "\"" << endl;
    rtrim(text);
    cout << "After: "
         << "\"" << text << "\"" << endl
         << endl;

    cout << "Calling rtrim() with a dynamically allocated string -- char*"
         << endl;
    cout << "------------------------------------------------------------"
         << endl;

    char src_text[] = "hello             ";
    size_t len = strlen(src_text) + 1;
    char* allocd_text = (char*)malloc(sizeof(char) * len);
    memset(allocd_text, 0, len);
    snprintf(allocd_text, len, "%s", src_text);

    cout << "Before: "
         << "\"" << allocd_text << "\"" << endl;
    rtrim(allocd_text);
    cout << "After: "
         << "\"" << allocd_text << "\"" << endl;

    free(allocd_text);
    allocd_text == NULL;

    cout << "====================== FINISHED ============================"
         << endl;
    return 0;
}
