#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
    public:
        Point(double x = 0, double y = 0);

        double getX() const;
        double getY() const;

        double getR() const;
        double getT() const;

        double distanceToCenter() const;
        double distance(const Point&) const;

        void setX(double);
        void setY(double);

        void translate(double dx, double dy);

        void print() const;

    private:
        double x, y;
};

#endif // POINT_H
