#include <iostream>
#pragma warning (disable : 4996)

class Helper
{
public:
	static bool isValid(const char* str)
	{
		return str && *str;
	}

	static bool setStr(char*& dest, const char* str)
	{
		if (!isValid(str))
		{
			return false;
		}
		char* temp = nullptr;
		temp = new (std::nothrow) char[strlen(str) + 1];
		if (!temp)
			return false;
		strcpy(temp, str);
		delete[] dest;
		dest = temp;
		return true;
	}
};


class Phone
{
public:
	Phone(const char* brand, const char* model, double price) : brand(nullptr), model(nullptr), price(0.0)
	{
		try
		{
			setBrand(brand);
			setModel(model);
			setPrice(price);
		}
		catch (...)
		{
			delete[] this->brand;
			brand = nullptr;
			delete[] this->model;
			model = nullptr;
			throw;
		}
	}

	Phone(const Phone& other) : brand(nullptr), model(nullptr), price(0.0){
		try
		{
			setBrand(other.brand);
			setModel(other.model);
			setPrice(other.price);
		}
		catch (...)
		{
			delete[] this->brand;
			brand = nullptr;
			delete[] this->model;
			model = nullptr;
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
				if (!Helper::setStr(tempB, other.brand) || !Helper::setStr(tempM, other.model) || other.price <= 0.0)
				{
					throw std::invalid_argument("invalid parameters");
				}
				delete[] brand;
				delete[] model;

				brand = tempB;
				model = tempM;
				price = other.price;
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
		delete[] brand;
		delete[] model;
	}

	void setBrand(const char* newBrand)
	{
		if (!Helper::setStr(brand, newBrand))
		{
			throw std::invalid_argument("Brand is not valid");
		}
	}

	void setModel(const char* newModel)
	{
		if (!Helper::setStr(model, newModel))
		{
			throw std::invalid_argument("Model is not valid");
		}
	}

	void setPrice(double newPrice)
	{
		if (newPrice <= 0.0)
		{
			throw std::invalid_argument("Price must be more than 0");
		}
		price = newPrice;
	}

	const char* getBrand() const
	{
		return this->brand;
	}

	const char* getModel() const
	{
		return this->model;
	}

	virtual double getPrice() const
	{
		return this->price;
	}

	virtual Phone* clone() const
	{
		return new Phone(*this);
	}

private:
	char* brand;
	char* model;
	double price;


};

class Smartphone : public Phone
{
public:
	Smartphone(const char* brand, const char* model, double price, const char* os, unsigned gb) : Phone(brand, model, price),
		os(nullptr), gb(gb)
	{
		setOs(os);
	}

	Smartphone(const Smartphone& other) : Phone(other), os(nullptr), gb(other.gb)
	{
		setOs(other.os);
	}

	Smartphone& operator=(const Smartphone& other)
	{
		if (this != &other)
		{

			Phone::operator=(other);

			char* tempOs = nullptr;
			try
			{
				if (!Helper::setStr(tempOs, other.os) || other.gb <= 0)
				{
					throw std::invalid_argument("invalid smartphone parameters");
				}

				
				delete[] os;

				
				os = tempOs;
				gb = other.gb;
			}
			catch (...)
			{
				delete[] tempOs;
				throw;
			}
		}
		return *this;
	}

	virtual ~Smartphone()
	{
		delete[] os;
	}

	void setOs(const char* newOs)
	{
		if (!Helper::setStr(os, newOs))
		{
			throw std::invalid_argument("Invalid OS");
		}
	}

	void setGb(unsigned gb)
	{
		this->gb = gb;
	}

	const char* getOs() const
	{
		return os;
	}

	unsigned getGb() const
	{
		return gb;
	}

	double getPrice() const override
	{
		return Phone::getPrice() + gb;
	}

	Phone* clone() const override
	{
		return new Smartphone(*this);
	}

	

private:
	char* os;
	unsigned gb;
};

class Store
{
public:
	Store(double budget) : budget(budget), cap(8), size(0), phones(nullptr)
	{
		if (budget < 1) {
			throw std::logic_error("Budget must be more than 1.");
		}
		phones = new Phone * [cap];
		for (int i = 0; i < cap; i++)
		{
			phones[i] = nullptr;
		}
	}

