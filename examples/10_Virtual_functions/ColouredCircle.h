#ifndef COLOUREDCIRCLE_H_INCLUDED
#define COLOUREDCIRCLE_H_INCLUDED

#include "Circle.h"

class ColouredCircle : public Circle
{
    friend void swap(ColouredCircle& first, ColouredCircle& second);

    public:
        ColouredCircle(double centerX, double centerY, double radius, const char* colour = "white");
        ColouredCircle(const Point& center, double radius, const char* colour = "white");

        ColouredCircle(const ColouredCircle&);
        ColouredCircle& operator = (const ColouredCircle&);
        virtual ~ColouredCircle() override;

        const char* getColour() const;
        void setColour(const char*);

    public:
        virtual Shape::Type getType() const override;
        virtual ColouredCircle* clone() const override;

    protected:
        virtual void printOwn() const override;

    private:
        char* colour;
};

#endif // COLOUREDCIRCLE_H_INCLUDED
