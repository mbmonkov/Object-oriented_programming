#include <iostream>

enum Color
{
	// всички константи от този тип
	UNKNOWN = -1,
	BLUE,	// 0
	RED,	// 1
	GRAY,	// 2 
	BLACK,	// 3
	COUNT
};

enum Feeling
{
	// префикс при в имената на константите,
	// за да избегнем дублирането на имена

	F_TIRED = 7,	// == 7
	F_HAPPY,		// == 8
	// съвпадение с BLUE в Color
	F_BLUE = 10	// == 10
};

bool isValid(Color value)
{
	// префиксът Color:: може и да се пропусне, но 
	// по този начин е по-лесно за четене
	return value > Color::UNKNOWN && value < Color::COUNT;
}

void printAsText(Color c)
{
	if (!isValid(c))
	{
		std::cout << "Not a valid color!" << std::endl;
		return;
	}

	static const char* colors[COUNT] = { "blue", "red", "gray", "black" };
	std::cout << colors[c] << std::endl;
}

void print(Color c)
{
	switch (c)
	{
		case RED:	std::cout << "red";		break;
		case BLUE:	std::cout << "blue";	break;
		case GRAY:	std::cout << "gray";	break;
		case BLACK: std::cout << "black";	break;

		default:
			std::cout << "Not a valid color!\n";

		// за да няма warning, ако не ги включим в switch-а
		case UNKNOWN:
		case COUNT:	break;
	}
}

int main()
{
	Color c;
	
	c = (Color)2;
	std::cout << c << std::endl;

	// не можем да прочетем стойност от стандартния вход
	// std::cin >> c;

	c = RED;
	std::cout << "color: " << c << std::endl;

	// Color и Feeling са различни типове
	// c = Feeling::F_BLUE;

	int value;
	std::cout << "Enter color (" << UNKNOWN + 1 << ", " << COUNT << "): ";
	std::cin >> value;
	c = (Color)value;
	print(c);

	c = (Color)(c + 1);
	std::cout << "\nNext color: ";
	printAsText(c);

	// как да обходим всички елементи на изброения тип?
	for (int c = UNKNOWN + 1; c < COUNT; ++c)
	{
		printAsText((Color)c);
	}

	// сравняват се числата, с които са кодирани елементие на изброения тип
	std::cout << "\nComparison:\n";
	print(c);
	std::cout << " < ";
	print(RED);
	std::cout << "? " << std::boolalpha << (c < RED) << std::endl;

	// Не сравняваме елементи от различни типове 
	Color::BLUE == Feeling::F_BLUE;

	return 0;
}