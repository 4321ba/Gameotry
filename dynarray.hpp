#ifndef DYNARRAY_H
#define DYNARRAY_H
#include "memtrace.h"

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
    
    class Iterator {
        T* current;
        T* end;
    public:
        
        // azért, hogy std::algoritmusokkal lehessen használni (pl std::equal)
        // https://stackoverflow.com/questions/59851539/no-type-named-value-type-in-struct-stditerator-traits
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::output_iterator_tag;

        Iterator(T* current, T* end): current(current), end(end) { }
        T& operator*() {
            if (current >= end)
                throw std::out_of_range("Iterator dereferencing is out of bounds!");
            return *current;
        }
        bool operator!=(const Iterator& other) { return current != other.current; }
        Iterator& operator++() { ++current; return *this; }
    };
    
    Iterator begin() { return Iterator(data, data + length); }
    Iterator end() { return Iterator(data + length, data + length); }
};

#endif // DYNARRAY_H
