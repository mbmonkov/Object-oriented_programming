#pragma once 
#include "Animal.h"
#include <stddef.h>  // ������� ������������ �� ��������� �� ���������� ������ ���� size_t

class Farm
{
	Animal** data;  // ������ �� ��������� ��� ������ �� ��� Animal (��� �������� ����������)
	size_t size;  // �������� ���� ������� � �������
	size_t capacity;  // ������������ ���� �������, ����� ������� ���� �� ���������, ����� �� �� ������ ����������

	void free();  // ����� �� ������������� �� ��������� ���������� �����
	void copyFrom(const Farm& other);  // ����� �� �������� �� ����� �� ���� ����� Farm
	void moveFrom(Farm&& other);  // ����� �� ����������� �� ����� �� ���� ����� Farm 

	void resize();  // ����� �� ����������� �� ���������� �� ������ �� �������

public:
	Farm();  // ����������� �� ������������
	~Farm();  // ����������

	Farm(const Farm& other);  // ����������� �� ��������
	Farm& operator=(const Farm& other);  // �������� �� ����������� ���� ��������

	Farm(Farm&& other) noexcept;  // ����������� �� �����������
	Farm& operator=(Farm&& other) noexcept;  // �������� �� ����������� ���� �����������

	void addAnimal(AnimalType type);  // ����� �� �������� �� ���� ������� �� ����� ���
	void makeSound() const;  // ����� �� ���������� �� ������� �� ������ ������� ��� �������
	AnimalType getType(size_t idx) const;  // ����� �� ���������� �� ���� �� ��������� �� ����� ������
};
