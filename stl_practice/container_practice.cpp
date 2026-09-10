#include <vector>
#include <iostream>
#include <cassert>
#include <array>
#include <list>
#include <deque>

#define TEST(name) std::cout << "[CONT] " << name << " ... "
#define PASS()     std::cout << "PASS\n"

// vector, deque and list
void practice_sequence()
{
    TEST("vector / deque / list");

    std::vector<int> v = {1, 2, 3};
    v.push_back(4);
    v.pop_back();
    assert(v.size() == 3);
    assert(v[1] == 2);

    std::vector<std::string> names;
    // No temporary string object construct/destruct.
    // Construct "aaaaa" directly within emplace_back
    names.emplace_back(5, 'a');
    assert(names[0] == "aaaaa");

    // deque supports to insert element at both head and tail
    std::deque<int> d = {2, 3};
    d.push_front(1);
    d.push_back(4);
    assert(d.front() == 1 && d.back() == 4);
    assert(d[2] == 3);

    // insert at any position
    std::list<int> lst = {1, 3, 4};
    auto it = lst.begin();
    ++it;
    lst.insert(it, 2);
    assert(lst.size() == 4);
    assert(lst.front() == 1);

    std::array<int, 3> arr = {1, 2, 3};
    assert(arr.size() == 3);
    assert(arr[0] == 1);

    PASS();
}

int main()
{
    std::cout << "=== STL Container Practice ===\n";
    
    practice_sequence();

    std::cout << "\nAll container practices passed!\n";
    return 0;
}
