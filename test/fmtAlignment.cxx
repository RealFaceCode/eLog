#include "../libBuild/hdr/fmt/fmt.hpp"
#include "assert.h"
using namespace elog::fmt;

void testAlignment()
{
    ::assert(Format("|{<4}|", 42), "|42  |");
    ::assert(Format("|{>4}|", 42), "|  42|");
    ::assert(Format("|{^<4}|", 42), "| 42 |");

    ::assert(Format("|{:<10}|", 3.1415f), "|3.1415    |");
    ::assert(Format("|{:>10}|", 3.1415f), "|    3.1415|");
    ::assert(Format("|{:^<10}|", 3.1415f), "|  3.1415  |");
}

int main()
{
    ::testAlignment();
    return 0;
}