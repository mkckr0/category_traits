#include "category_traits.hpp"
#include <vector>

struct A
{
    int x = 1;
};

int main()
{
    A a;

    static_assert(is_lvalue<decltype(("abcd"))>::value, R"("abcd" is a lvalue)");
    static_assert(is_glvalue<decltype(("abcd"))>::value, R"("abcd" is a glvalue)");
    static_assert(!is_xvalue<decltype(("abcd"))>::value, R"("abcd" is not a xvalue)");
    static_assert(!is_rvalue<decltype(("abcd"))>::value, R"("abcd" is not a rvalue)");
    static_assert(!is_prvalue<decltype(("abcd"))>::value, R"("abcd" is not a prvalue)");
    
    static_assert(is_lvalue<decltype((a))>::value, R"(a is a lvalue)");
    static_assert(is_glvalue<decltype((a))>::value, R"(a is a glvalue)");
    static_assert(!is_xvalue<decltype((a))>::value, R"(a is not a xvalue)");
    static_assert(!is_rvalue<decltype((a))>::value, R"(a is not a rvalue)");
    static_assert(!is_prvalue<decltype((a))>::value, R"(a is not a prvalue)");

    static_assert(!is_lvalue<decltype((A()))>::value, R"(A() is not a lvalue)");
    static_assert(!is_glvalue<decltype((A()))>::value, R"(A() is not a glvalue)");
    static_assert(!is_xvalue<decltype((A()))>::value, R"(A() is not a xvalue)");
    static_assert(is_rvalue<decltype((A()))>::value, R"(A() is a rvalue)");
    static_assert(is_prvalue<decltype((A()))>::value, R"(A() is a prvalue)");

    // this group of test case may be failed on old compiler. gcc-11 and mscv-1932 is ok.
    static_assert(!is_lvalue<decltype((A().x))>::value, R"(A().x is not a lvalue)");
    static_assert(is_glvalue<decltype((A().x))>::value, R"(A().x is a glvalue)");
    static_assert(is_xvalue<decltype((A().x))>::value, R"(A().x is a xvalue)");
    static_assert(is_rvalue<decltype((A().x))>::value, R"(A().x is a rvalue)");
    static_assert(!is_prvalue<decltype((A().x))>::value, R"(A().x is not a prvalue)");

    std::vector<int> v;
    static_assert(!is_lvalue<decltype((std::move(v)))>::value, R"(std::move(v) is not a lvalue)");
    static_assert(is_glvalue<decltype((std::move(v)))>::value, R"(std::move(v) is a glvalue)");
    static_assert(is_xvalue<decltype((std::move(v)))>::value, R"(std::move(v) is a xvalue)");
    static_assert(is_rvalue<decltype((std::move(v)))>::value, R"(std::move(v) is a rvalue)");
    static_assert(!is_prvalue<decltype((std::move(v)))>::value, R"(std::move(v) is not a prvalue)");
}
