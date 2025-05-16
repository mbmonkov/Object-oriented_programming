#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"
#include "Shape.h"

class Circle: public Shape
{
    public:
        Circle(double x = 0, double y = 0, double r = 0);
        Circle(const Point&, double);

        const Point& getCenter() const { return center; }
        double getRadius() const { return radius; }

        void setRadius(double);
        void setCenter(double, double);
        void setCenter(const Point&);

        bool isInside(const Point& ) const;
        bool intersect(const Circle& ) const;

    public:
        virtual double getArea() const override; 
        virtual Shape::Type getType() const override;   
        virtual Circle* clone() const override;

    protected:
        virtual void printOwn() const override;

    private:
        Point center;
        double radius;
};

#endif // CIRCLE_H
