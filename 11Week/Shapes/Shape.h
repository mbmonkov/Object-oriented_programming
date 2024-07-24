#pragma once
#include <iostream> 

class Shape   // Декларира абстрактен клас Shape - не може да се създават инстанции от този клас
{
protected:
    struct point  // Декларира структура point, която представлява точка с координати x и y
    {
        point() :x(0), y(0) {}  // Конструктор по подразбиране, който инициализира x и y с 0
        point(int x, int y) :x(x), y(y) {}  // Конструктор с параметри, който инициализира x и y с дадени стойности
        int x;  // Координата x на точката
        int y;  // Координата y на точката
        double getDist(const point& other) const  // Метод за изчисляване на разстоянието до друга точка
        {
            int dx = x - other.x;  // Разлика по x координатата
            int dy = y - other.y;  // Разлика по y координатата

            return sqrt(dx * dx + dy * dy);  // Връща разстоянието, изчислено чрез формулата за Евклидово разстояние
        }
    };
    const point& getPointAtIndex(size_t index) const;  // Декларира метод за вземане на точка по индекс (само за четене)

private:
    point* points;  
    size_t pointsCount;  

    void copyFrom(const Shape& other);  // Метод за копиране на данни от друг обект от клас Shape
    void moveFrom(Shape&& other);  // Метод за преместване на данни от друг обект от клас Shape (rvalue reference)
    void free();  // Метод за освобождаване на ресурси

public:
    Shape(size_t pointsCount);  // Конструктор с параметър за брой точки

    Shape(const Shape& other);  // Конструктор за копиране
    Shape(Shape&& other) noexcept;  // Конструктор за преместване (noexcept указва, че не хвърля изключения)

    Shape& operator=(const Shape& other);  // Оператор за присвояване (копиране)
    Shape& operator=(Shape&& other) noexcept;  // Оператор за присвояване (преместване) с гаранция, че не хвърля изключения

    virtual ~Shape();  // Виртуален деструктор, който гарантира правилно почистване при наследяване

    void setPoint(size_t pointIndex, int x, int y);  // Метод за задаване на координатите на точка по индекс

    virtual double getArea() const = 0;  // Чисто виртуален метод за изчисляване на площ (трябва да се имплементира в наследници)
    virtual double getPer()  const;  // Виртуален метод за изчисляване на периметър (може да бъде имплементиран или преопределен в наследници)
    virtual bool isPointIn(int x, int y) const = 0;  // Чисто виртуален метод за проверка дали точка с координати (x, y) е вътре във формата (трябва да се имплементира в наследници)
};
