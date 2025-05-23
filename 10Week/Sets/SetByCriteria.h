#pragma once
#include "DynamicSet.h"

// ���� �� ������ � ��������� �� �����, �������� �� ��������
class SetByCriteria : private DynamicSet
{
public:
    // �����������, ����� ������������ ��������� �� ����� � ���������� �� ��������� �����
    SetByCriteria(unsigned n, bool (*incl)(unsigned n));

    // ����� �� �������� �� ��� ��������� �����
    void setInclude(bool (*incl)(unsigned n));

    // ��������� �������� �������� ������ �� ������� ���� DynamicSet
    using DynamicSet::print;
    using DynamicSet::contains;

private:
    // ����� �� ��������� �� ����������� � ���������� �� ��������� ��������
    void fillSet(bool (*criteria)(unsigned n));
};
