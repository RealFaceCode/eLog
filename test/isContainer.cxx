#include "../libBuild/fmt.hpp"
using namespace eLog::fmt;
#include <tuple>

void test_is_container()
{
    assert(is_container_v<int>, false);
    assert(is_container_v<std::string>, true);
    assert(is_container_v<std::vector<int>>, true);
    assert(is_container_v<std::unordered_map<int, int>>, true);
    assert(is_container_v<std::stringstream>, false);
    assert(is_container_v<std::string_view>, true);
    assert(is_container_v<std::tuple<>>, false);

    assert(is_iterable_v<int>, false);
    assert(is_iterable_v<std::string>, true);
    assert(is_iterable_v<std::vector<int>>, true);
    assert(is_iterable_v<std::unordered_map<int, int>>, true);
    assert(is_iterable_v<std::stringstream>, false);
    assert(is_iterable_v<std::string_view>, false);
    assert(is_iterable_v<std::tuple<>>, false); 

    assert(is_container_or_iterable_v<int>, false);
    assert(is_container_or_iterable_v<std::string>, true);
    assert(is_container_or_iterable_v<std::vector<int>>, true);
    assert(is_container_or_iterable_v<std::unordered_map<int, int>>, true);
    assert(is_container_or_iterable_v<std::stringstream>, false);
    assert(is_container_or_iterable_v<std::string_view>, true);
    assert(is_container_or_iterable_v<std::tuple<>>, false);

    assert(is_container_and_iterable_v<std::string_view>, false);
    assert(is_container_and_iterable_v<std::string>, true);
    assert(is_container_and_iterable_v<std::vector<int>>, true);
    assert(is_container_and_iterable_v<std::unordered_map<int, int>>, true);
    assert(is_container_and_iterable_v<std::stringstream>, false);
    assert(is_container_and_iterable_v<std::tuple<>>, false);
}

int main()
{
    ::test_is_container();
    return 0;
}