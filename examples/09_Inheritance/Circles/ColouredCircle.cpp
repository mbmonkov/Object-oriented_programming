#define _CRT_SECURE_NO_WARNINGS

#include "ColouredCircle.h"

#include <cstring>

// Всеки клас се грижи за собствените си член-данни
ColouredCircle::ColouredCircle(double centerX, double centerY, double radius, const char* colour)
    : Circle(centerX, centerY, radius), colour(nullptr)
{
    this->setColour(colour);

    // само информативно, за да се проследи извикването на методите
    std::cout << "\nCreate coloured circle:" << std::endl;
    print();
}

ColouredCircle::ColouredCircle(const Point& center, double radius, const char* colour)
    : Circle(center, radius), colour(nullptr)
{
    this->setColour(colour);
}

// извикване на копиращ конструктор на базовия клас
ColouredCircle::ColouredCircle(const ColouredCircle& other)
    : Circle(other), colour(nullptr)
{
    this->setColour(other.colour);
}

ColouredCircle& ColouredCircle::operator = (const ColouredCircle& other)
{
    if(this != &other)
    {
        // операция за просвояване на базовия клас,
        // която да се погрижи за наследените компоненти
        Circle::operator=(other);

        this->setColour(other.colour);
    }

    return *this;
}

/// Всеки клас се грижи за собствените си член-данни
ColouredCircle::~ColouredCircle()
{
    std::cout << "~ColouredCircle(): " << std::endl;
    print();

    // освобождават се само собствените член-данни
    delete [] this->colour;
    this->colour = nullptr;
}

const char* ColouredCircle::getColour() const
{
    return this->colour;
}

void ColouredCircle::setColour(const char* newColour)
{
    if (!newColour || !*newColour)
        throw std::invalid_argument("Empty color!");

    char* temp = this->colour;

    this->colour = new char [strlen(newColour) + 1];
    strcpy(this->colour, newColour);

    delete[] temp;
}

void ColouredCircle::print() const
{
    Circle::print();
    std::cout << " Colour: " << this->colour << std::endl;
}
