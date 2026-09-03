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

        // No need to construct data objects in the external of Node ( the construction requires additional system cost )
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
    struct Iterator {
        Node* node;

        explicit Iterator(Node* n) : node(n) {}

        // operator * return reference of node data itself
        T& operator*() { return node->data; }
        T* operator->() { return &node->data; }

        // pre-increment
        // ++it, move to next element and then return the reference
        Iterator& operator++() {
            node = node->next;
            return *this;
        }

        // post-increment
        // it++, return the current reference firstly and then move to next element
        // 'int' is dummy operator to distinct pre/post-increment
        Iterator operator++(int) {
            Iterator tmp = *this;
            node = node->next;
            return tmp;
        }

        // --it
        Iterator& operator--() {
            node = node->prev;
            return *this;
        }

        // it--
        Iterator operator--(int) {
            Iterator tmp = *this;
            node = node->prev;
            return tmp;
        }

        bool operator==(const Iterator& other) { return node == other.node; }
        bool operator!=(const Iterator& other) { return node != other.node; }
    };

    struct ConstIterator {
        const Node* node;

        explicit ConstIterator(Node* n) : node(n) {}

        // allows Iterator to be converted into ConstIterator implicitly
        ConstIterator(const Iterator& it) : node(it.node) {}

        const T& operator*() const { return node->data; }
        const T* operator->() const { return &node->data; }

        ConstIterator& operator++() { node = node->next; return *this; } 
        ConstIterator operator++(int) {
            Iterator tmp = *this;
            node = node->next;
            return tmp;
        }

        ConstIterator& operator--() { node = node->prev; return *this; } 
        ConstIterator operator--(int) {
            Iterator tmp = *this;
            node = node->prev;
            return tmp;
        }

        bool operator==(const ConstIterator& other) const { return node == other.node; }
        bool operator!=(const ConstIterator& other) const { return node != other.node; }
    };

    MyList() : sentinel_(new Node()), size_(0) {}
    ~MyList() {
        delete sentinel_;
    }

    using iterator = Iterator;
    using const_iterator = ConstIterator;

private:
    Node* sentinel_;
    std::size_t size_;
};

#endif
