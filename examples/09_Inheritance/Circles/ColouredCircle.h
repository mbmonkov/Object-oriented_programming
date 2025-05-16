#ifndef COLOUREDCIRCLE_H_INCLUDED
#define COLOUREDCIRCLE_H_INCLUDED

#include "Circle.h"

class ColouredCircle : public Circle
{
    public:
        ColouredCircle(double centerX, double centerY, double radius, const char* colour = "white");
        ColouredCircle(const Point& center, double radius, const char* colour = "white");

        ColouredCircle(const ColouredCircle&);
        ColouredCircle& operator = (const ColouredCircle&);
        ~ColouredCircle();

        const char* getColour() const;
        void setColour(const char*);

        void print() const;

    private:
        char* colour;
};

#endif // COLOUREDCIRCLE_H_INCLUDED
