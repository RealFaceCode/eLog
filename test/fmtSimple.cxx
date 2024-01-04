#include "../libBuild/tmp/fmt.hpp"
#include "assert.h"
using namespace tmp::fmt;

void testSimple()
{
    ::assert(Format("{}", 42), "42");
    ::assert(Format("{}", std::vector<int>{1, 2, 3}), "[1, 2, 3]");
    ::assert(Format("{}", std::vector<std::string>{"a", "b", "c"}), "[a, b, c]");
    ::assert(Format("{}", std::vector<std::vector<int>>{{1, 2}, {3, 4}}), "[[1, 2], [3, 4]]");
    ::assert(Format("{}", std::vector<std::vector<std::string>>{{"a", "b"}, {"c", "d"}}), "[[a, b], [c, d]]");

    ::assert(Format("{0}", 42), "42");
    ::assert(Format("{0}", std::vector<int>{1, 2, 3}), "[1, 2, 3]");
    ::assert(Format("{0}", std::vector<std::string>{"a", "b", "c"}), "[a, b, c]");
    ::assert(Format("{0}", std::vector<std::vector<int>>{{1, 2}, {3, 4}}), "[[1, 2], [3, 4]]");
    ::assert(Format("{0}", std::vector<std::vector<std::string>>{{"a", "b"}, {"c", "d"}}), "[[a, b], [c, d]]");

    ::assert(Format("{:s}", 42), "42");
    ::assert(Format("{:s}", std::vector<int>{1, 2, 3}), "[1, 2, 3]");
    ::assert(Format("{:s}", std::vector<std::string>{"a", "b", "c"}), "[a, b, c]");
    ::assert(Format("{:s}", std::vector<std::vector<int>>{{1, 2}, {3, 4}}), "[[1, 2], [3, 4]]");
    ::assert(Format("{:s}", std::vector<std::vector<std::string>>{{"a", "b"}, {"c", "d"}}), "[[a, b], [c, d]]");

    ::assert(Format("{0:s}", 42), "42");
    ::assert(Format("{0:s}", std::vector<int>{1, 2, 3}), "[1, 2, 3]");
    ::assert(Format("{0:s}", std::vector<std::string>{"a", "b", "c"}), "[a, b, c]");
    ::assert(Format("{0:s}", std::vector<std::vector<int>>{{1, 2}, {3, 4}}), "[[1, 2], [3, 4]]");
    ::assert(Format("{0:s}", std::vector<std::vector<std::string>>{{"a", "b"}, {"c", "d"}}), "[[a, b], [c, d]]");
}

int main()
{
    ::testSimple();
    return 0;
}