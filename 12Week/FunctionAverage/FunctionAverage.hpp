#pragma once

// ���������� �� �������� ���� IntFunctionAverage, ����� ������ ��� ���� �������
template<class FunctionOne, class FunctionTwo>
class IntFunctionAverage
{
private:
    FunctionOne first;  // ����-���������� �� ������� ������� ��� ������������ ����� �� ��� FunctionOne
    FunctionTwo second; // ����-���������� �� ������� ������� ��� ������������ ����� �� ��� FunctionTwo

public:
    // ����������� �� �����, ������������ ������� � ������� �������
    IntFunctionAverage(const FunctionOne& fOne, const FunctionTwo& fTwo) : first(fOne),  second(fTwo) {}

    // ����� �� ����������� �� �������� �������� �� ����������� �� ����� �������
    double average(int x) const
    {
        return (first(x) + second(x)) / 2.0; // ��������� �������� �������� �� ����������� �� first � second
    }
};
