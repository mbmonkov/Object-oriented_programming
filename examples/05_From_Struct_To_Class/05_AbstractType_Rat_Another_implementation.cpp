#include <iostream>

//struct Rat
//{
//	int num;
//	int denom; 
//}; 

// променяме представянето на рационалното число
typedef int Rat[2];

int getGCD(int a, int b)
{
	while (a != b)
	{
		if (a < b)
			b = b - a;
		else
			a = a - b;
	}

	return a;
}

bool create(Rat& rat, int n, int d)
{
	if (d == 0)
		d = 1;

	int gcd = getGCD(abs(n), abs(d));

	if (n * d < 0)
	{
		rat[0] = - abs(n)/gcd;
		rat[1] = abs(d)/gcd;
	}
	else
	{
		rat[0] = abs(n) / gcd;
		rat[1] = abs(d) / gcd;
	}

	//if (d == 0)
	//	return false;

	//rat.num = n;
	//rat.denom = d;

	return true;
}

int getNum(const Rat& rat)
{
	return rat[0];

	//return rat.num;
}

int getDenom(const Rat& rat)
{
	return rat[1];

	//return rat.denom;
}

void add(Rat& res, const Rat& left, const Rat& right)
{
	create(res, 
				getNum(left) * getDenom(right) + getNum(right) * getDenom(left),
				getDenom(left) * getDenom(right));
}

void substract(Rat& res, const Rat& left, const Rat& right)
{
	create(res,
		getNum(left) * getDenom(right) - getNum(right) * getDenom(left),
		getDenom(left) * getDenom(right));
}

void multiply(Rat& res, const Rat& left, const Rat& right)
{
	create(res, getNum(left) * getNum(right), 
				getDenom(left) * getDenom(right));
}

bool isZero(const Rat& rat)
{
	return getNum(rat) == 0;
}

bool divide(Rat& res, const Rat& left, const Rat& right)
{
	if (isZero(right))
		return false;

	create(res, getNum(left) * getDenom(right), 
				getDenom(left) * getNum(right));
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
	create(right, 5, 3);

	Rat res;
	// add(res, left, right);
	// substract(res, left, right);
	multiply(res, left, right);
	// divide(res, left, right);
	print(res);

	return 0;
}
