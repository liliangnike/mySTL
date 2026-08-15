#ifndef __MY_VECTOR_HEADER_FILE__
#define __MY_VECTOR_HEADER_FILE__

#include <algorithm>
#include <initializer_list>
// During template instantiation, compiler must know the template declaration and implementation at the same time
// So for template, all functions declaration and implementation should be in one header file
// No need to implement in additional cpp file
template <typename T>
class MyVector {
public:
    // equivalent to C typedef, to define type alias
    // typedef T* iterator;
    // type const T* const_iterator;
    //
    // But modern C++ recommends to use 'using'
    using iterator = T*;
    using const_iterator = const T*;

    // default constructor
    MyVector() : data_(nullptr), size_(0), capacity_(0) {}

    // Avoid the implicit conversion like MyVector<int> v = 5;
    explicit MyVector(std::size_t count, const T& value = T())
        : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(count);
        for (std::size_t i = 0; i < count; i++) data_[i] = value;
        size_ = count;
    }

    // C++11 allows to initialize vector with a value set grouped by {}
    // For example, MyVector<int> = {1, 2, 3, 4, 5}
    MyVector(std::initializer_list<T> init)
        : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(init.size());
        for (const auto& val : init) data_[size++] = val;
    }

    ~MyVector() { delete[] data_; }

    // copy constructor - deepcopy
    // shallow copy - 2 objects share one memory
    MyVector(const MyVector& other)
        : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(other.size_);
        std::copy(other.begin(), other.end(), data_);
        size_ = other.size_;
    }

    // assign constructor
    // check if a = a, delete then copy the memory that already was free
    MyVector& operator=(const MyVector& other)
        : data_(nullptr), size_(0), capacity_(0)
    {
        if (this != &other) {
            // free itself
            delete [] data_;
            data_ = nullptr;
            size_ 0 ;
            capacity_ = 0;
            reserve(other.size_);
            std::copy(other.begin(), other.end(), data_);
            size_ = other.size_;
        }

        return *this;
    }

    // No out of range check -> unexpected behaviours
    T& operator[](std::size_t idx) { return data_[idx]; }
    const T& operator[](std::size_t idx) { return data_[idx]; }

    // check out of range
    T& at(std::size_t idx) {
        if (idx >= size_) throw std::out_of_range("MyVection::at(): index out of range");
        return data_[idx];
    }
    const T& at(std::size_t idx) {
        if (idx >= size_) throw std::out_of_range("MyVection::at(): index out of range");
        return data_[idx];
    }

    T& front() { return data_[0]; }
    T& back()  { return data_[size_ - 1]; }
    const T& front() const { return data_[0]; }
    const T& back()  const { return data_[size_ - 1]; }

    void push_back(const T& value) {
        if (size_ == capacity_) grow();
        data_[size_++] = value;
    }
    // Provide move function - avoid unnecessary copy
    void push_back(T&& value) {
        if (size_ == capacity_) grow();
        // value is right-value reference, but the parameter has name, so it is left value
        // So right-value reference is actually left value, so move should be used
        data[size_++] = std::move(value);
    }
    // Both of pop_back and clear only change size, memory data is unchanged.
    // 1. Avoid system overhead - the data elements are possible to be overwritten by next push_back action
    // 2. For basic data types, such as int, double, .etc, it is ok to save the old value until the next write action
    // 3. For complicated data structures, we should consider to call the destructor function ~T()? Or keep until the MyVector object is destroyed
    void pop_back() { if(size_ > 0) --size_; }
    void clear() { size_ = 0; }

    // reserve 'moves' all the original data to a new memory space, size is not changed
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

    // Change size and new elements are initialized with the 'value'
    void resize(std::size_t new_sz, const T& value = T()) {
        if (new_sz > capacity_) reserve(new_sz);
        for (std::size_t i = size_; i < new_sz; i++) data_[i] = value;
        size_ = new_sz;
    }

    iterator begin() { return data_; }
    iterator end()   { return data_ + size_; }  // What's difference with back()? back returns last element reference, can be read/write; end return the next position pointer of last position
    const_iterator begin() const { return data_; }
    const_iterator end() const { return data_ +size_; }
    const_iterator cbegin() const { return data_; }
    const_iterator cend() const { return data_ +size_; }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    T* data() const { return data_; }
    const T* data() const { return data_; }

    bool operator==(const MyVector& other) const {
        if (size_ != other.size()) return false;
        for (std::size_t i = 0; i < size_; i++) {
            if (data_[i] != other.data()[i]) return false;
        }

        return true;
    }
    // operator== already implemented
    bool operator!=(const MyVector& other) const { return !(*this == other); }

    void swap(const MyVector& other) const {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
private:
    void grow() {
        std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        reserve(new_capacity);
    }

    T*          data_;
    std::size_t size_;      // actual element numbers
    std::size_t capacity_;  // allocated memory space
};

#endif
