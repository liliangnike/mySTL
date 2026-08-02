#ifndef __MY_VECTOR_HEADER_FILE__
#define __MY_VECTOR_HEADER_FILE__

// During template instantiation, compiler must know the template declaration and implementation at the same time
// So for template, all functions declaration and implementation should be in one header file
// No need to implement in additional cpp file
template <typename T>
class MyVector {
public:
    MyVector() {}
    ~MyVector() {}

private:
};

#endif
