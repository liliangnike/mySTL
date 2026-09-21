#include <iostream>
#include <cassert>
#include <type_traits>
#include <map>
#include <vector>
#include <memory>

#define TEST(name) std::cout << "[MODERN] " << name << " ... ";
#define PASS()     std::cout << "PASS\n"

void practice_auto_decltype()
{
    TEST("auto / decltype");
    // auto -> variable declaration and initialization. 'const' and 'reference' are discarded.
    // int x = 10;
    // const int& ref = x;
    // auto a = ref; // a will be int type. Both const and reference attributes are discarded
    //
    // decltype -> check expression but not calculate to confirm value type. const, volatile and reference are kept.
    // int x = 10;
    // const int& ref = x;
    // decltype(x) a1 = 10;     // a1 is int
    // decltype(ref) a2 = x;    // a2 is const int&
    //
    // C++14 introduces decltype(auto)

    int x = 10;
    const int cx = 20;
    int& rx = x;

    auto a1 = x;    // int
    auto a2 = cx;   // int, discard const
    auto a3 = rx;   // int, discard reference
    auto& a4 = rx;  // int&
    assert(a1 == 10 && a2 == 20 && a3 == 10);
    a4 = 99;
    assert(x == 99);

    decltype(rx) d1 = x; // int&
    decltype(cx) d2 = 1; // const int
    // is_same_v or is_same is to check type during compilation, so static_assert is used here
    static_assert(std::is_same_v<decltype(rx), int&>, "");
    static_assert(std::is_same_v<decltype(cx), const int>, "");

    std::map<std::string, int> mp{{"a", 1}, {"b", 2}};
    int sum = 0;
    // iterator map -> use const auto&, read only and avoid copying
    for (const auto& c : mp) sum += c.second;
    assert(sum == 3);

    PASS();
}

void practice_range_structured()
{
    TEST("range-for / C++17 structured binding");
    
    std::vector<int> v = {1, 2, 3};
    int sum = 0;
    for (int x : v) sum += x;   // copy objects
    assert(sum == 6);

    for (int& x : v) x *= 2;    // reference, can be modified
    assert(v[0] == 2 && v[1] == 4 && v[2] == 6);
    
    sum = 0;
    for (const int& x : v) sum += x;    // const reference, not copy objects
    assert(sum == 12);

    std::map<std::string, int> mp = {{"alice", 90}, {"bob", 80}};
    int total = 0;
    for (const auto& [name, score] : mp) { // C++17 structured binding
        (void) name;
        total += score;
    }
    assert(total == 170);

    auto [left, right] = std::pair<int, int>{1, 10};
    assert(left == 1 && right == 10);

    PASS();
}

void practice_smart_ptr()
{
    TEST("unique_ptr / shared_ptr / weak_ptr");

    std::unique_ptr<int> u = std::make_unique<int>(42);
    assert(*u == 42);
    std::unique_ptr<int> u1 = std::move(u);
    assert(*u1 == 42);
    assert(u == nullptr);

    PASS();
}

int main()
{
    std::cout << "=== Modern C++ Practice ===\n";
    practice_auto_decltype();
    practice_range_structured();
    practice_smart_ptr();
    
    std::cout << "\nAll modern C++ practices passed!\n";
    return 0;
}
