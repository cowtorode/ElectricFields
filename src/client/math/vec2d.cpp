//
// Created by cory on 11/30/23.
//

#include <cmath>
#include "vec2d.h"

Vec2D::Vec2D(double x, double y) : x(x), y(y) { }

Vec2D::Vec2D() : Vec2D(0, 0) { }

Vec2D * Vec2D::operator+=(Vec2D vec) {
    x += vec.x;
    y += vec.y;

    // returns a pointer to this vector object after adding the vector argument
    return this;
}

Vec2D Vec2D::operator+(Vec2D vec) const {
    // this + vec
    // this works because addition is commutative
    vec.x += x;
    vec.y += y;

    // returns the original passed vector object after adding this vector to the argument.
    // this method does not change the values of this object, but returns a new copy,
    // (the copy is made when you pass a vector into the method)
    return vec;
}

Vec2D Vec2D::operator-(Vec2D vec) const {
    // this - vec
    vec.x = x - vec.x;
    vec.y = y - vec.y;

    // returns the original passed vector object after adding this vector to the argument.
    // this method does not change the values of this object, but returns a new copy,
    // (the copy is made when you pass a vector into the method)
    return vec;
}

Vec2D Vec2D::operator*(double scalar) const {
    // this * scalar
    return Vec2D{x * scalar, y * scalar};
}

Vec2D Vec2D::operator/(double scalar) const {
    // this / scalar
    return Vec2D{x / scalar, y / scalar};
}

double Vec2D::getMagnitude() const {
    return sqrt(x * x + y * y);
}
