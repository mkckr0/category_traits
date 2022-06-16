#ifndef CATEGORY_TRAITS_HPP
#define CATEGORY_TRAITS_HPP

#include <type_traits>

template<typename T> struct is_lvalue : std::false_type {};
template<typename T> struct is_lvalue<T&> : std::true_type {};

template<typename T> struct is_xvalue : std::false_type {};
template<typename T> struct is_xvalue<T&&> : std::true_type {};

template<typename T> struct is_glvalue : std::integral_constant<bool, is_lvalue<T>::value || is_xvalue<T>::value> {};
template<typename T> struct is_prvalue : std::integral_constant<bool, !is_glvalue<T>::value> {};
template<typename T> struct is_rvalue : std::integral_constant<bool, !is_lvalue<T>::value> {};

#if __cplusplus > 201402L || _MSVC_LANG > 201402L

template<typename T> constexpr bool is_lvalue_v = is_lvalue<T>::value;
template<typename T> constexpr bool is_xvalue_v = is_xvalue<T>::value;
template<typename T> constexpr bool is_glvalue_v = is_glvalue<T>::value;
template<typename T> constexpr bool is_prvalue_v = is_prvalue<T>::value;
template<typename T> constexpr bool is_rvalue_v = is_rvalue<T>::value;

#endif

#endif // !CATEGORY_TRAITS_HPP
