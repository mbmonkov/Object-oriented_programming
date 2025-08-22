#include <iostream>
#include <stdexcept>
#pragma warning (disable:4996)

class StringHelper
{
public:
	static bool isStrValid(const char* str)
	{
		return str && *str;
	}

	static bool setStr(char*& dest, const char* str)
	{
		if (!(isStrValid(str)))
		{
			return false;
		}
		char* temp = new (std::nothrow) char[strlen(str) + 1];
		delete[] dest;
		dest = strcpy(temp, str);
		return true;
	}
};

class Phone
{
public:
	Phone(const char* brand, const char* model, double price) : _brand(nullptr), _model(nullptr), _price(price)
	{
		if (price < 0 || !StringHelper::isStrValid(brand) || !StringHelper::isStrValid(model))
		{
			throw std::invalid_argument("Invalid arguments for Phone");
		}
		try
		{
			if (!StringHelper::setStr(_brand, brand) || !StringHelper::setStr(_model,model))
			{
				throw std::exception();
			}
			_price = price;
		}
		catch (...)
		{
			delete[] _brand;
			_brand = nullptr;
			delete[] _model;
			_model = nullptr;
			throw;
		}
	}

	Phone(const Phone& other): _brand(nullptr), _model(nullptr), _price(other._price)
	{
		if (!StringHelper::isStrValid(other._brand) || !StringHelper::isStrValid(other._model))
		{
			throw std::invalid_argument("Invalid arguments");
		}
		try
		{
			if (!StringHelper::setStr(_brand, other._brand) || !StringHelper::setStr(_model, other._model))
			{
				throw std::exception();
			}

		}
		catch (...)
		{
			delete[] _brand;
			delete[] _model;
			throw;
		}
	}

	Phone& operator=(const Phone& other)
	{
		if (this != &other)
		{
			char* tempB = nullptr;
			char* tempM = nullptr;
			try 
			{
				if (!StringHelper::setStr(tempB, other._brand) || !StringHelper::setStr(tempM, other._model))
				{
					throw std::exception();
				}
				delete[] _brand;
				delete[] _model;

				_brand = tempB;
				_model = tempM;
				_price = other._price;
			}
			catch (...)
			{
				delete[] tempM;
				delete[] tempB;
				throw;
			}

		}
		return *this;
	}

	virtual ~Phone()
	{
		delete[] _brand;
		delete[] _model;
		_brand = nullptr;
		_model = nullptr;
	}

	virtual Phone* clone() const
	{
		return new Phone(*this);
	}

	const char* getBrand() const
	{
		return _brand;
	}

	const char* getModel() const
	{
		return _model;
	}

	virtual double getPrice() const
	{
		return _price;
	}

	bool setPrice(double price)
	{
		if (price >= 0.0)
		{
			_price = price;
			return true;
		}
		return false;
	}

private:
	char* _brand;
	char* _model;
	double _price;
};

class Smartphone : public Phone
{
public:
	Smartphone(const char* brand, const char* model, double price, const char* os, unsigned gb)
		: Phone(brand, model, price),_os(nullptr), _gb(gb)
	{
		if (!StringHelper::isStrValid(os))
		{
			throw std::invalid_argument("Invalid argumenst");
		}
		if (!StringHelper::setStr(_os, os))
		{
			throw std::invalid_argument("Invalid argumenst(OS)");
		}
	}

	Smartphone(const Smartphone& other) : Phone(other), _gb(other._gb), _os(nullptr)
	{
		if (!StringHelper::isStrValid(other._os) || !StringHelper::setStr(_os, other._os))
		{
			throw std::invalid_argument("Invalid argumnets");
		}
	}

	Smartphone& operator=(const Smartphone& other)
	{
		if (this != &other)
		{
			Phone::operator=(other);
			char* temp = nullptr;
	
			if (!StringHelper::setStr(temp, other._os))
			{
				throw std::invalid_argument("invalid arguments");
			}
			

			delete[] _os;
			_os = temp;
			_gb = other._gb;
		}
		return *this;
	}


	virtual ~Smartphone() override
	{
		delete[] _os;
		_os = nullptr;
	}

	virtual Smartphone* clone() const override
	{
		return new Smartphone(*this);
	}

	const char* getOs() const
	{
		return _os;
	}

	unsigned getMemory() const
	{
		return _gb;
	}

	double getPrice() const override
	{
		return Phone::getPrice() + _gb;
	}

private:
	char* _os;
	unsigned _gb;
};