	Store(const Store& other) : phones(nullptr), cap(other.cap), size(other.size), budget(other.budget)
	{
		phones = new Phone * [cap];
		size_t help = 0;

		try 
		{
			for (int i = 0; i < size; i++)
			{
				phones[i] = other.phones[i]->clone();
				++help;
			}
			for (size_t j = size; j < other.cap; j++)
			{
				phones[j] = nullptr;
			}

		}
		catch (...)
		{
			for (size_t j = 0; j < help; j++)
			{
				delete phones[j];
			}
			delete[] phones;
			throw;
		}
	}

	Store& operator=(const Store& other)
	{
		if (this == &other)
			return *this;

		Phone** newArr = nullptr;

			newArr = new Phone * [other.cap];
			size_t help = 0;

			try
			{
				for (int i = 0; i < other.size; i++)
				{
					
					newArr[i] = other.phones[i]->clone();
					help++;
				}

				for (size_t j = help; j < other.cap; j++)
				{
					newArr[j] = nullptr;
				}
			}
			catch (...) 
			{
				for (size_t i = 0; i < help; i++)
				{
					delete newArr[i];
				}
				delete[] newArr;
				throw;  
			}
		

		for (size_t i = 0; i < size; i++)
			delete phones[i];
		delete[] phones;

		phones = newArr;
		size = other.size;
		cap = other.cap;
		budget = other.budget;

		return *this;


		//Store temp(other);
		//std::swap(phones, temp.phones);
		//std::swap(size, temp.size);
		//std::swap(cap, temp.cap);
		//std::swap(budget, temp.budget);
	}

	~Store()
	{
		for (int i = 0; i < size; i++)
		{
			delete phones[i];
		}
		delete[] phones;
		phones = nullptr;
	}

	bool add(const Phone& phone)
	{
		if (budget < phone.getPrice())
			return false;

		Phone* copy = nullptr;
		try
		{
			copy = phone.clone();
		}
		catch (...)
		{

			return false;
		}

		try
		{
			if (size == cap)
			{
				resize();
			}
		}
		catch (...)
		{
			delete copy;
			return false;
		}
		phones[size++] = copy;
		budget -= phone.getPrice();
		return true;
	}



	bool sell(const char* brand, const char* model)
	{
		for (int i = 0; i < size; i++)
		{
			if (!(strcmp(brand, phones[i]->getBrand())))
			{
				if (!(strcmp(model, phones[i]->getModel())))
				{
					sellIndex(i);
					return true;
				}
			}
		}
		return false;
	}

	bool sellCheapestByBrand(const char* brand)
	{
		if (!brand || !*brand || size == 0)
			return false;

		int minIndex = -1;
		double minPrice = 0.0;

		for (int i = 0; i < size; i++)
		{
			if (strcmp(phones[i]->getBrand(), brand) == 0)
			{
				if (minIndex == -1 || phones[i]->getPrice() < minPrice)
				{
					minIndex = i;
					minPrice = phones[i]->getPrice();
				}
			}
		}

		if (minIndex == -1)
			return false;

		sellIndex(minIndex);  
		return true;
	}


	bool sellCheapestSamsung()
	{
		return sellCheapestByBrand("Samsung");
	}

private:
	Phone** phones;
	int size;
	int cap;
	double budget;

	void resize()
	{
		unsigned newCap = cap * 2;
		Phone** temp = new Phone * [newCap];
		size_t help = 0;

		try 
		{
			for (int i = 0; i < size; i++) 
			{				
				temp[i] = phones[i]->clone(); 
				help++;
			}
			for (int i = help; i < newCap; i++)
			{
				temp[i] = nullptr;
			}
		}
		catch (...)
		{
			for (size_t j = 0; j < help; j++)
				delete temp[j]; 
			delete[] temp;
			throw; 
		}

		
		for (size_t j = 0; j < size; ++j)
			delete phones[j];
		delete[] phones;

		phones = temp;
		cap = newCap;
	}

	void sellIndex(unsigned i)
	{
		budget += phones[i]->getPrice();
		delete phones[i];

		for (size_t j = i + 1; j < size; j++)
			phones[j - 1] = phones[j];

		--size;
		phones[size] = nullptr;
	}

};

class ExplodingPhone : public Phone {
public:
	ExplodingPhone(const char* brand, const char* model, double price, bool explode = false)
		: Phone(brand, model, price), explode(explode) {}

