#pragma once

#include <string>
#include <string_view>
#include <source_location>
#include <sstream>
#include <type_traits>


namespace elog::fmt
{
    template <typename T>
    using not_ref_type = std::remove_reference_t<T>;

    template <typename T>
    struct is_container {
        private:
            template <typename U>
            static constexpr auto test(int) -> decltype(
                    std::declval<U>().begin(), std::declval<U>().end(), std::true_type{});

            template <typename>
            static constexpr std::false_type test(...);

        public:
            static constexpr bool value = decltype(test<T>(0))::value;
    };

    template <typename T>
    constexpr bool is_container_v = is_container<T>::value;

    template <typename T>
    struct is_iterable {
        private:
            template <typename U>
            static constexpr auto test(int) -> decltype(
                    std::declval<U>().begin(), std::declval<U>().end(), ++std::declval<U>().begin(), std::true_type{});

            template <typename>
            static constexpr std::false_type test(...);

        public:
            static constexpr bool value = decltype(test<T>(0))::value;
    };

    template <typename T>
    constexpr bool is_iterable_v = is_iterable<T>::value;

    template <typename T>
    struct is_container_or_iterable {
        static constexpr bool value = is_container_v<T> || is_iterable_v<T>;
    };

    template <typename T>
    constexpr bool is_container_or_iterable_v = is_container_or_iterable<T>::value;

    template <typename T>
    struct is_container_and_iterable {
        static constexpr bool value = is_container_v<T> && is_iterable_v<T>;
    };

    template <typename T>
    constexpr bool is_container_and_iterable_v = is_container_and_iterable<T>::value;

    // check for string or string_view type
    template <typename T>
    struct is_string {
        static constexpr bool value = std::is_same_v<T, std::string>
                                    || std::is_same_v<T, const std::string>
                                    || std::is_same_v<T, std::string&>
                                    || std::is_same_v<T, const std::string&>
                                    || std::is_same_v<T, std::string*>
                                    || std::is_same_v<T, const std::string*>;
    };

    template <typename T>
    constexpr bool is_string_v = is_string<T>::value;

    template <typename T>
    struct is_string_view {
        static constexpr bool value = std::is_same_v<T, std::string_view>
                                    || std::is_same_v<T, const std::string_view>
                                    || std::is_same_v<T, std::string_view&>
                                    || std::is_same_v<T, const std::string_view&>
                                    || std::is_same_v<T, std::string_view*>
                                    || std::is_same_v<T, const std::string_view*>;
    };

    template <typename T>
    constexpr bool is_string_view_v = is_string_view<T>::value;

    template <typename T>
    struct is_string_or_string_view {
        static constexpr bool value = is_string_v<T> || is_string_view_v<T>;
    };

    template <typename T>
    constexpr bool is_string_or_string_view_v = is_string_or_string_view<T>::value;

    // check for char type
    template <typename T>
    struct is_char {
        static constexpr bool value = std::is_same_v<T, char>;
    };

    template <typename T>
    constexpr bool is_char_v = is_char<T>::value;

    template <typename T>
    struct is_const_char {
        static constexpr bool value = std::is_same_v<T, const char>;
    };

    template <typename T>
    constexpr bool is_const_char_v = is_const_char<T>::value;

    template <typename T>
    struct is_char_ptr {
        static constexpr bool value = std::is_same_v<T, char*>;
    };

    template <typename T>
    constexpr bool is_char_ptr_v = is_char_ptr<T>::value;

    template <typename T>
    struct is_const_char_ptr {
        static constexpr bool value = std::is_same_v<T, const char*>;
    };

    template <typename T>
    constexpr bool is_const_char_ptr_v = is_const_char_ptr<T>::value;

    template <typename T>
    struct is_char_array {
        static constexpr bool value = std::is_array_v<T> && std::is_same_v<std::remove_extent_t<T>, char>;
    };

    template <typename T>
    constexpr bool is_char_array_v = is_char_array<T>::value;

    template <typename T>
    struct is_const_char_array {
        static constexpr bool value = std::is_array_v<T> && std::is_same_v<std::remove_extent_t<T>, const char>;
    };

    template <typename T>
    constexpr bool is_const_char_array_v = is_const_char_array<T>::value;

    template <typename T>
    struct is_integer {
        static constexpr bool value = std::is_integral_v<T>;
    };

    template <typename T>
    constexpr bool is_integer_v = is_integer<T>::value;

    template <typename T>
    struct is_float {
        static constexpr bool value = std::is_same_v<T, float>;
    };

    template <typename T>
    constexpr bool is_float_v = is_float<T>::value;

    template <typename T>
    struct is_double {
        static constexpr bool value = std::is_same_v<T, double>;
    };

    template <typename T>
    constexpr bool is_double_v = is_double<T>::value;    

    template <typename T>
    struct is_floating_point {
        static constexpr bool value = is_float_v<T> || is_double_v<T>;
    };

    template <typename T>
    constexpr bool is_floating_point_v = is_floating_point<T>::value;

    template <typename T>
    struct is_arithmetic {
        static constexpr bool value = is_integer_v<T> || is_float_v<T>;
    };

    template <typename T>
    constexpr bool is_arithmetic_v = is_arithmetic<T>::value;

    template <typename T>
    struct is_bool {
        static constexpr bool value = std::is_same_v<T, bool>;
    };

    template <typename T>
    constexpr bool is_bool_v = is_bool<T>::value;

    template <typename T>
    struct is_pointer {
        static constexpr bool value = std::is_pointer_v<T>;
    };

    template <typename T>
    constexpr bool is_pointer_v = is_pointer<T>::value;

    template <typename T>
    struct is_nullptr {
        static constexpr bool value = std::is_same_v<T, std::nullptr_t>;
    };

    template <typename T>
    constexpr bool is_nullptr_v = is_nullptr<T>::value;

    template <typename T>
    struct is_cstring {
        static constexpr bool value = is_const_char_ptr_v<T> || is_char_ptr_v<T> || is_const_char_array_v<T> || is_char_array_v<T>;
    };

    template <typename T>
    constexpr bool is_cstring_v = is_cstring<T>::value;

    template <typename T>
    struct is_string_type {
        static constexpr bool value = is_string_or_string_view_v<T> || is_cstring_v<T>;
    };

    template <typename T>
    constexpr bool is_string_type_v = is_string_type<T>::value;

    //is_map
    template <typename T>
    struct is_map {
        private:
            template <typename U>
            static constexpr auto test(int) -> decltype(
                    std::declval<U>().begin(), std::declval<U>().end(),
                    std::declval<U>().begin()->first, std::declval<U>().begin()->second,
                    std::true_type{});

            template <typename>
            static constexpr std::false_type test(...);

        public:
            static constexpr bool value = decltype(test<T>(0))::value;
    };

    template <typename T>
    constexpr bool is_map_v = is_map<T>::value;

    //is_pair
    template <typename T>
    struct is_pair {
        private:
            template <typename U>
            static constexpr auto test(int) -> decltype(
                    std::declval<U>().first, std::declval<U>().second, std::true_type{});

            template <typename>
            static constexpr std::false_type test(...);

        public:
            static constexpr bool value = decltype(test<T>(0))::value;
    };

    template <typename T>
    constexpr bool is_pair_v = is_pair<T>::value;
}