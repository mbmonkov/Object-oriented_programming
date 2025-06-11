#include <iostream>

struct Rat
{
	int num;
	int denom; 
}; 

bool create(Rat& rat, int n, int m)
{
	if (m == 0)
		m = 1;

	//if (m == 0)
	//	return false;

	rat.num = n;
	rat.denom = m;

	return true;
}

int getNum(const Rat& rat)
{
	return rat.num;
}

int getDenom(const Rat& rat)
{
	return rat.denom;
}

Rat add(const Rat& left, const Rat& right)
{
	Rat res;
	create(res, 
				getNum(left) * getDenom(right) + getNum(right) * getDenom(left),
				getDenom(left) * getDenom(right));

	return res;
}

Rat substract(const Rat& left, const Rat& right)
{
	Rat res;
	create(res, getNum(left) * getDenom(right) - getNum(right) * getDenom(left),
				getDenom(left) * getDenom(right));

	return res;
}

Rat multiply(const Rat& left, const Rat& right)
{
	Rat res;
	create(res, getNum(left) * getNum(right), 
				getDenom(left) * getDenom(right));

	return res;
}

Rat divide(const Rat& left, const Rat& right)
{
	Rat res;
	create(res, getNum(left) * getDenom(right), 
				getDenom(left) * getNum(right));

	return res;
}

void print(const Rat& rat)
{
	std::cout << getNum(rat) << "/" << getDenom(rat) << std::endl;
}

int main()
{
	Rat left;
	create(left, 1, 5);

	Rat right;
	create(right, 1, 3);

	//Rat res = add(left, right);
	//Rat res = substract(left, right);
	//Rat res = multiply(left, right);
	Rat res = divide(left, right);
	print(res);

	return 0;
}
