// Attribute.h
#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

template<typename T>
class Attribute {
private:
    T value;

public:
    Attribute() : value(T()) {} // Default constructor

    Attribute(T val) : value(val) {} // Constructor declaration

    Attribute<T>& operator+=(const T& rhs);

    T getValue() const;
};

#include "Attribute.cpp" // Include the implementation file

#endif // ATTRIBUTE_H_
