#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <iostream>
#include <stdexcept>
#include <cstddef>

template <typename T>
class DynArray {
    static const size_t DEFAULT_SIZE = 4;
    
    size_t length; // number of valid elements
    size_t size; // size of data (there may be invalid elements at the end)
    T* data;
    
public:
    DynArray(): length(0), size(DEFAULT_SIZE), data(nullptr) {
        data = new T[size];
    }
    
    ~DynArray() { delete[] data; }
    
    DynArray(const DynArray& other): data(nullptr) {
        *this = other;
    }
    
    DynArray& operator=(const DynArray& other) {//TODO kell ez?
        delete[] data;
        length = other.length;
        size = other.size;
        data = new T[size];
        for (size_t i = 0; i < length; ++i)
            data[i] = other.data[i];
        return *this;
    }
    
    T& operator[](size_t idx) {
        if (idx >= length)
            throw std::range_error("Index out of bounds for DynArray!");
        return data[idx];
    }
    
    const T& operator[](size_t idx) const {
        if (idx >= length)
            throw std::range_error("Index out of bounds for DynArray!");
        return data[idx];
    }
    
    void append(T appendee) {
        if (length >= size) {
            T* old_data = data;
            size *= 2;
            data = new T[size];
            for (size_t i = 0; i < length; ++i)
                data[i] = old_data[i];
            delete[] old_data;
        }
        data[length++] = appendee;
    }
    
    size_t len() { return length; }
};

#endif // DYNARRAY_H
