#include "MyString.h"
#include <cstring>
#include <algorithm>
#pragma warning (disable : 4996)


static unsigned roundToPowerOfTwo(unsigned v) //static! -> will be discused in the next lecture
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
    return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* data)
{
    _size = std::strlen(data);
    _allocatedDataSize = dataToAllocByStringLen(_size);
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, data);
}

MyString::MyString(size_t stringLength)
{
    _allocatedDataSize = dataToAllocByStringLen(stringLength);
    _data = new char[_allocatedDataSize];
    _size = 0;
    _data[0] = '\0';
}

MyString::MyString(const MyString& other)
{
    copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MyString::~MyString()
{
    free();
}

size_t MyString::getCapacity() const
{
    return _allocatedDataSize - 1;
}

size_t MyString::getSize() const
{
    return _size;
}

const char* MyString::c_str() const
{
    return _data;
}

MyString& MyString::operator+=(const MyString& other)
{
    if (getSize() + other.getSize() + 1 > _allocatedDataSize)
        resize(dataToAllocByStringLen(getSize() + other.getSize()));

    // we need to use strncat instead of strcat, because strcat will not work for str += str 
    // (the terminating zero of str will be destroyed by the first char)
    std::strncat(_data, other._data, other.getSize());

    _size = getSize() + other.getSize();
    return *this;
}

char& MyString::operator[](size_t index)
{
    return _data[index]; // no security check!!
}

const char& MyString::operator[](size_t index) const
{
    return _data[index]; // no security check!!
}

std::ostream& operator<<(std::ostream& os, const MyString& obj)
{
    return os << obj._data;
}

std::istream& operator>>(std::istream& is, MyString& ref)
{
    char buff[1024];
    is >> buff;
    size_t buffStringSize = std::strlen(buff);

    if (buffStringSize > ref.getCapacity())
        ref.resize(dataToAllocByStringLen(buffStringSize));

    strcpy(ref._data, buff);
    ref._size = buffStringSize;
    return is;
}

void MyString::resize(unsigned newAllocatedDataSize)
{
    char* newData = new char[newAllocatedDataSize + 1];
    std::strcpy(newData, _data);
    delete[] _data;
    _data = newData;
    _allocatedDataSize = newAllocatedDataSize;
}

void MyString::free()
{
    delete[] _data;
}

void MyString::copyFrom(const MyString& other)
{
    _allocatedDataSize = other._allocatedDataSize;
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, other._data);
    _size = other._size;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
    MyString result(lhs.getSize() + rhs.getSize());
    result += lhs; // no resize is needed
    result += rhs;
    return result;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}


#include "NVector.h"

NVector::NVector(size_t n) : size(n)
{
	data = new int[n];

	for (int i = 0; i < n; i++)
		data[i] = 0;
}

NVector::NVector(const NVector& other)
{
	copyFrom(other);
}

