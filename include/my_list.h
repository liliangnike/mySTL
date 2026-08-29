#ifndef __MY_LIST_HEADER_FILE__
#define __MY_LIST_HEADER_FILE__

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
    };
public:
    MyList() : size_(0) {}
    ~MyList() {}

private:
    std::size_t size_;
};

#endif
