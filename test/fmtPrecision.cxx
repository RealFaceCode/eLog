#include "../libBuild/fmt.hpp"
using namespace eLog::fmt;

void test_precision()
{
    assert(format("{:.2}", 3.1415), "3.14");
    assert(format("{:.2}", 3.145), "3.15");
    assert(format("{:.2}", 3.149), "3.15");
    assert(format("{:.2}", 3.150), "3.15");
    assert(format("{:.2}", 3.151), "3.15");

    assert(format("{:.2}", 3.1415f), "3.14");
    assert(format("{:.2}", 3.145f), "3.15");
    assert(format("{:.2}", 3.149f), "3.15");
    assert(format("{:.2}", 3.150f), "3.15");
    assert(format("{:.2}", 3.151f), "3.15");

    assert(format("{:.5}", 3.1415), "3.14150");
    assert(format("{:.5}", 3.145l), "3.14500");
    assert(format("{:.5}", 3.149l), "3.14900");
    assert(format("{:.5}", 3.150l), "3.15000");
    assert(format("{:.5}", 3.151l), "3.15100");

    assert(format("{:.1}", 3.1415), "3.1");
    assert(format("{:.1}", 3.145), "3.1");
    assert(format("{:.1}", 3.149), "3.1");
    assert(format("{:.1}", 3.150), "3.1");
    assert(format("{:.1}", 3.151), "3.2");
}

int main()
{
    ::test_precision();
    return 0;
}