NVector& NVector::operator=(const NVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
NVector::~NVector()
{
	free();
}

void NVector::copyFrom(const NVector& other)
{
	size = other.size;
	data = new int[size];

	for (int i = 0; i < size; i++)
		data[i] = other.data[i];
}
void NVector::free()
{
	delete[] data;
	size = 0;
}



//v += v1;
NVector& NVector::operator+=(const NVector& other)
{
	if (size != other.size)
		throw "The vectors should have the same size!";

	for (int i = 0; i < size; i++)
		data[i] += other.data[i];

	return *this;
}

NVector& NVector::operator-=(const NVector& other)
{
	if (size != other.size)
		throw "The vectors should have the same size!";

	for (int i = 0; i < size; i++)
		data[i] -= other.data[i];

	return *this;
}

NVector operator+(const NVector& lhs, const NVector& rhs)
{
	NVector lhsCopy(lhs);
	lhsCopy += rhs;

	return lhsCopy;
}

NVector operator-(const NVector& lhs, const NVector& rhs)
{
	NVector lhsCopy(lhs);
	lhsCopy -= rhs;

	return lhsCopy;
}

int& NVector::operator[](size_t index)
{
	if (index >= size)
		throw "Invalid index";

	return data[index];
}

int NVector::operator[](size_t index) const
{
	if (index >= size)
		throw "Invalid index";

	return data[index];
}

size_t NVector::operator~() const
{
	return size;
}

std::ostream& operator<<(std::ostream& os, const NVector& v)
{
	os << "[ ";
	for (int i = 0; i < v.size; i++)
		os << v[i] << " ";
	os << " ]";

	return os;
}

std::istream& operator>>(std::istream& is, NVector& v)
{
	for (int i = 0; i < v.size; i++)
		is >> v[i];

	return is;
}

bool operator||(const NVector& lhs, const NVector& rhs)
{
	if (~lhs != ~rhs) {
		throw "The vectors should have the same size!";
	}

	double ratio = 0.0;
	bool ratioSet = false;

	for (size_t i = 0; i < ~lhs; ++i)
	{
		// Skip if both components are zero
		if (lhs[i] == 0 && rhs[i] == 0)
		{
			continue;
		}
		// If one component is zero but the other is not, vectors are not parallel
		if (lhs[i] == 0 || rhs[i] == 0)
		{
			return false;
		}

		// Calculate the ratio of the current components
		double currentRatio = lhs[i] / rhs[i];
		// If the ratio is not set, set it. Otherwise, compare it with the current ratio
		if (!ratioSet)
		{
			ratio = currentRatio;
			ratioSet = true;
		}
		else if (std::abs(ratio - currentRatio) > 1e-6)
		{ // Use a small epsilon for floating point comparison
			// If the ratios are different, vectors are not parallel
			return false;
		}
	}
	return true;
}

NVector& NVector::operator*=(size_t scalar)
{
	for (int i = 0; i < size; i++)
		data[i] *= scalar;

	return *this;
}

NVector operator*(const NVector& lhs, size_t scalar)
{
	NVector copy(lhs);
	copy *= scalar;
	return copy;
}
NVector operator*(size_t scalar, const NVector& lhs)
{
	return lhs * scalar;
}
size_t operator%(const NVector& lhs, const NVector& rhs)
{
	if (~lhs != ~rhs)
		throw "The vectors should have the same size!";

	size_t res = 0;
	for (int i = 0; i < ~lhs; i++)
		res += lhs[i] * rhs[i];

	return res;
}

bool operator|=(const NVector& lhs, const NVector& rhs)
{
	return  lhs % rhs == 0; //the size check is done by %
}

#include <iostream> 
#include <assert.h> 
#include "String and StringView/MyString.h" 
#include "String and StringView/StringView.h" 

// Клас, който представлява интерпретация на булеви стойности за променливи от 'a' до 'z'
class BooleanInterpretation
{
public:
    // Задава стойност на булева променлива, представена от символа 'ch'
    void set(char ch, bool value)
    {
        assert(ch >= 'a' && ch <= 'z'); 
        values[ch - 'a'] = value;
    }

    // Връща стойността на булева променлива, представена от символа 'ch'
    bool operator()(char ch) const
    {
        assert(ch >= 'a' && ch <= 'z');
        return values[ch - 'a'];
    }

    // Връща броя на булевите променливи, които са зададени на true
    size_t getTrueCount() const
    {
        size_t count = 0;
        for (int i = 0; i < 26; i++)
        {
            if (values[i])
                count++;
        }
        return count;
    }

    // Изключва стойности от маската (чрез нулиране на булевите променливи, в зависимост от стойността на маската)
    void excludeValuesByMask(unsigned mask)
    {
        for (int i = 25; i >= 0; i--)
        {
            if (values[i])
            {
                if (mask % 2 == 0) // последният бит е 0
                    values[i] = false;
                mask /= 2; // премахва последния бит
            }
        }
    }
private:
    bool values[26]{ false }; // Масив за съхранение на булевите стойности за променливи от 'a' до 'z'
};

// Абстрактен базов клас за булеви изрази
struct BooleanExpression
{
    BooleanExpression() = default; // Конструктор по подразбиране
    BooleanExpression(const BooleanExpression&) = delete; // Забранява копирането
    BooleanExpression& operator=(const BooleanExpression&) = delete; // Забранява оператор за копиране

    virtual bool eval(const BooleanInterpretation& interpet) const = 0; // Чиста виртуална функция за оценка на израза
    virtual ~BooleanExpression() = default; // Деструктор по подразбиране
    virtual BooleanExpression* clone() const = 0; // Чиста виртуална функция за клониране на израза

    virtual void populateVariables(BooleanInterpretation& interpret) const = 0; // Чиста виртуална функция за попълване на променливи
};

// Представлява булева променлива
struct Var : BooleanExpression
{
private:
    char ch;

public:
    Var(char ch) : ch(ch) {} // Конструктор

    bool eval(const BooleanInterpretation& interpet) const override 
    {
        return interpet(ch);
    }

    virtual BooleanExpression* clone() const override 
    {
        return new Var(ch);
    }

    void populateVariables(BooleanInterpretation& interpret) const override 
    {
        interpret.set(ch, true);
    }
};

// Абстрактен клас за унарни операции върху булеви изрази
struct UnaryOperation : BooleanExpression
{
    UnaryOperation(BooleanExpression* expr) : expr(expr) {} // Конструктор

    void populateVariables(BooleanInterpretation& interpret) const override
    {
        expr->populateVariables(interpret);
    }

    ~UnaryOperation()
    {
        delete expr;
    }
protected:
    BooleanExpression* expr; // "подизраз" на операцията
};

// Представлява логическо отрицание (NOT)
struct Negation : UnaryOperation
{
    Negation(BooleanExpression* expr) : UnaryOperation(expr) {} // Конструктор

    virtual BooleanExpression* clone() const override
    {
        return new Negation(expr->clone());
    }

    bool eval(const BooleanInterpretation& interpet) const override
    {
        return !expr->eval(interpet);
    }
};

// Абстрактен клас за бинарни операции върху булеви изрази
struct BinaryOperation : BooleanExpression
{
    BinaryOperation(BooleanExpression* left, BooleanExpression* right) : left(left), right(right) {} // Конструктор

    void populateVariables(BooleanInterpretation& interpret) const override 
    {
        left->populateVariables(interpret);
        right->populateVariables(interpret);
    }

    ~BinaryOperation() 
    {
        delete left;
        delete right;
    }
protected:
    BooleanExpression* left; // Ляв "подизраз"
    BooleanExpression* right; // Десен "подизраз"
};

// Представлява логическа конюнкция (AND)
struct Conjunction : BinaryOperation
{
    Conjunction(BooleanExpression* left, BooleanExpression* right) : BinaryOperation(left, right) {} // Конструктор

    virtual BooleanExpression* clone() const override
    {
        return new Conjunction(left->clone(), right->clone());
    }

    bool eval(const BooleanInterpretation& interpet) const override 
    {
        return left->eval(interpet) && right->eval(interpet);
    }
};

// Представлява логическа дизюнкция (OR)
struct Disjunction : BinaryOperation
{
    Disjunction(BooleanExpression* left, BooleanExpression* right) : BinaryOperation(left, right) {} // Конструктор

    virtual BooleanExpression* clone() const override 
    {
        return new Disjunction(left->clone(), right->clone());
    }

    bool eval(const BooleanInterpretation& interpet) const override 
    {
        return left->eval(interpet) || right->eval(interpet);
    }
};

// Представлява импликация (IMPLIES)
struct Implies : BinaryOperation
{
    Implies(BooleanExpression* left, BooleanExpression* right) : BinaryOperation(left, right) {} // Конструктор

    BooleanExpression* clone() const override 
    {
        return new Implies(left->clone(), right->clone());
    }

    bool eval(const BooleanInterpretation& interpet) const override 
    {
        return !left->eval(interpet) || right->eval(interpet);
    }
};

// Функция за създаване на булеви изрази от низ
BooleanExpression* expressionFactory(StringView str)
{
    str = str.substr(1, str.length() - 2); // Премахва първата и последната скоба

    if (str.length() == 1)
        return new Var(str[0]); // Ако дължината на низа е 1, създава променлива

    unsigned count = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
            count++;
        else if (str[i] == ')')
            count--;
        else if (count == 0)
        {
            switch (str[i])
            {
            case '!': return new Negation(expressionFactory(str.substr(i + 1, str.length() - i - 1)));
            case '&': return new Conjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
            case '|': return new Disjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
            case '>': return new Implies(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
            }
        }
    }
    throw std::invalid_argument("Invalid expression!"); // Хвърля изключение, ако изразът е невалиден
}

// Клас, който управлява булевите изрази
class BooleanExpressionHandler
{
private:

    // Проверява всички възможни присвоявания на булеви стойности, за да види дали изразът е тавтология или противоречие
    bool checkAllTruthAssignments(bool value) const
    {
        size_t varsCount = myVariables.getTrueCount(); // Брои колко променливи са зададени на true
        size_t powerOfTwo = 1 << varsCount; // Определя броя на възможните комбинации от булеви стойности
        for (int i = 0; i < powerOfTwo; i++)
        {
            BooleanInterpretation current = myVariables; // Създава копие на интерпретацията на променливите
            current.excludeValuesByMask(i); // Изключва стойности в зависимост от маската
            if (expr->eval(current) != value) // Проверява дали текущото оценяване е различно от очакваното
                return false;
        }
        return true;
    }

    // Освобождава ресурси
    void free()
    {
        delete expr;
    }

    // Копира данни от друг обект
    void copyFrom(const BooleanExpressionHandler& other)
    {
        expr = other.expr->clone(); // Клонира израза
        myVariables = other.myVariables; // Копира променливите
    }

    // Премества данни от друг обект
    void moveFrom(BooleanExpressionHandler&& other)
    {
        expr = other.expr; // Прехвърля собствеността на израза
        myVariables = std::move(other.myVariables); // Премества променливите
        other.expr = nullptr; // Нулира израза в другия обект
    }

    BooleanInterpretation myVariables; // Променливи за оценка на булевия израз
    BooleanExpression* expr = nullptr; // Указател към текущия булев израз

public:
    BooleanExpressionHandler(const MyString& str)
    {
        expr = expressionFactory(str); // Създава булев израз от низ
        expr->populateVariables(myVariables); // Попълва променливите в интерпретацията
    }


       // Конструктор за копиране
    BooleanExpressionHandler(const BooleanExpressionHandler& other)
    {
        copyFrom(other);
    }

    // Оператор за присвояване чрез копиране
    BooleanExpressionHandler& operator=(const BooleanExpressionHandler& other)
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
    }

    // Конструктор за преместване
    BooleanExpressionHandler(BooleanExpressionHandler&& other) noexcept
    {
        moveFrom(std::move(other));
    }

    // Оператор за присвояване чрез преместване
    BooleanExpressionHandler& operator=(BooleanExpressionHandler&& other) noexcept
    {
        if (this != &other)
        {
            free();
            moveFrom(std::move(other));
        }
        return *this;
    }

    // Деструктор
    ~BooleanExpressionHandler()
    {
        free();
    }

    // Оценява булевия израз, използвайки дадената интерпретация
    bool evaluate(const BooleanInterpretation& bi) const
    {
        return expr->eval(bi);
    }

    // Проверява дали изразът е тавтология (винаги истинен)
    bool isTautology() const
    {
        return checkAllTruthAssignments(true);
    }

    // Проверява дали изразът е противоречие (винаги фалшив)
    bool isContradiction() const
    {
        return checkAllTruthAssignments(false);
    }

};

int main()
{
    BooleanExpressionHandler be("((p)|((q)&(t)))"); // Създава булев израз от низ
    BooleanInterpretation bi; // Създава интерпретация на булевите променливи
    bi.set('p', true); // Задава променливата 'p' на true
    std::cout << be.evaluate(bi) << std::endl; // Оценява и отпечатва резултата от израза

    BooleanExpressionHandler be2("((p)|(!(p)))"); // Създава друг булев израз
    std::cout << be2.isTautology() << std::endl; // Проверява и отпечатва дали изразът е тавтология
}
