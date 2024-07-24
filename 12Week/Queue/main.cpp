#include <iostream>
#include <memory>

template <typename T, const unsigned S>
class MyStack
{
private:
    T arr[S];
    size_t size = 0;
public:

    void push(const T& obj)
    {
        if (size >= S)
            return;
        arr[size++] = obj;
    }
    void push(T&& obj)
    {
        if (size >= S)
            return;
        arr[size++] = std::move(obj);
    }

    const T& peek() const
    {
        if (isEmpty())
            throw std::out_of_range("Error!");

        return arr[size - 1];
    }
    void pop()
    {
        if (isEmpty())
            throw std::out_of_range("Error!");
        size--;
    }

    bool isEmpty() const
    {
        return size == 0;
    }
};

// �������� ���� (������� �� std::optional)
template <typename T>
class Optional
{
private:
    T* data = nullptr; // �������� ��� �������

    // �������� �� ������� �� ���� Optional �����
    void copyFrom(const Optional<T>& other)
    {
        if (other.data)
            data = new T(*other.data); // �������� �� �������
        else
            data = nullptr;
    }

    // ������������� �� �������
    void free()
    {
        delete data;
    }

public:
    // ����������� �� ������������
    Optional() = default;

    // ����������� � �������� �� ��������
    Optional(const T& value)
    {
        data = new T(value); // �������� �� ����������
    }

    // ����������� � ���������� ��������
    Optional(T&& value)
    {
        data = new T(std::move(value)); // ����������� �� ����������
    }

    // �������� �� ����������� (��������)
    Optional<T>& operator=(const Optional<T>& other)
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
    }

    // �������� �� ����e������ �� ����������
    const T& operator*() const
    {
        if (!data)
            throw std::runtime_error("No value stored");
        return *data;
    }
    T& operator*()
    {
        if (!data)
            throw std::runtime_error("No value stored");
        return *data;
    }

    // �������� �� ���� �������� (��������)
    void setValue(const T& value)
    {
        delete data;
        data = new T(value);
    }

    // �������� �� ���� �������� (�����������)
    void setValue(T&& value)
    {
        delete data;
        data = new T(std::move(value));
    }

    // �������� �� ����������
    void reset()
    {
        delete data;
        data = nullptr;
    }

    // �������� �� �������� ���� ��� ��������
    operator bool() const
    {
        return data != nullptr;
    }
};

// �������� ����  (������� �� std::shared_ptr)
template <typename T>
class SharedPtr
{
private:
    T* data;             // �������� ��� �������
    unsigned* pointersCount; // ����� �� �����������

    // ������������� �� �������
    void free()
    {
        if (*pointersCount == 1)
        {
            delete data;
            delete pointersCount;
        }
        else
            (*pointersCount)--;
    }

    // �������� �� ��������� �� ���� SharedPtr �����
    void copyFrom(const SharedPtr<T>& other)
    {
        data = other.data;
        pointersCount = other.pointersCount;
        (*pointersCount)++;
    }

public:
    // ����������� � �����
    SharedPtr(T* data)
    {
        this->data = data;
        pointersCount = new unsigned(1);
    }

    // ����������� �� ��������
    SharedPtr(const SharedPtr<T>& other)
    {
        copyFrom(other);
    }

    // �������� �� ����������� (��������)
    SharedPtr& operator=(const SharedPtr<T>& other)
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
    }

    // �������� �� ����e������ �� �������
    const T& operator*() const
    {
        return *data;
    }

    T& operator*()
    {
        return *data;
    }

    // ����������
    ~SharedPtr()
    {
        free();
    }
};

// �������� ���� �� ������ �� ���������
template <class T, class D>
class Pair
{
private:
    T first;  // ������� ��������
    D second; // ������� ��������

public:
    // ����������� � �������� �� ���������
    Pair(const T& first, const D& second) : first(first), second(second)
    {}

    // ����������� � ���������� ���������
    Pair(T&& first, D&& second) : first(std::move(first)), second(std::move(second))
    {}

    // ���������� �� ������� ��������
    const T& getFirst() const
    {
        return first;
    }

    // ���������� �� ������� ��������
    const D& getSecond() const
    {
        return second;
    }

    // �������� �� ������� �������� (��������)
    void setFirst(const T& first)
    {
        this->first = first;
    }

    // �������� �� ������� �������� (�����������)
    void setFirst(T&& first)
    {
        this->first = std::move(first);
    }

    // �������� �� ������� �������� (��������)
    void setSecond(const D& second)
    {
        this->second = second;
    }

    // �������� �� ������� �������� (�����������)
    void setSecond(D&& second)
    {
        this->second = std::move(second);
    }
};

// �������� ���� 
template <typename T, typename D, typename K>
class Tripple
{
private:
    Pair<Pair<T, D>, K> data; // ������, �������� �� �� ������ � ������������ ��������
};

int main()
{
    // ������ �� ���������� �� Pair
    Pair<int, char> qq(3, 'D');
    std::cout << "First: " << qq.getFirst() << ", Second: " << qq.getSecond() << std::endl;
}
