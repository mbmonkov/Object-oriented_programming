#include <iostream>
#include "Rational.h"

// ������������ �������, ����� ��������� ��� ������������ ��
// ���������� ����� � ������������ �� � �������� �� 0

// �������������� ��������� � 0, � ����������� � 1
Rational::Rational(int numer, int denom)
	: numerator(numer)
{
	setDenominator(denom);
}

// ��������, ����� ����� ��������� �� ���. �����
int Rational::getNumerator() const
{
	return numerator;
}

// ��������, ����� ����� ����������� �� ���. �����
int Rational::getDenominator() const
{
	return denominator;
}

// ��������
void Rational::setNumerator(int numer)
{
	numerator = numer;
}

void Rational::setDenominator(int denom)
{
	if (0 == denom)
		throw "Invalid denominator!";

	denominator = denom;
}

// ������������� ���������
// �������� �� ���������� �����

// += ��������, ������� ������� �����
Rational& Rational::operator += (const Rational& rhs)
{
	// ������� ����� �� �������
	numerator = numerator * rhs.denominator + denominator * rhs.numerator;
	denominator = denominator * rhs.denominator;

	// ���������� � ����������� ����� �����
	return *this;
}

// -= ������� ������� �����
Rational& Rational::operator -= (const Rational& rhs)
{
	// ������� ����� �� �������
	numerator = numerator * rhs.denominator - denominator * rhs.numerator;
	denominator = denominator * rhs.denominator;

	// ���������� � ����������� ����� �����
	return *this;
}

Rational::operator double() const
{
	return (double)numerator / denominator;
}

const Rational operator + (const Rational& lhs, const Rational& rhs)
{
	// + ���� �� �������� ������������ +=
	// � ��������� ��������� ����� ����� ��������,
	// ���� ����� �������� � ������ ��������

	Rational result = lhs;
	result += rhs;
	return result;

}

// ��������� �� ���������� �����
const Rational operator - (const Rational& lhs, const Rational& rhs)
{
	Rational result = lhs;
	result -= rhs;
	return result;
}

// ��������� �� ���������� �����
// ������ �������, ���� ������ �� ����-�������
const Rational operator * (const Rational& lhs, const Rational& rhs)
{
	// ��� ����� ���������� *=, ���� �� �� �������� ��...
	return Rational(lhs.getNumerator() * rhs.getNumerator(), lhs.getDenominator() * rhs.getDenominator());
}

// ������ �� ���������� �����
const Rational operator / (const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.getNumerator() * rhs.getDenominator(), lhs.getDenominator() * rhs.getNumerator());
}

//// �������, ����� ���������� ���������� � ���� �����
//// �������� �� ���������� ����� � ����
//const Rational operator + (int number, const Rational& rat)
//{
//	// ���������� � �����������
//	return rat + number;
//
//	// ����, ����� � �� ���� �����, 
//	// ��� �� ������ �������, �� ���� �� ���� ���� �� ���� �����
//
//	// + �������� ���� �������� Rational, 
//	// �� ����������� � �������� ������ ��������� �� �����������, 
//	// ����� ��������� ���� �������� ������������ �� ���������.
//	// �������� ��, �� ������ �� ������� ����� Rational,
//	// ���� �� ������� ����������� � ��������� (number, 0)
//}

//// ��������� �� ���������� ����� � ����
//const Rational operator - (int number, const Rational& rat)
//{
//	// ������ �������� -, ����� �� ������� ����� �� rat
//	return - rat + number;
//}
//
//// ��������� �� ���������� ����� � ����
//const Rational operator * (int number, const Rational& rat)
//{
//	// ���������� � �����������
//	return rat * number;
//}
//
//// ������ �� ���������� ����� � ����
//const Rational operator / (int number, const Rational& rat)
//{
//	return Rational(number) / rat;
//}

double Rational::operator()() const
{
	return (double)(*this);
}

std::ostream& operator << (std::ostream& out, const Rational& rat)
{
	out << rat.numerator << "/" << rat.denominator;
	return out;
}

std::istream& operator >> (std::istream& in, Rational& rat)
{
	// �������� ������� ������: ��������/����������
	char slash = ' ';
	
	// �� �� ������� ������ rat ��� ������� ��� ���������� �� ������,
	// ����� ��� �������� ����������
	int num = -1;
	in >> num;

	in >> slash;
	if (slash != '/')
		in.setstate(std::ios::failbit);
	
	int denom = 1;
	in >> denom;

	// ��� ������� � � ����� ���������,
	// ��������� ������
	if (in)
	{
		rat.numerator = num;
		rat.denominator = denom;
	}

	return in;
}

// �������, ����� ��������� ����������� ��������
// ����� ���������� �����
bool operator == (const Rational& lhs, const Rational& rhs)
{
	return
		lhs.getNumerator() * rhs.getDenominator() == 
		lhs.getDenominator() * rhs.getNumerator();
}

bool operator != (const Rational& lhs, const Rational& rhs)
{
	return !(lhs == rhs);
}

bool operator < (const Rational& lhs, const Rational& rhs)
{
	return
		lhs.getNumerator() * rhs.getDenominator() < 
		lhs.getDenominator() * rhs.getNumerator();
}

bool operator <= (const Rational& lhs, const Rational& rhs)
{
	// return !(rhs < lhs);
	return lhs < rhs || lhs == rhs;
}

bool operator > (const Rational& lhs, const Rational& rhs)
{
	return rhs < lhs;
}

bool operator >= (const Rational& lhs, const Rational& rhs)
{
	// return rhs <= lhs;
	return !(lhs < rhs);
}

// ������ �������� � ���������� �����
const Rational operator + (const Rational& rat)
{
	// ����� �����
	return rat;
}

const Rational operator - (const Rational& rat)
{
	return Rational(-rat.getNumerator(), rat.getDenominator());
}

// ��������� ����� �� ���������
Rational& operator++(Rational& rat)                
{
	rat += 1;
	return rat;
}

// ���������� �����, �� �� �� ��������� �� �����������,
// � ����������� �� ��������� �� ������ ���� ���������,
// ����� �� �� �������� ������ (dummy)
const Rational operator++(Rational& rat, int dummy)
{
	Rational old = rat;
	++rat;
	return old;
}

// -- rat;
Rational& operator--(Rational& rat)
{
	rat -= 1;
	return rat;
}

// rat -- dummy
// �� �� �� ��������� 
const Rational operator--(Rational& rat, int dummy)
{
	Rational old = rat;
	--rat;
	return old;
}