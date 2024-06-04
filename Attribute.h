#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

template<typename T>
class Attribute {
private:
    T value;

public:
    Attribute() : value(T()) {}

    Attribute(T val) : value(val) {}

    Attribute<T>& operator+=(const T& rhs) {
        value += rhs;
        return *this;
    }

    T getValue() const {
        return value;
    }
};

#endif // ATTRIBUTE_H_

