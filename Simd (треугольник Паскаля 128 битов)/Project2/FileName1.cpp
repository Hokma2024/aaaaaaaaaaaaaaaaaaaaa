#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include "Ch02_01.h"
using namespace std;

// Функция сложения двух 128-битных чисел, представленных как два 64-битных числа
void AddI128(XmmVal* result, const XmmVal* a, const XmmVal* b)
{
    uint64_t low = a->m_U64[0] + b->m_U64[0];
    uint64_t carry = (low < a->m_U64[0]) ? 1 : 0; // Проверка переполнения

    result->m_U64[0] = low;
    result->m_U64[1] = a->m_U64[1] + b->m_U64[1] + carry;
}

void CalculatePascalRow(int n, vector<XmmVal>& row, const vector<XmmVal>& prevRow)
{
    row[0].m_U64[0] = 1; row[0].m_U64[1] = 0;       // Первый элемент всегда 1
    row[n - 1].m_U64[0] = 1; row[n - 1].m_U64[1] = 0; // Последний элемент всегда 1

    for (int k = 1; k < n - 1; ++k)
    {
        XmmVal tempA, tempB, result;

        tempA.m_U64[0] = prevRow[k - 1].m_U64[0];
        tempA.m_U64[1] = prevRow[k - 1].m_U64[1];

        tempB.m_U64[0] = prevRow[k].m_U64[0];
        tempB.m_U64[1] = prevRow[k].m_U64[1];

        AddI128(&result, &tempA, &tempB);

        row[k].m_U64[0] = result.m_U64[0];
        row[k].m_U64[1] = result.m_U64[1];
    }
}

void CalculatePascalTriangle(int numRows)
{
    vector<vector<XmmVal>> triangle(numRows);
    ofstream out;
    string filename = "output_triangle.txt";
    out.open(filename);

    for (int n = 1; n <= numRows; ++n)
    {
        triangle[n - 1].resize(n);
        if (n == 1)
        {
            triangle[0][0].m_U64[0] = 1;
            triangle[0][0].m_U64[1] = 0;
        }
        else
        {
            CalculatePascalRow(n, triangle[n - 1], triangle[n - 2]);
        }
    }

    for (int n = 0; n < numRows; ++n)
    {
        out << setw((numRows - n) * 2) << "";

        for (int k = 0; k <= n; ++k)
        {
            // Вывод 128-битного числа в виде строки
            out << setw(30) << triangle[n][k].ToStringU128() << " ";
        }
        out << endl;
    }

    out.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int numRows = 100;
    CalculatePascalTriangle(numRows);
    cout << "Треугольник Паскаля записан в файл output_triangle.txt" << endl;
}
