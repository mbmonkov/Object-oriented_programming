#include <iostream>
#include "Rational.h"

// единственото условие, което поставяме при дефинирането на
// рационални числа е знаменателят да е различен от 0

// инициализираме числителя с 0, а знаменателя с 1
Rational::Rational(int numer, int denom)
	: numerator(numer)
{
	setDenominator(denom);
}

// селектор, който връща числителя на рац. число
int Rational::getNumerator() const
{
	return numerator;
}

// селектор, който връща знаменателя на рац. число
int Rational::getDenominator() const
{
	return denominator;
}

// мутатори
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

// предефинирани оператори
// събиране на рационални числа

// += натрупва, променя текущия обект
Rational& Rational::operator += (const Rational& rhs)
{
	// текущят обект се променя
	numerator = numerator * rhs.denominator + denominator * rhs.numerator;
	denominator = denominator * rhs.denominator;

	// резултатът е промененият текущ обект
	return *this;
}

// -= променя текущия обект
Rational& Rational::operator -= (const Rational& rhs)
{
	// текущят обект се променя
	numerator = numerator * rhs.denominator - denominator * rhs.numerator;
	denominator = denominator * rhs.denominator;

	// резултатът е промененият текущ обект
	return *this;
}

Rational::operator double() const
{
	return (double)numerator / denominator;
}

const Rational operator + (const Rational& lhs, const Rational& rhs)
{
	// + може да използва дефинираният +=
	// в резултата записваме първо левия аргумент,
	// след което добавяме и десния аргумент

	Rational result = lhs;
	result += rhs;
	return result;

}

// изваждане на рационални числа
const Rational operator - (const Rational& lhs, const Rational& rhs)
{
	Rational result = lhs;
	result -= rhs;
	return result;
}

// умножение на рационални числа
// външна функция, няма достъп до член-данните
const Rational operator * (const Rational& lhs, const Rational& rhs)
{
	// ако имаме дефинирано *=, може да се използва то...
	return Rational(lhs.getNumerator() * rhs.getNumerator(), lhs.getDenominator() * rhs.getDenominator());
}

// делене на рационални числа
const Rational operator / (const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.getNumerator() * rhs.getDenominator(), lhs.getDenominator() * rhs.getNumerator());
}

//// функции, които реализират аритметика с цяло число
//// събиране на рационално число с цяло
//const Rational operator + (int number, const Rational& rat)
//{
//	// операцията е комутативна
//	return rat + number;
//
//	// така, кодът е на едно място, 
//	// ако се налага промяна, тя също ще бъде само на едно място
//
//	// + получава като аргумент Rational, 
//	// но обръщението е възможно заради наличието на конструктор, 
//	// чиито аргументи имат зададени подразбиращи се стойности.
//	// Получава се, че неявно се създава обект Rational,
//	// като се извиква конструктор с аргументи (number, 0)
//}

//// изваждане на рационално число и цяло
//const Rational operator - (int number, const Rational& rat)
//{
//	// унарна операция -, която ще промени знака на rat
//	return - rat + number;
//}
//
//// умножение на рационално число с цяло
//const Rational operator * (int number, const Rational& rat)
//{
//	// операцията е комутативна
//	return rat * number;
//}
//
//// делене на рационално число с цяло
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
	// очакваме следния формат: числител/знаменател
	char slash = ' ';
	
	// за да запазим обекта rat без промяна при възникване на грешка,
	// четем във временни променливи
	int num = -1;
	in >> num;

	in >> slash;
	if (slash != '/')
		in.setstate(std::ios::failbit);
	
	int denom = 1;
	in >> denom;

	// ако потокът е в добро състояние,
	// променяме обекта
	if (in)
	{
		rat.numerator = num;
		rat.denominator = denom;
	}

	return in;
}

// функции, които реализира логическите операции
// между рационални числа
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

// унарни операции с рационални числа
const Rational operator + (const Rational& rat)
{
	// връща копие
	return rat;
}

const Rational operator - (const Rational& rat)
{
	return Rational(-rat.getNumerator(), rat.getDenominator());
}

// префиксна форма на оператора
Rational& operator++(Rational& rat)                
{
	rat += 1;
	return rat;
}

// постфиксна форма, за да се различава от префиксната,
// в дефиницията на функцията се добавя един параметър,
// който не се използва никъде (dummy)
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
// за да се различава 
const Rational operator--(Rational& rat, int dummy)
{
	Rational old = rat;
	--rat;
	return old;
}