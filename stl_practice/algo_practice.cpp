#include <vector>
#include <iostream>
#include <algorithm>
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

int main()
{
    std::cout << "=== STL Algorithm Practice === \n"; 

    practice_sort();
    practice_find();
    practice_count();

    std::cout << "\n=== All algorithm practice cases passed!\n";
    return 0;
}
