#ifndef __MY_VECTOR_HEADER_FILE__
#define __MY_VECTOR_HEADER_FILE__

// During template instantiation, compiler must know the template declaration and implementation at the same time
// So for template, all functions declaration and implementation should be in one header file
// No need to implement in additional cpp file
template <typename T>
class MyVector {
public:
    // default constructor
    MyVector() data_(nullptr), size_(0), capacity_(0) {}
    ~MyVector() {}

    void reserver(std::size_t new_capacity) {
        if (new_capacity <= capacity_) return; 
    }

private:
    T*          data_;
    std::size_t size_;
    std::size_t capacity_;
};

#endif
