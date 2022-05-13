/**
 * \file dynarray.hpp
 * Sablonos dinamikus tömb megvalósítása.
 * 
 * Az elemek csak iterátorral érhetők el, és hozzáfűzni lehet csak, törölni nem.
 * Ha pointer típust tárol dinamikus memóriára, akkor a használó feladata a felszabadítás.
 */
#ifndef DYNARRAY_H
#define DYNARRAY_H
#include "memtrace.h"

#include <iostream>
#include <exception>
#include <cstddef>

/**
 * Sablonos dinamikus tömb megvalósítása.
 * 
 * Az elemek csak iterátorral érhetők el, és hozzáfűzni lehet csak, törölni nem.
 * Ha pointer típust tárol dinamikus memóriára, akkor a használó feladata a felszabadítás.
 * Mindig duplázza a tömb hosszát, ha elfogynak a helyek.
 */
template <typename T>
class DynArray {
    constexpr static size_t DEFAULT_SIZE = 4;
    
    size_t length; ///< number of valid elements
    size_t size; ///< size of data (there may be invalid elements at the end)
    T* data;
    
    // we don't provide these:
    DynArray(const DynArray& other);
    DynArray& operator=(const DynArray& other);
public:
    DynArray(): length(0), size(DEFAULT_SIZE), data(new T[size]) { }
    
    ~DynArray() { delete[] data; }
    
    /// Hozzáfűzi az elemet a tömb végéhez. Ha túl kicsi, akkor megnyújtja. 
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
    /**
     * Iterátor a sablon dinamikus tömbhöz.
     * 
     * A túlment iterátor dereferálását kivétellel díjazza.
     */
    class Iterator {
        T* current;
        T* end;
    public:
        
        // https://stackoverflow.com/questions/59851539/no-type-named-value-type-in-struct-stditerator-traits
        /// azért, hogy std::algoritmusokkal lehessen használni (pl std::equal)
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
