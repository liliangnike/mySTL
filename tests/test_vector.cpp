#include "my_vector.h"
#include <iostream>
#include <cassert>

#define TEST(name) std::cout << "[TEST] " << name << " ... "
#define PASS() std::cout << "PASS\n"

void test_basic() {
    TEST("MyVector basic");

    MyVector<int> v;
    assert(v.empty());
    assert(v.size() == 0);

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    assert(v.size() == 3);
    assert(v[0] == 1);
    assert(v.front() == 1);
    assert(v.back() == 3);

    v.pop_back();
    assert(v.size() == 2);
    
    PASS();
}

void test_initializer_list() {
    TEST("MyVector initializer_list");

    MyVector<int> v = {1, 2, 3, 4, 5};
    assert(v.size() == 5);
    assert(v[0] == 1);
    assert(v[4] == 5);

    PASS();
}

int main()
{
    std::cout << "=== MyVector Tests ===\n";
    
    test_basic();
    test_initializer_list();

    std::cout << "\nAll tests passed!\n";
    return 0;
}
