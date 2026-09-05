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

    MyList() : sentinel_(new Node()), size_(0) {
        sentinel_->prev = sentinel_;
        sentinel_->next = sentinel_;
    }
    ~MyList() {
        delete sentinel_;
    }

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    // insert new element and return the iterator of the new element
    // Before inserting: ... ←→ prev_node ←→ pos_node ←→ ...
    // After inserting : ... ←→ prev_node ←→ new_node ←→ pos_node ←→ ...
    // returns iterator of new_node
    iterator insert(iterator pos, const T& value) {
        Node* new_node = new Node(value);
        Node* pos_node = pos.node;
        Node* prev_node = pos_node->prev;
       
        new_node->prev = prev_node;
        new_node->next = pos_node;
        prev_node->next = new_node;
        pos_node->prev = new_node;

        ++size_;

        return Iterator(new_node);
    }

    iterator insert(iterator pos, T&& value) {
        Node* new_node = new Node(std::move(value));
        Node* pos_node = pos.node;
        Node* prev_node = pos_node->prev;
       
        new_node->prev = prev_node;
        new_node->next = pos_node;
        prev_node->next = new_node;
        pos_node->prev = new_node;

        ++size_;

        return Iterator(new_node);
    }

    // erase the node that pos points and return the iterator of next element
    // Before erasing, ... ←→ prev ←→ target ←→ next ←→ ...
    // After erasing, ... ←→ prev ←→ next ←→ ...
    iterator erase(iterator pos) {
        if (pos == end()) throw std::out_of_range("MyList::erase: end iterator");
        Node* target = pos.node;
        Node* prev_node = target->prev;
        Node* next_node = target->next;
        
        prev_node->next = next_node;
        next_node->prev = prev_node;

        delete target;
        --size_;

        return Iterator(next_node);
    }

    // clear all node, only keep sentinel
    void clear() {
        Node* current = sentinel_->next;    // begin
        while (current != sentinel_) {      // not end. If end, then while loop stops
            Node* next = current->next;
            delete current;
            current = next;
        }
        sentinel_->prev = sentinel_;
        sentinel_->next = sentinel_;
        size_ = 0;
    }

    void swap(MyList& other) noexcept {
        std::swap(sentinel_, other.sentinel_);
        std::swap(size_, other.size_);
    }

    // iterator
    iterator begin() { return Iterator(sentinel_->next); }
    iterator end()   { return Iterator(sentinel_); }

    const_iterator begin() const { return ConstIterator(sentinel_->next); }
    const_iterator end() const   { return ConstIterator(sentinel_); }

    std::size_t size() const { return size_; }
    bool empty() const       { return size_ == 0; }
private:
    // Define an effective data node without data saved. It will be used as head or tail node.
    // Eliminate boundary check.
    // sentinel_ ←→ node1 ←→ node2 ←→ ... ←→ sentinel_
    // (head)                                   (tail)
    // begin() is sentinel_->next
    // end() is sentinel_
    Node* sentinel_;
    std::size_t size_;
};

#endif
