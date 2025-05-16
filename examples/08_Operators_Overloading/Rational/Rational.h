#pragma once

#ifndef _RATIONAL_HEADER_INCLUDED_
#define _RATIONAL_HEADER_INCLUDED_

#include <iostream>

class Rational
{
    public:
        // �����������, ����� ��������� �� � ������������ �� ���������
        // ������������� ���� �� �� �������� �� ������ ������������� 
        // �� ���� ����� �� ����������
        Rational(int = 0, int = 1);

        // ���������
        // ����� ��������� �� ������������ �����
        int getNumerator() const;
        // ����� ����������� �� ������������ �����
        int getDenominator() const;

        // ��������
		// �� ������� �� ��������� � ����������� �� ���������� ����� 
        void setNumerator(int);
        void setDenominator(int);

        // ������������� ���������

        // x += y, 
        // � ��� ������ �������� x �� �������, ��� ���� ��������� �� ����������, 
        // ������ ������� �������� y ������ ������
        // ����������� ���� ����-������� �� �����
        Rational& operator += (const Rational&);
        Rational& operator -= (const Rational&);

        // ������������� �� ���������� �� ������������� �� double
        // ����������� �� ������ ���� ����-������� �� �����
        explicit operator double() const;

        // ��������� ������ ���� ������������ (�������)
        // �������� �� ���������� �� ������� (), ���������� ������ ���������� ����� ������� ����� 
        // �������� �� ���������� ������
        // ���������� () ������ �� ����������� ���� ����-������� �� �����
        double operator()() const;

        // O��������� �� ���� � ����� �� �������������.
        // ������ �������� �� � ���������� �����, � �����. 
        // ������� �������� ������ �� ��������� ���� ������ �������.
		friend std::ostream& operator << (std::ostream&, const Rational&);
        friend std::istream& operator >> (std::istream&, Rational&);

    private:
        int numerator;
        int denominator;
};

// ��������� ���������� ���������� ����� ���������� �����

// �������� �� ���������� �����
// x + y, �������� �� �� ����������� �� +? ����� � ����������?
// ���������� ������� ���� ���������� �����, 
// ��� �� ������� ����������� �� ����� ���������.
// ������ �������� �� ���������� � ���������� �����,
// ������ ���������� ���� �� ���� ������������� � ���� ����-������� �� �����.
const Rational operator + (const Rational&, const Rational&);

const Rational operator - (const Rational&, const Rational&);
const Rational operator * (const Rational&, const Rational&);
const Rational operator / (const Rational&, const Rational&);

// ��������� ���������� ���������� � ���� �����

// ������ �������� �� ���������� � ���� �����, 
// ����� ��������, �� ���������� ������ �� �� �����������
// � ������ �������, �� ���� �� � ����-������� �� �����

// ��� ���������� ����������� �������� ���� ������ �������
// � �����������, ����� ���� �� �� �������� �� �������������,
// ���������� ����� �� �� ���������, ���� � �� �� �� ����������

//const Rational operator + (int, const Rational&);
//const Rational operator - (int, const Rational&);
//const Rational operator * (int, const Rational&);
//const Rational operator / (int, const Rational&);

// �������, ����� ��������� ����������� ��������
// ����� ���������� �����
bool operator == (const Rational&, const Rational&);
bool operator != (const Rational&, const Rational&);
bool operator <  (const Rational&, const Rational&);
bool operator <= (const Rational&, const Rational&);
bool operator >  (const Rational&, const Rational&);
bool operator >= (const Rational&, const Rational&);

// ������ �������� � ���������� �����
const Rational operator + (const Rational&);
const Rational operator - (const Rational&);

// ++ � --
Rational& operator++(Rational&);                //  ++r
const Rational operator++(Rational&, int);      //  r++

Rational& operator--(Rational&);                //  --r
const Rational operator--(Rational&, int);      //  r--

#endif // _RATIONAL_HEADER_INCLUDED_
