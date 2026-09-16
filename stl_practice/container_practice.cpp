#include <vector>
#include <iostream>
#include <cassert>
#include <array>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>
#include <functional>

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

    // multiset / multimap: key values could be duplicate
    std::multiset<int> ms = {1, 2, 2, 3};
    assert(ms.count(2) == 2);

    std::multimap<std::string, int> mm;
    mm.emplace("math", 95);
    mm.emplace("math", 80);
    assert(mm.count("math") == 2);

    PASS();
}

void practice_unordered()
{
    TEST("unordered_set / unordered_map");

    std::unordered_set<int> us = {3, 1, 2, 2};
    assert(us.size() == 3);
    assert(us.count(1) == 1);
    us.erase(1);
    assert(us.find(1) == us.end());

    std::unordered_map<std::string, int> um;
    um["apple"] = 3;
    um["banana"] = 5;
    assert(um["apple"] == 3);
    assert(um.size() == 2);

    int sum = 0;
    for (const auto& data : um) sum += data.second;
    assert(sum == 8);

    // TODO, - unordered_map rehash functions, bucket_count, load_factor and max_load_factor will be studied in future

    PASS();
}

void practice_adapters()
{
    TEST("stack / queue / priority_queue");

    std::stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    assert(st.top() == 3);
    st.pop();
    assert(st.top() == 2);
    assert(st.size() == 2);

    // Compared with vector, queue has high-efficient function pop/front
    std::queue<int> q;
    q.push(10);
    q.push(20);
    assert(q.front() == 10);
    assert(q.back() == 20);
    q.pop();
    assert(q.front() == 20);
   
    // priority_queue -> default is max_heap, top is always the max value
    std::priority_queue<int> max_heap;
    max_heap.push(30);
    max_heap.push(10);
    max_heap.push(20);
    assert(max_heap.top() == 30);

    // For priority_queue min_heap, use greater<>. top is always the min value
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    min_heap.push(30);
    min_heap.push(10);
    min_heap.push(20);
    assert(min_heap.top() == 10);

    PASS();
}

void practice_pair_tuple()
{
    TEST("pair / tuple ");

    // pair only has 2 elements
    std::pair<std::string, int> p{"age", 18};
    assert(p.first == "age");
    assert(p.second == 18);

    auto p1 = std::make_pair(1, 3.14);
    assert(p1.first == 1);

    // tuple can contains single, multiple or any number element
    std::tuple<int, std::string, double> t{1, "hi", 2.5};
    assert(std::get<0>(t) == 1);
    assert(std::get<1>(t) == "hi");

    // C++ 17 structured binding
    auto [k, v] = p;
    assert(k == "age" && v == 18);

    auto [x, y, z] = t;
    assert(x == 1 && y == "hi" && z == 2.5);

    PASS();
}

void practice_string()
{
    TEST("string");

    std::string s = "hello";
    s += " world";
    assert(s == "hello world");
    assert(s.size() == 11);
    assert(s.substr(0, 5) == "hello");
    assert(s.find("world") == 6);
    assert(s.find("xyz") == std::string::npos);

    s.replace(0, 5, "hi");
    assert(s == "hi world");

    std::map<std::string, int> freq;
    for (char c : std::string("abcdsasa")) ++freq[std::string(1, c)];
    assert(freq["a"] == 3);

    PASS();
}

int main()
{
    std::cout << "=== STL Container Practice ===\n";
    
    practice_sequence();
    practice_ordered();
    practice_unordered();
    practice_adapters();
    practice_pair_tuple();
    practice_string();

    std::cout << "\nAll container practices passed!\n";
    return 0;
}
