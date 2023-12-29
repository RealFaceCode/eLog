#include "../libBuild/fmt.hpp"
using namespace eLog::fmt;

void textComplex()
{
    assert(format("|{0:<4d}|", 42), "|42  |");
    assert(format("|{0:^<4d}|", 42), "| 42 |");
    assert(format("|{0:>4d}|", 42), "|  42|");
    assert(format("|{.2}|", 42.12345), "|42.12|");
    assert(format("|{.4>10}|", 42), "|      0042|");
    assert(format("|{e}|", 42), "|4.200000e+01|");
    assert(format("|{e}|", 42.3f), "|4.230000e+01|");
    assert(format("|{e.2}|", 42.3f), "|4.23e+01|");
    assert(format("|{e.2^<10}|", 42.3), "| 4.23e+01 |");
    assert(format("|{n}|", 123456789), "|123'456'789|");
    assert(format("|{1:d}, {0:.4}|", 1, 2), "|2, 0001|");
}

int main()
{
    ::textComplex();
    return 0;
}