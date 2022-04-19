#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <iostream>
#include <exception>
#include <cstddef>

template <typename T>
class DynArray {
    constexpr static size_t DEFAULT_SIZE = 4;
    
    size_t length; // number of valid elements
    size_t size; // size of data (there may be invalid elements at the end)
    T* data;
    
    // we don't provide these:
    DynArray(const DynArray& other);
    DynArray& operator=(const DynArray& other);
public:
    DynArray(): length(0), size(DEFAULT_SIZE), data(new T[size]) { }
    
    ~DynArray() { delete[] data; }
    
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
    
    
    class Iterator {
        T* current;
    public:
        Iterator(T* p): current(p) { }
        T& operator*() { return *current; }
        bool operator!=(const Iterator& other) { return current != other.current; }
        Iterator& operator++() { ++current; return *this; }
    };
    
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + length); }
};

#endif // DYNARRAY_H
