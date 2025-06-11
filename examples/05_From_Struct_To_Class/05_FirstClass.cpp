#include <iostream>

struct Rat
{
private:
	// скрити за външния свят
	// достъпни само за функциите на структурата
	int num;
	int denom; // denom != 0

public:
	// достъпни за външния свят
	bool create(int n, int d);
	int getNum() const;
	int getDenom() const;
};

// пълното име на функцията е Rat::create
bool Rat::create(int n, int d)
{
	if (d == 0)
		return false;

	this->num = n;
	this->denom = d;

	return true;
}

// константна функция
// не променя текущия обект
int Rat::getNum() const
{
	return this->num;
}

int Rat::getDenom() const
{
	return this->denom;
}

// външна функция,
// няма достъп до член-данните на класа, които са в private частта
Rat sum(const Rat& left, const Rat& right)
{
	Rat res;

	res.create(
			left.getNum() * right.getDenom() +
			right.getNum() * left.getDenom(),
			left.getDenom() * right.getDenom()
	);

	return res;
}

void print(const Rat& rat)
{
	std::cout << rat.getNum() << "/" << rat.getDenom() << std::endl;
}

int main()
{
	Rat r;
	if (!r.create(1, 0))
	{
		std::cerr << "The denominator cannot be zero!\n";
	}

	// r.create(1, 0);
	// r е текущият обект, върху който се изпълнява функцията

	Rat r1;
	if (r.create(2, 3) && r1.create(3, 4))
	{
		Rat res = sum(r, r1);
		print(res);
	}

	return 0;
}
