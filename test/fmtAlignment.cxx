#include "../libBuild/tmp/fmt.hpp"
#include "assert.h"
using namespace tmp::fmt;

void testAlignment()
{
    ::assert(Format("{<4}", 42), "42  ");
    ::assert(Format("{>4}", 42), "  42");
    ::assert(Format("{^<4}", 42), " 42 ");

    ::assert(Format("{:<10}", 3.1415), "3.1415    ");
    ::assert(Format("{:>10}", 3.1415), "    3.1415");
    ::assert(Format("{:^<10}", 3.1415), "  3.1415  ");
}

int main()
{
    ::testAlignment();
    return 0;
}