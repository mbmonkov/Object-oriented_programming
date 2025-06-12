#include "MyString.h"
#include <cstring>
#include <algorithm>
#pragma warning (disable : 4996)


static unsigned roundToPowerOfTwo(unsigned v) //static! -> will be discused in the next lecture
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
    return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* data)
{
    _size = std::strlen(data);
    _allocatedDataSize = dataToAllocByStringLen(_size);
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, data);
}

MyString::MyString(size_t stringLength)
{
    _allocatedDataSize = dataToAllocByStringLen(stringLength);
    _data = new char[_allocatedDataSize];
    _size = 0;
    _data[0] = '\0';
}

MyString::MyString(const MyString& other)
{
    copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MyString::~MyString()
{
    free();
}

size_t MyString::getCapacity() const
{
    return _allocatedDataSize - 1;
}

size_t MyString::getSize() const
{
    return _size;
}

const char* MyString::c_str() const
{
    return _data;
}

MyString& MyString::operator+=(const MyString& other)
{
    if (getSize() + other.getSize() + 1 > _allocatedDataSize)
        resize(dataToAllocByStringLen(getSize() + other.getSize()));

    // we need to use strncat instead of strcat, because strcat will not work for str += str 
    // (the terminating zero of str will be destroyed by the first char)
    std::strncat(_data, other._data, other.getSize());

    _size = getSize() + other.getSize();
    return *this;
}

char& MyString::operator[](size_t index)
{
    return _data[index]; // no security check!!
}

const char& MyString::operator[](size_t index) const
{
    return _data[index]; // no security check!!
}

std::ostream& operator<<(std::ostream& os, const MyString& obj)
{
    return os << obj._data;
}

std::istream& operator>>(std::istream& is, MyString& ref)
{
    char buff[1024];
    is >> buff;
    size_t buffStringSize = std::strlen(buff);

    if (buffStringSize > ref.getCapacity())
        ref.resize(dataToAllocByStringLen(buffStringSize));

    strcpy(ref._data, buff);
    ref._size = buffStringSize;
    return is;
}

void MyString::resize(unsigned newAllocatedDataSize)
{
    char* newData = new char[newAllocatedDataSize + 1];
    std::strcpy(newData, _data);
    delete[] _data;
    _data = newData;
    _allocatedDataSize = newAllocatedDataSize;
}

void MyString::free()
{
    delete[] _data;
}

void MyString::copyFrom(const MyString& other)
{
    _allocatedDataSize = other._allocatedDataSize;
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, other._data);
    _size = other._size;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
    MyString result(lhs.getSize() + rhs.getSize());
    result += lhs; // no resize is needed
    result += rhs;
    return result;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}


#include "NVector.h"

NVector::NVector(size_t n) : size(n)
{
	data = new int[n];

	for (int i = 0; i < n; i++)
		data[i] = 0;
}

NVector::NVector(const NVector& other)
{
	copyFrom(other);
}

NVector& NVector::operator=(const NVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
NVector::~NVector()
{
	free();
}

void NVector::copyFrom(const NVector& other)
{
	size = other.size;
	data = new int[size];

	for (int i = 0; i < size; i++)
		data[i] = other.data[i];
}
void NVector::free()
{
	delete[] data;
	size = 0;
}



//v += v1;
NVector& NVector::operator+=(const NVector& other)
{
	if (size != other.size)
		throw "The vectors should have the same size!";

	for (int i = 0; i < size; i++)
		data[i] += other.data[i];

	return *this;
}

NVector& NVector::operator-=(const NVector& other)
{
	if (size != other.size)
		throw "The vectors should have the same size!";

	for (int i = 0; i < size; i++)
		data[i] -= other.data[i];

	return *this;
}

NVector operator+(const NVector& lhs, const NVector& rhs)
{
	NVector lhsCopy(lhs);
	lhsCopy += rhs;

	return lhsCopy;
}

NVector operator-(const NVector& lhs, const NVector& rhs)
{
	NVector lhsCopy(lhs);
	lhsCopy -= rhs;

	return lhsCopy;
}

int& NVector::operator[](size_t index)
{
	if (index >= size)
		throw "Invalid index";

	return data[index];
}

int NVector::operator[](size_t index) const
{
	if (index >= size)
		throw "Invalid index";

	return data[index];
}

size_t NVector::operator~() const
{
	return size;
}

std::ostream& operator<<(std::ostream& os, const NVector& v)
{
	os << "[ ";
	for (int i = 0; i < v.size; i++)
		os << v[i] << " ";
	os << " ]";

	return os;
}

std::istream& operator>>(std::istream& is, NVector& v)
{
	for (int i = 0; i < v.size; i++)
		is >> v[i];

	return is;
}

bool operator||(const NVector& lhs, const NVector& rhs)
{
	if (~lhs != ~rhs) {
		throw "The vectors should have the same size!";
	}

	double ratio = 0.0;
	bool ratioSet = false;

	for (size_t i = 0; i < ~lhs; ++i)
	{
		// Skip if both components are zero
		if (lhs[i] == 0 && rhs[i] == 0)
		{
			continue;
		}
		// If one component is zero but the other is not, vectors are not parallel
		if (lhs[i] == 0 || rhs[i] == 0)
		{
			return false;
		}

		// Calculate the ratio of the current components
		double currentRatio = lhs[i] / rhs[i];
		// If the ratio is not set, set it. Otherwise, compare it with the current ratio
		if (!ratioSet)
		{
			ratio = currentRatio;
			ratioSet = true;
		}
		else if (std::abs(ratio - currentRatio) > 1e-6)
		{ // Use a small epsilon for floating point comparison
			// If the ratios are different, vectors are not parallel
			return false;
		}
	}
	return true;
}

NVector& NVector::operator*=(size_t scalar)
{
	for (int i = 0; i < size; i++)
		data[i] *= scalar;

	return *this;
}

NVector operator*(const NVector& lhs, size_t scalar)
{
	NVector copy(lhs);
	copy *= scalar;
	return copy;
}
NVector operator*(size_t scalar, const NVector& lhs)
{
	return lhs * scalar;
}
size_t operator%(const NVector& lhs, const NVector& rhs)
{
	if (~lhs != ~rhs)
		throw "The vectors should have the same size!";

	size_t res = 0;
	for (int i = 0; i < ~lhs; i++)
		res += lhs[i] * rhs[i];

	return res;
}

bool operator|=(const NVector& lhs, const NVector& rhs)
{
	return  lhs % rhs == 0; //the size check is done by %
}
