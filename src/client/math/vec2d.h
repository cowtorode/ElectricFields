//
// Created by cory on 11/30/23.
//

#ifndef CPPTEST_VEC2D_H
#define CPPTEST_VEC2D_H

#include <string>

class Vec2D {
private:
    double x;
    double y;
public:
    Vec2D();

    Vec2D(double x, double y);

    double getX() const { return x; }

    double getY() const { return y; }

    double getMagnitude() const;

    Vec2D *operator+=(Vec2D vec);

    Vec2D operator+(Vec2D vec) const;

    Vec2D operator-(Vec2D vec) const;

    Vec2D operator*(double scalar) const;

    Vec2D operator/(double scalar) const;
};


#endif //CPPTEST_VEC2D_H
