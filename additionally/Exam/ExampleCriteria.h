#pragma once

struct ExampleCriteria
{
    bool include = false;  // �������� ���� ������� ������ �� ���� �������� ��� ���������.
    size_t size = 0;       // ������ �� ������ �� �����.
    int arr[32] = { 0 };   // ����� �� �����, ����� ��������� ��������.

    bool operator()(unsigned n) const
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == n)
            {
                return include;
            }
        }
        return !include;
    }
};
