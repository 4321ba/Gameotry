/**
 * \file vector.cpp
 * Kellett csinálni külön fájlt a statikus konstans adattagoknak.
 */
#include "memtrace.h"

#include "vectormath.h"

const Vector Vector::UP   ( 0, -1);
const Vector Vector::DOWN ( 0,  1);
const Vector Vector::LEFT (-1,  0);
const Vector Vector::RIGHT( 1,  0);
