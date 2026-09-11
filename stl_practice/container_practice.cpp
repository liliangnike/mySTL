#include <vector>
#include <iostream>
#include <cassert>
#include <array>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <algorithm>

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

void practice_ordered()
{
    TEST("set / map / multiset / multimap");

    std::set<int> s = {3, 1, 2, 2}; // remove duplicate element and sort automatically
    assert(s.size() == 3);
    assert(*s.begin() == 1);
    assert(s.count(2) == 1);
    assert(s.find(99) == s.end());
    s.erase(2);
    assert(s.count(2) == 0);

    // upper_bound / lower_bound - only ordered set has this
    std::set<int> s1 = {10, 20, 30, 40};
    auto ub = s1.upper_bound(30);   // first one that > 30, point to next iterator of '30'
    auto lb = s1.lower_bound(25);   // first one that >= 25, point to iterator of '20'
    assert(*ub == 40);
    assert(*lb == 30);

    std::map<std::string, int> mp;
    mp["alice"] = 90;
    mp.insert({"bob", 80}); // insert an <std::string, int> objects - extra system cost
    mp.emplace("carol", 85);    // in-place construct
    assert(mp["alice"] == 90);
    assert(mp.at("bob") == 80);
    assert(mp.count("dave") == 0);

    assert(mp["dave"] == 0);    // operator[] insert default value, "dave" = 0
    assert(mp.size() == 4);

    auto fd = mp.find("eve");
    assert(fd == mp.end());
    assert(mp.size() == 4);

    PASS();
}

int main()
{
    std::cout << "=== STL Container Practice ===\n";
    
    practice_sequence();
    practice_ordered();

    std::cout << "\nAll container practices passed!\n";
    return 0;
}