class Store
{
public:
	Store(double budget) : budget(budget), capacity(8), size(0)
	{
		if (budget < 1) {
			throw std::logic_error("Budget must be more than 1.");
		}
		arr = new Phone * [capacity];
		for (int i = 0; i < capacity; i++)
		{
			arr[i] = nullptr;
		}
	}

	Store(const Store& other) : budget(other.budget), capacity(other.capacity), size(other.size) {
		arr = new Phone * [capacity];
		for (unsigned i = 0; i < size; i++) {
			arr[i] = other.arr[i]->clone();
		}
	}

	Store& operator=(const Store& other) {
		if (this != &other) {
			Store temp(other);
			swap(temp);
		}
		return *this;
	}

	bool add(const Phone& phone)
	{
		if (budget < phone.getPrice())
			return false;
		if (size == capacity)
		{
			resize();
		}

		Phone* copy = nullptr;
		try 
		{
			copy = phone.clone();  
		}
		catch (...) 
		{
			return false;         
		}

		arr[size++] = copy;
		budget -= phone.getPrice();
		return true;
	}


	bool sell(const char* brand, const char* model)
	{
		for (int i = 0; i < size; i++)
		{
			if (!(strcmp(brand, arr[i]->getBrand())))
			{
				if (!(strcmp(model, arr[i]->getModel())))
				{
					sellIndex(i);
					return true;
				}
			}
		}
		return false;
	}

	~Store()
	{
		for (int i = 0; i < size; i++)
		{
			delete arr[i];
		}
		delete[] arr;
		arr = nullptr;
	}


	bool sellCheapestByBrand(const char* brand)
	{
		if (!brand || !*brand || size == 0)
			return false;

		int minIndex = -1;
		double minPrice = -1.0;

		for (int i = 0; i < size; i++)
		{
			if (strcmp(arr[i]->getBrand(), brand) == 0)
			{
				if (minPrice == -1.0)
				{
					minPrice = arr[i]->getPrice();
				}
				if (minPrice > arr[i]->getPrice())
				{
					minPrice = arr[i]->getPrice();
					minIndex = i;

				}
			}
		}

		if (minIndex == -1)
			return false;

		budget += arr[minIndex]->getPrice();
		delete arr[minIndex];

		for (int i = minIndex; i < size - 1; i++)
			arr[i] = arr[i + 1];

		size--;
		return true;
	}

	bool sellCheapestSamsung()
	{
		return sellCheapestByBrand("Samsung");
	}


private:
	Phone** arr;
	unsigned capacity;
	unsigned size;
	double budget;

	void sellIndex(unsigned i)
	{
		budget += arr[i]->getPrice();
		delete arr[i];
		arr[i] = nullptr;
		for (int j = i + 1; j < size; j++)
		{
			arr[j - 1] = arr[j];
		}
		--size;
	}

	void resize()
	{
		int newCap = capacity * 1.6;
		Phone** temp = new Phone * [newCap];
		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
		capacity = newCap;
	}

	void swap(Store& other) noexcept {
		std::swap(arr, other.arr);
		std::swap(capacity, other.capacity);
		std::swap(size, other.size);
		std::swap(budget, other.budget);
	}
};

int main()
{
	try
	{
		Store store(7000);   

		Phone p1("Samsung", "Galaxy A10", 300);
		Phone p2("Samsung", "Galaxy S20", 800);
		Phone p3("Apple", "iPhone 12", 1200);
		Smartphone s1("Samsung", "Galaxy S21", 1000, "Android", 128);
		Smartphone s2("Apple", "iPhone 13", 1500, "iOS", 256);

		std::cout << (store.add(p1) ? 1 : 0);
		std::cout << (store.add(p2) ? 1 : 0);
		std::cout << (store.add(p3) ? 1 : 0);
		std::cout << (store.add(s1) ? 1 : 0);
		std::cout << std::endl;
		std::cout << (store.add(s2) ? 1 : 0);
		std::cout << std::endl;

		try {
			Phone tooExpensive("V", "S", 10000);
			std::cout << (store.add(tooExpensive) ? 1 : 0);
		}
		catch (const std::exception& e) {
			std::cout << "Exception when creating Vertu: " << e.what() << "\n";
		}

		if (store.sell("Samsung", "Galaxy A10"))
			std::cout << "true";
		else
			std::cout << 0;

		std::cout << std::endl;

		if (store.sellCheapestSamsung())
			std::cout << "true";
		else
			std::cout << "false";
	}
	catch (...)
	{
		std::cout << "error";
	}
}