	Phone* clone() const override {
		if (explode)
			throw std::runtime_error("Boom! clone failed");
		return new ExplodingPhone(*this);
	}

private:
	bool explode;
};

int main() {
	try {
		Store store(5000);

		Phone p1("Samsung", "Galaxy A10", 300);
		Smartphone s1("Apple", "iPhone 13", 1500, "iOS", 256);
		ExplodingPhone bad("Vertu", "Expensive", 10000, true);

		std::cout << "Initial store setup done.\n";

		// добавяне на нормални телефони
		store.add(p1);
		store.add(s1);

		std::cout << "Store before adding exploding phone: " << std::endl;
		std::cout << "Budget: " << 5000 - p1.getPrice() - s1.getPrice() << std::endl;

		try {
			store.add(bad);
		}
		catch (const std::exception& e) {
			std::cout << "Caught exception: " << e.what() << std::endl;
		}

		std::cout << "Store after failed add remains unchanged.\n";

		// Copy constructor
		Store storeCopy(store);
		std::cout << "Store copied successfully.\n";

		// Проверка дали оригиналът е непроменен
		std::cout << "Original store still has Samsung Galaxy A10? "
			<< (store.sell("Samsung", "Galaxy A10") ? "false" : "true") << std::endl;

		// Assignment operator
		Store storeAssign(1000);
		storeAssign = store;
		std::cout << "Store assigned successfully.\n";

		std::cout << "Original store still has Apple iPhone 13? "
			<< (store.sell("Apple", "iPhone 13") ? "false" : "true") << std::endl;

	}
	catch (...) {
		std::cout << "Unexpected error!\n";
	}
}

//int main()
//{
//	try
//	{
//		// --- Създаваме оригинални обекти ---
//		Phone p1("Samsung", "Galaxy A10", 300);
//		Smartphone s1("Apple", "iPhone 13", 1500, "iOS", 256);
//		Store store1(5000);
//
//		store1.add(p1);
//		store1.add(s1);
//
//		// --- Copy Constructor за Phone ---
//		Phone p2 = p1;
//		std::cout << "p2 brand: " << p2.getBrand() << ", model: " << p2.getModel() << ", price: " << p2.getPrice() << "\n";
//
//		// --- Copy Constructor за Smartphone ---
//		Smartphone s2 = s1;
//		std::cout << "s2 brand: " << s2.getBrand() << ", model: " << s2.getModel()
//			<< ", OS: " << s2.getOs() << ", GB: " << s2.getGb() << ", price: " << s2.getPrice() << "\n";
//
//		// --- Copy Constructor за Store ---
//		Store store2 = store1;
//		std::cout << "store2 copied successfully. Size: " << store2.add(p1) << "\n";
//
//		// --- Operator= за Phone ---
//		Phone p3("Nokia", "3310", 50);
//		p3 = p1;
//		std::cout << "p3 brand: " << p3.getBrand() << ", model: " << p3.getModel() << ", price: " << p3.getPrice() << "\n";
//
//		// --- Operator= за Smartphone ---
//		Smartphone s3("Samsung", "S20", 800, "Android", 128);
//		s3 = s1;
//		std::cout << "s3 brand: " << s3.getBrand() << ", model: " << s3.getModel()
//			<< ", OS: " << s3.getOs() << ", GB: " << s3.getGb() << ", price: " << s3.getPrice() << "\n";
//
//		// --- Operator= за Store ---
//		Store store3(10000);
//		store3 = store1;
//		std::cout << "store3 assigned successfully.\n";
//
//		// --- Проверка: продаване на телефон в store3 ---
//		if (store3.sell("Samsung", "Galaxy A10"))
//			std::cout << "store3 sold Galaxy A10\n";
//		else
//			std::cout << "store3 could not sell Galaxy A10\n";
//
//	}
//	catch (const std::exception& e)
//	{
//		std::cout << "Exception: " << e.what() << "\n";
//	}
//	catch (...)
//	{
//		std::cout << "Unknown error\n";
//	}
//}