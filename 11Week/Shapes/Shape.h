#pragma once
#include <iostream> 

class Shape   // ��������� ���������� ���� Shape - �� ���� �� �� �������� ��������� �� ���� ����
{
protected:
    struct point  // ��������� ��������� point, ����� ������������ ����� � ���������� x � y
    {
        point() :x(0), y(0) {}  // ����������� �� ������������, ����� ������������ x � y � 0
        point(int x, int y) :x(x), y(y) {}  // ����������� � ���������, ����� ������������ x � y � ������ ���������
        int x;  // ���������� x �� �������
        int y;  // ���������� y �� �������
        double getDist(const point& other) const  // ����� �� ����������� �� ������������ �� ����� �����
        {
            int dx = x - other.x;  // ������� �� x ������������
            int dy = y - other.y;  // ������� �� y ������������

            return sqrt(dx * dx + dy * dy);  // ����� ������������, ��������� ���� ��������� �� ��������� ����������
        }
    };
    const point& getPointAtIndex(size_t index) const;  // ��������� ����� �� ������� �� ����� �� ������ (���� �� ������)

private:
    point* points;  
    size_t pointsCount;  

    void copyFrom(const Shape& other);  // ����� �� �������� �� ����� �� ���� ����� �� ���� Shape
    void moveFrom(Shape&& other);  // ����� �� ����������� �� ����� �� ���� ����� �� ���� Shape (rvalue reference)
    void free();  // ����� �� ������������� �� �������

public:
    Shape(size_t pointsCount);  // ����������� � ��������� �� ���� �����

    Shape(const Shape& other);  // ����������� �� ��������
    Shape(Shape&& other) noexcept;  // ����������� �� ����������� (noexcept ������, �� �� ������ ����������)

    Shape& operator=(const Shape& other);  // �������� �� ����������� (��������)
    Shape& operator=(Shape&& other) noexcept;  // �������� �� ����������� (�����������) � ��������, �� �� ������ ����������

    virtual ~Shape();  // ��������� ����������, ����� ��������� �������� ���������� ��� �����������

    void setPoint(size_t pointIndex, int x, int y);  // ����� �� �������� �� ������������ �� ����� �� ������

    virtual double getArea() const = 0;  // ����� ��������� ����� �� ����������� �� ���� (������ �� �� ������������ � ����������)
    virtual double getPer()  const;  // ��������� ����� �� ����������� �� ��������� (���� �� ���� ������������� ��� ������������ � ����������)
    virtual bool isPointIn(int x, int y) const = 0;  // ����� ��������� ����� �� �������� ���� ����� � ���������� (x, y) � ����� ��� ������� (������ �� �� ������������ � ����������)
};
