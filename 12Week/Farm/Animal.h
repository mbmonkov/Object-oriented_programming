#pragma once 

// ��������� enum ���� AnimalType � ��� ���������: Cat, Dog � Cow
enum class AnimalType
{
	Cat,  
	Dog,  
	Cow  
};

// ���������� ���� Animal
class Animal
{
public:
	// ����� ��������� �����
	virtual void makeNoise() const = 0;

	// ��������� ����������
	virtual ~Animal() = default;

	// ����� ��������� �����
	virtual AnimalType getType() const = 0;

	// ����� ��������� �����
	virtual Animal* clone() const = 0;
};
