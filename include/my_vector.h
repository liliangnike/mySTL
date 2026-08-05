#ifndef __MY_VECTOR_HEADER_FILE__
#define __MY_VECTOR_HEADER_FILE__

#include <algorithm>
// During template instantiation, compiler must know the template declaration and implementation at the same time
// So for template, all functions declaration and implementation should be in one header file
// No need to implement in additional cpp file
template <typename T>
class MyVector {
public:
    // default constructor
    MyVector() data_(nullptr), size_(0), capacity_(0) {}
    ~MyVector() {}

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) return; 
        // allocate memory
        T* new_data = new T[new_capacity];
        if (data_) {
            // 2 std::move in C++
            // 1. <utility>, std::move is to convert left value to right value
            // 2. <algorithm>, move a data block into another new address - std::move(*begin, *end, *target_position)
            //    Can understand as: find a new bigger 'home' for original data
            std::move(data_, data_ + size_, new_data);
            delete[] data_;
        }
        
        data_ = new_data;
        capacity_ = new_capacity;
    }

private:
    T*          data_;
    std::size_t size_;
    std::size_t capacity_;
};

#endif
