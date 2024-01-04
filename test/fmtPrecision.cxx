#include "../libBuild/tmp/fmt.hpp"
#include "assert.h"
using namespace tmp::fmt;

void test_precision()
{
    ::assert(Format("{:.2}", 3.1415), "3.14");
    ::assert(Format("{:.2}", 3.145), "3.15");
    ::assert(Format("{:.2}", 3.149), "3.15");
    ::assert(Format("{:.2}", 3.150), "3.15");
    ::assert(Format("{:.2}", 3.151), "3.15");

    ::assert(Format("{:.2}", 3.1415f), "3.14");
    ::assert(Format("{:.2}", 3.145f), "3.14");
    ::assert(Format("{:.2}", 3.149f), "3.15");
    ::assert(Format("{:.2}", 3.150f), "3.15");
    ::assert(Format("{:.2}", 3.151f), "3.15");

    ::assert(Format("{:.5}", 3.1415), "3.14150");
    ::assert(Format("{:.5}", 3.145), "3.14500");
    ::assert(Format("{:.5}", 3.149), "3.14900");
    ::assert(Format("{:.5}", 3.150), "3.15000");
    ::assert(Format("{:.5}", 3.151), "3.15100");

    ::assert(Format("{:.1}", 3.1415), "3.1");
    ::assert(Format("{:.1}", 3.145), "3.1");
    ::assert(Format("{:.1}", 3.149), "3.1");
    ::assert(Format("{:.1}", 3.150), "3.1");
    ::assert(Format("{:.1}", 3.151), "3.2");
}

int main()
{
    ::test_precision();
    return 0;
}