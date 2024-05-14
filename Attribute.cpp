// Attribute.cpp
#ifndef ATTRIBUTE_CPP_
#define ATTRIBUTE_CPP_

#include "Attribute.h"

template<typename T>
Attribute<T>& Attribute<T>::operator+=(const T& rhs) {
    value += rhs;
    return *this;
}

template<typename T>
T Attribute<T>::getValue() const {
    return value;
}

#endif // ATTRIBUTE_CPP_
