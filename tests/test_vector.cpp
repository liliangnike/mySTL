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

void test_copy() 
{
    TEST("MyVector copy constructor/assignment");

    MyVector<int> v1 = {1, 2, 3};
    MyVector<int> v2(v1);
    assert(v1 == v2);

    v2[2] = 10;
    assert(v1[2] == 3);

    MyVector<int> v3;
    v3 = v1;
    assert(v1 == v3);

    PASS();
}

void test_move()
{
    TEST("MyVector move constructor/assignment");

    MyVector<int> v1 = {1, 2, 3, 4, 5};

    MyVector<int> v2(std::move(v1));
    assert(v2.size() == 5);
    assert(v2[0] == 1);
    assert(v1.empty());
    assert(v1.size() == 0);

    MyVector<int> v3;
    v3 = std::move(v2);
    assert(v3.size() == 5);
    assert(v2.size() == 0);

    PASS();
}

void test_iterator()
{
    TEST("MyVector iterator");

    MyVector<int> v = {1, 2, 3, 4, 5};

    int sum = 0;
    for (const auto& x : v) sum += x;
    assert(sum == 15);
  
    sum = 0;
    for (auto it = v.begin(); it != v.end(); it++) {
        sum += *it;
    }
    assert(sum == 15);

    PASS();
}

int main()
{
    std::cout << "=== MyVector Tests ===\n";
    
    test_basic();
    test_initializer_list();
    test_copy();
    test_move();
    test_iterator();

    std::cout << "\nAll tests passed!\n";
    return 0;
}
