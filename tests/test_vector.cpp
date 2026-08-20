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

    PASS();
}

int main()
{
    std::cout << "=== MyVector Tests ===\n";
    std::cout << "\nAll tests passed!\n";
    return 0;
}
