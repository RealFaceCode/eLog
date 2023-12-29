#include "../libBuild/fmt.hpp"
using namespace eLog::fmt;

void testAlignment()
{
    assert(format("{<4}", 42), "42  ");
    assert(format("{>4}", 42), "  42");
    assert(format("{^<4}", 42), " 42 ");

    assert(format("{:<10}", 3.1415), "3.1415    ");
    assert(format("{:>10}", 3.1415), "    3.1415");
    assert(format("{:^<10}", 3.1415), "  3.1415  ");
}

int main()
{
    ::testAlignment();
    return 0;
}