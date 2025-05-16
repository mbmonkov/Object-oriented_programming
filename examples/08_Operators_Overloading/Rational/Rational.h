#pragma once

#ifndef _RATIONAL_HEADER_INCLUDED_
#define _RATIONAL_HEADER_INCLUDED_

#include <iostream>

class Rational
{
    public:
        // Конструктор, чиито параметри са с подразбиращи се стойности
        // конструкторът може да се използва за неявно преобразуване 
        // на цяло число до рационално
        Rational(int = 0, int = 1);

        // селектори
        // връща числителя на рационалното число
        int getNumerator() const;
        // връща знаменателя на рационалното число
        int getDenominator() const;

        // мутатори
		// за промяна на числителя и знаменателя на рационално число 
        void setNumerator(int);
        void setDenominator(int);

        // предефинирани оператори

        // x += y, 
        // в нея левият аргумент x се променя, той носи резултата от операцията, 
        // докато десният аргумент y остава същият
        // предефинира като член-функция на класа
        Rational& operator += (const Rational&);
        Rational& operator -= (const Rational&);

        // предефиниране на операцията за преобразуване до double
        // предефинира се винаги като член-функция на класа
        explicit operator double() const;

        // разглежда обекта като функционален (функция)
        // символът на операцията са скобите (), операцията работи единствено върху текущия обект 
        // извършва се действието делене
        // операторът () винаги се предефинира като член-функция на класа
        double operator()() const;

        // Oперациите за вход и изход са двуаргументни.
        // Левият аргумент не е рационално число, а поток. 
        // Подобни операции винаги се дефинират като външни функции.
		friend std::ostream& operator << (std::ostream&, const Rational&);
        friend std::istream& operator >> (std::istream&, Rational&);

    private:
        int numerator;
        int denominator;
};

// функциите реализират аритметика между рационални числа

// събиране на рационални числа
// x + y, променят ли се аргументите на +? Какъв е резултатът?
// Операцията създава ново рационално число, 
// без да променя стойностите на двата аргумента.
// Левият аргумент на операцията е рационално число,
// затова операцията може да бъде предефинирана и като член-функция на класа.
const Rational operator + (const Rational&, const Rational&);

const Rational operator - (const Rational&, const Rational&);
const Rational operator * (const Rational&, const Rational&);
const Rational operator / (const Rational&, const Rational&);

// функциите реализират аритметика с цяло число

// левият аргумент на събирането е цяло число, 
// което означава, че операцията трябва да се предефинира
// с външна функция, не може да е член-функция на класа

// при дефинирани аритметични операции като външни функции
// и конструктор, който може да се използва за преобразуване,
// операциите могат да се използват, дори и да не са дефинирани

//const Rational operator + (int, const Rational&);
//const Rational operator - (int, const Rational&);
//const Rational operator * (int, const Rational&);
//const Rational operator / (int, const Rational&);

// функции, които реализира логическите операции
// между рационални числа
bool operator == (const Rational&, const Rational&);
bool operator != (const Rational&, const Rational&);
bool operator <  (const Rational&, const Rational&);
bool operator <= (const Rational&, const Rational&);
bool operator >  (const Rational&, const Rational&);
bool operator >= (const Rational&, const Rational&);

// унарни операции с рационални числа
const Rational operator + (const Rational&);
const Rational operator - (const Rational&);

// ++ и --
Rational& operator++(Rational&);                //  ++r
const Rational operator++(Rational&, int);      //  r++

Rational& operator--(Rational&);                //  --r
const Rational operator--(Rational&, int);      //  r--

#endif // _RATIONAL_HEADER_INCLUDED_
