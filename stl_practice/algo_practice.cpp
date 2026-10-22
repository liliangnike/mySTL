#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>  // std::accumulate
#include <cassert>

#define TEST(name) std::cout << "[ALGO] " << name << " ... "
#define PASS()     std::cout << "PASS\n";

void practice_sort()
{
    TEST("sort / stable_sort");

    std::vector<int> v = {5, 1, 3, 4, 2};
    std::sort(v.begin(), v.end());
    assert(v == std::vector<int>({1, 2, 3, 4, 5}));

    PASS();
}

void practice_find()
{
    TEST("find / find_if ");

    std::vector<int> v = {1, 2, 3, 4, 5, 6};

    auto it = std::find(v.begin(), v.end(), 3);
    assert(it != v.end() && *it == 3);
    assert(std::distance(v.begin(), it) == 2);

    auto it1 = std::find(v.begin(), v.end(), 100);
    assert(it1 == v.end());

    // find the 1st x that meets condition
    auto it2 = std::find_if(v.begin(), v.end(),
            [](int x){ return x > 4; } );
    assert(*it2 == 5);

    // find the 1st x that does not meet condition
    auto it3 = std::find_if_not(v.begin(), v.end(),
            [](int x){ return x < 3; } );
    assert(*it3 == 3);

    PASS();
}

void practice_count()
{
    TEST("count / count_if ");

    std::vector<int> v = {1, 2, 2, 3, 2, 4, 5};

    int cnt = std::count(v.begin(), v.end(), 2);
    assert(cnt == 3);

    int even = std::count_if(v.begin(), v.end(),
            [](int x){ return x % 2 == 0; } );
    assert(even == 4);

    PASS();
}

void practice_accumulate()
{
    TEST("accumulate / transform");

    std::vector<int> v = {1, 2, 3, 4, 5};
    // accumulate to get sum
    int sum = std::accumulate(v.begin(), v.end(), 0);   // 0 is not only the initial value, but also determines the return result data type
    assert(sum == 15);

    // accumulate to get product - 1, using multiplies
    int product1 = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
    assert(product1 == 120);
    
    // accumulate to get product - 2, using lambda
    // Every C++ algorithm has its own signature & semantic for the passed lambda
    // Here the lambda is equivalent to:
    // for (int x : v) {
    //      acc *= x;
    // }
    // TODO, learn the lambda specific rules for all algorithm functions like sort, find_if, for_each, .etc
    int product2 = std::accumulate(v.begin(), v.end(), 1, 
                   [](int acc, int x){ return acc * x; });
    assert(product2 == 120);

    PASS();
}

void practice_erase_remove()
{
    TEST("erase-remove idiom");

    std::vector<int> v = {1, 2, 3, 2, 4, 2, 5};

    // remove all elements whose values are 2
    v.erase(std::remove(v.begin(), v.end(), 2), v.end());
    assert(v == std::vector<int>({1, 3, 4, 5}));

    std::vector<int> v2 = {1, 2, 3, 4, 5, 6};

    // remove all even numbers
    auto new_end = std::remove_if(v2.begin(), v2.end(), [](int x){ return x % 2 == 0; });
    v2.erase(new_end, v2.end());
    assert(v2 == std::vector<int>({1, 3, 5}));

    PASS();
}

void practice_minmax()
{
    TEST(" min_element / max_element");

    using IntVec = std::vector<int>;
    IntVec v = {3, 1, 4, 1, 5, 9, 2, 6};

    auto min_iter = std::min_element(v.begin(), v.end());
    auto max_iter = std::max_element(v.begin(), v.end());
    assert(*min_iter == 1);
    assert(*max_iter == 9);

    auto [mn, mx] = std::minmax_element(v.begin(), v.end());
    assert(*mn == 1 && *mx == 9);

    PASS();
}

void practice_unique()
{
    TEST("unique");

    using IntVec = std::vector<int>;

    IntVec v = {1, 2, 2, 3, 3, 3, 4, 5, 5};
    // v is already sorted
    auto new_begin = std::unique(v.begin(), v.end());
    v.erase(new_begin, v.end());
    assert(v == IntVec({1,2,3,4,5}));

    IntVec v1 = {3, 1, 2, 1, 3};
    // v1 is not sorted. Must be sorted before using unique
    std::sort(v1.begin(), v1.end());
    auto v2_new_begin = std::unique(v1.begin(), v1.end());
    v1.erase(v2_new_begin, v1.end());
    assert(v1 == IntVec({1, 2, 3}));

    PASS();
}

void practice_lambda()
{
    TEST("lambda capture mode");

    int x = 10;
    int y = 20;

    // capture by value: x is copy, no impact on external. Also see below mutable example.
    auto by_value = [x]() { return x + 1; };
    assert(by_value() == 11);
    x = 100;
    assert(by_value() == 11);

    // capture by reference: y is reference, internal modification updates external value
    auto by_reference = [&y]() { return y += 1; };
    by_reference();
    assert(y == 21);

    int z = 5;
    auto mutable_lambda = [z]() mutable {
        z += 1;     // modified the copied z
        return z;
    };
    assert(mutable_lambda() == 6);
    assert(z == 5);

    PASS();
}

int main()
{
    std::cout << "=== STL Algorithm Practice === \n"; 

    practice_sort();
    practice_find();
    practice_count();
    practice_accumulate();
    practice_erase_remove();
    practice_minmax();
    practice_unique();
    practice_lambda();

    std::cout << "\n=== All algorithm practice cases passed!\n";
    return 0;
}
