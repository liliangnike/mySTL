#ifndef __MY_LIST_HEADER_FILE__
#define __MY_LIST_HEADER_FILE__

#include <utility>

// C++ STL list is bidirectional list
// The implementation is also same like that
// C++11 introduced singly linked list, std::forward_list
template <typename T>
class MyList {
private:
    // struct vs class: struct -> public, class -> private
    struct Node {
        T data;
        Node* prev;
        Node* next;

        // No need to construct data objects in the external of Node ( this is additional system const )
        // Pass data constructor parameters into Node. When Node is constructed, data object is constructed at the same time
        //
        // std::forward -> Perfecr forwarding, keep parameters' original left/right value attributes
        template<typename... Args>  // ... means Args is parameter pack, can be 0 or 1 or multiple parameters with any types. For example, it can be any (or combination) of int, double or std::string, .etc
        Node(Args&&... args) // Args&& -> Universal reference, args -> Parameter Pack. Can be Node()、Node(1)、Node(1, "hello", 3.14), .etc
            : data(std::forward<Args>(args)...) // ... here is to expand the parameter pack. If Node(1, "hello"), then it is expanded as "data(std::forward<int>(arg1), std::forward<const char*>(arg2))"
              prev(nullptr),
              next(nullptr)
        {}
    };
public:
    MyList() : size_(0) {}
    ~MyList() {}

private:
    std::size_t size_;
};

#endif
