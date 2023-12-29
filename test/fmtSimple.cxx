#include "../libBuild/fmt.hpp"
using namespace eLog::fmt;

void testSimple()
{
    assert(format("{}", 42), "42");
    assert(format("{}", std::vector<int>{1, 2, 3}), "[1, 2, 3]");
    assert(format("{}", std::vector<std::string>{"a", "b", "c"}), "[a, b, c]");
    assert(format("{}", std::vector<std::vector<int>>{{1, 2}, {3, 4}}), "[[1, 2], [3, 4]]");
    assert(format("{}", std::vector<std::vector<std::string>>{{"a", "b"}, {"c", "d"}}), "[[a, b], [c, d]]");

    assert(format("{0}", 42), "42");
    assert(format("{0}", std::vector<int>{1, 2, 3}), "[1, 2, 3]");
    assert(format("{0}", std::vector<std::string>{"a", "b", "c"}), "[a, b, c]");
    assert(format("{0}", std::vector<std::vector<int>>{{1, 2}, {3, 4}}), "[[1, 2], [3, 4]]");
    assert(format("{0}", std::vector<std::vector<std::string>>{{"a", "b"}, {"c", "d"}}), "[[a, b], [c, d]]");

    assert(format("{:s}", 42), "42");
    assert(format("{:s}", std::vector<int>{1, 2, 3}), "[1, 2, 3]");
    assert(format("{:s}", std::vector<std::string>{"a", "b", "c"}), "[a, b, c]");
    assert(format("{:s}", std::vector<std::vector<int>>{{1, 2}, {3, 4}}), "[[1, 2], [3, 4]]");
    assert(format("{:s}", std::vector<std::vector<std::string>>{{"a", "b"}, {"c", "d"}}), "[[a, b], [c, d]]");

    assert(format("{0:s}", 42), "42");
    assert(format("{0:s}", std::vector<int>{1, 2, 3}), "[1, 2, 3]");
    assert(format("{0:s}", std::vector<std::string>{"a", "b", "c"}), "[a, b, c]");
    assert(format("{0:s}", std::vector<std::vector<int>>{{1, 2}, {3, 4}}), "[[1, 2], [3, 4]]");
    assert(format("{0:s}", std::vector<std::vector<std::string>>{{"a", "b"}, {"c", "d"}}), "[[a, b], [c, d]]");
}

int main()
{
    ::testSimple();
    return 0;
}