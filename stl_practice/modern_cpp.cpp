#include <iostream>
#include <cassert>
#include <type_traits>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>

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

void practice_lambda()
{
    TEST("lambda");

    int x = 10, y = 20;

    // [] capture by value - new copied 'x' object
    auto by_val = [x]() { return x + 1; };
    x = 99;
    assert (by_val() == 11);    // new 'x' object value is unchangable. See below mutable example

    // [&] capture by reference
    auto by_ref = [&y]() { y += 1; };
    by_ref();
    assert(y == 21);

    // copied object of the captured parameter only can be changed in 'mutuable' return type
    int z = 5;
    auto mut = [z]() mutable { z += 1; return z; };
    assert(mut() == 6);
    assert( z == 5);        // original external parameter is not changed

    // generic lambda
    auto add = [](auto a, auto b) { return a + b; };
    assert(add(1, 2) == 3);
    assert(add(std::string("a"), std::string("b")) == "ab");

    // used in algorithm utilities
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto n = std::count_if(vec.begin(), vec.end(), [](int n) { return n > 3; });
    assert(n == 2);

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

    auto arr = std::make_unique<int[]>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    assert(arr[1] == 2);

    std::shared_ptr<int> s1 = std::make_shared<int>(7);     // s1 -> control block, user_count++(1) -> int*
    {
        std::shared_ptr<int> s2 = s1;                           // s1 and s2 -> control block, user_count++ (2) -> int*
        assert(s1.use_count() == 2 && s2.use_count() == 2);
    } // block to check the shared_ptr scope, s2 is destroyed when leaving the block
    assert(s1.use_count() == 1);

    std::weak_ptr<int> w = s1;  // w observes s1
    assert(!w.expired());
    {
        auto locked = w.lock(); //convert it into shared_ptr
        assert(locked && *locked == 7);
        assert(s1.use_count() == 2);
    }
    s1.reset();
    assert(w.expired());        // s1 was already reset
    assert(w.lock() == nullptr);

    PASS();
}

struct Wdiget {
    int* p;

    Wdiget() : p(new int(0)) {}
    explicit Wdiget(int v) : p(new int(v)) {}

    // 3-5-0 rules
    ~Wdiget() { delete p; }

    // copy constructor - deep copy, other.p is address. new memory requires value.
    Wdiget(const Wdiget& other) : p(new int(*other.p)) {}

    // copy assignment - deep copy
    Wdiget& operator=(const Wdiget& other)
    {
        if(this != &other) {
            delete p;
            p = new int(*other.p);
        }

        return *this;
    }

    // move constructor - take/move pointer ownership
    Wdiget(Wdiget&& other) noexcept : p(other.p) { other.p = nullptr; }

    // move assignment
    Wdiget& operator=(Wdiget&& other)
    {
        // other address
        if(this != &other) {
            delete p;
            p = other.p;
            other.p = nullptr;
        }
         return *this;
    }

};

void practice_move()
{
    TEST("move semantics");

    Wdiget a(10);
    Wdiget b = a; // copy constructor, a is still valid
    assert(*a.p == 10 && *b.p == 10);

    Wdiget c = std::move(a);
    assert(a.p == nullptr);
    assert(*c.p == 10);

    PASS();
}

template <typename T>
Wdiget make_wdiget(T&& args)
{
    return Wdiget(std::forward<T>(args));
}

int main()
{
    std::cout << "=== Modern C++ Practice ===\n";
    practice_auto_decltype();
    practice_range_structured();
    practice_lambda();
    practice_smart_ptr();
    practice_move();
    
    std::cout << "\nAll modern C++ practices passed!\n";
    return 0;
}
