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

int main()
{
    std::cout << "=== STL Algorithm Practice === \n"; 

    practice_sort();

    std::cout << "\n=== All algorithm practice cases passed!\n";
    return 0;
}
