#include <iostream>

// за да се избегнат конфликтите,
// пакетираме изброения тип в namespace
namespace Color
{
	enum Color
	{
		UNKNOWN = -1,
		BLUE,	// 0
		RED,	// 1
		GRAY,	// 2 
		BLACK,	// 3
		COUNT
	};
}

// за да се избегнат конфликтите
namespace Feeling
{
	enum Feeling
	{
		UNKNOWN = -1,
		TIRED,
		HAPPY,
		BLUE,
		COUNT
	};
}

bool isValid(Color::Color value)
{
	return value > Color::UNKNOWN && value < Color::COUNT;
}

void print(Color::Color c)
{
	if (!isValid(c))
	{
		std::cout << "Not a valid color!\n" << std::endl;
		return;
	}

	// неявно преобразуване до цяло число
	static const char* colors[Color::COUNT] = { "blue", "red", "gray", "black" };
	std::cout << colors[c] << std::endl;
}

int main()
{
	Color::Color c;
	c = Color::BLACK;
	print(c);

	int value;
	std::cin >> value;
	c = (Color::Color)value;
	print(c);

	// обхождане на всички елементи на изброения тип
	for (int c = Color::UNKNOWN + 1; c < Color::COUNT; ++c)
	{
		print((Color::Color)c);
	}

	return 0;
}