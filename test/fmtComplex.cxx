#include "../libBuild/hdr/fmt/fmt.hpp"
#include "assert.h"
using namespace elog::fmt;

void textComplex()
{
    ::assert(Format("|{0:<4d}|", 42), "|42  |");
    ::assert(Format("|{0:^<4d}|", 42), "| 42 |");
    ::assert(Format("|{0:>4d}|", 42), "|  42|");
    ::assert(Format("|{.2}|", 42.12345), "|42.12|");
    ::assert(Format("|{.4>10}|", 42), "|      0042|");
    ::assert(Format("|{e}|", 42), "|4.200000e+01|");
    ::assert(Format("|{e}|", 42.3f), "|4.230000e+01|");
    ::assert(Format("|{e.2}|", 42.3f), "|4.23e+01|");
    ::assert(Format("|{e.2^<10}|", 42.3), "| 4.23e+01 |");
    ::assert(Format("|{n}|", 123456789), "|123'456'789|");
    ::assert(Format("|{1:d}, {0:.4}|", 1, 2), "|2, 0001|");
}

int main()
{
    ::textComplex();
    return 0;
}