#include <iostream>

// scoped enumerations
enum class Color
{
	UNKNOWN = -1,
	BLUE,	// 0
	RED,	// 1
	GRAY,	// 2 
	BLACK,	// 3
	COUNT
};

enum class Feeling
{
	UNKNOWN = -1,
	TIRED,
	HAPPY,
	BLUE,
	COUNT
};

bool isValid(Color value)
{
	return value > Color::UNKNOWN && value < Color::COUNT;
}

void print(Color c)
{
	if (!isValid(c))
	{
		std::cout << "not value" << std::endl;
		return;
	}

	// няма неявно преобразуване между базовия тип и Color
	static const char* colors[(int)Color::COUNT] = { "red", "blue", "gray", "black" };
	std::cout << colors[(int)c] << std::endl;
}

int main()
{
	Color c;
	// не може да се прочете стойност от стандартния вход
	// std::cin >> c;
	// нито да се изведе на стандартния изход
	// std::cout << c << std::endl;

	// изрично трябва да се посочи името на изброения тип
	// само BLACK не може да се използва
	c = Color::BLACK;

	int value;
	std::cin >> value;
	c = (Color)value;
	print(c);

	// не могат да се прилагат аритметични операции без явно преобразуване до базовия тип
	//c = (Color)(c + 1);

	for (int c = (int)Color::UNKNOWN + 1; c < (int)Color::COUNT; ++c)
	{
		print((Color)c);
	}

	// грешка по време на компилация
	// Feeling::BLUE == Color::BLUE;

	return 0;
}