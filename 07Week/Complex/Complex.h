#pragma once
#include <iostream>
class Complex
{
public:
	Complex();
	Complex(double real, double im);

	double getReal() const;
	double getIm() const;

	void setReal(double real);
	void setIm(double im);

	Complex getConjugated() const;  //����� ���������� ����������� ����� �� ������� �����.

	//assignment operators 
	// a+=b ��� � �� ������ ���������� �� b. � �� ������� , b �� ��. ����������  �� ����� a �� �� ���� �� �� ������ ������� ������ (a+=b+=c)
	Complex& operator+=(const Complex&);
	Complex& operator-=(const Complex&);
	Complex& operator*=(const Complex&);
	Complex& operator/=(const Complex&);



	//stream opeartors   ( std::cout << c1)  (std::cin >> c1 )
	friend std::ostream& operator<<(std::ostream&, const Complex&);
	friend std::istream& operator>>(std::istream&, Complex&);

private:
	double real;
	double im;

};
// a+b. ���������� ����� ���� ����������(Complex), ����� � ���������� �� ����������.
Complex operator+(const Complex&, const Complex&);
Complex operator-(const Complex&, const Complex&);
Complex operator*(const Complex&, const Complex&);
Complex operator/(const Complex&, const Complex&);

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);
