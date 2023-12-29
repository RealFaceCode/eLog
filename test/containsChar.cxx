#include "../libBuild/fmt.hpp"
using namespace eLog::fmt;

void test_ContainsChars()
{
    assert(ContainsChars("Hello, World!", "Hd!"), true);
    assert(ContainsChars("Hello, World!", "z!"), false);
    assert(ContainsChars("Hello, World!", "ol"), true);
    assert(ContainsChars("Hello, World!", "eW"), true);
    assert(ContainsChars("{4:2b}", ":b"), true);
}

int main()
{
    ::test_ContainsChars();
    return 0;
}