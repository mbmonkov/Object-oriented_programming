#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

class Circle
{
    public:
        Circle(double x = 0, double y = 0, double r = 0);
        Circle(const Point&, double);
        // само за извеждане...
        ~Circle();

        const Point& getCenter() const { return center; }
        double getRadius() const { return radius; }

        void print() const;

        void setRadius(double);
        void setCenter(double, double);
        void setCenter(const Point&);

        bool isInside(const Point& ) const;
        bool intersect(const Circle& ) const;

    private:
        Point center;
        double radius;
};

#endif // CIRCLE_H
