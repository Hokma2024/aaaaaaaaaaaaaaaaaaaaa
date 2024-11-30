#include <immintrin.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include "Ch02_01.h"
using namespace std;

void CalculatePascalRow(int n, vector<XmmVal>& row, const vector<XmmVal>& prevRow)
{
    row[0].m_I64[0] = 1;  // Первый элемент всегда 1
    row[n - 1].m_I64[0] = 1;  // Последний элемент всегда 1

    for (int k = 1; k < n - 1; ++k)
    {
        XmmVal tempA, tempB, result;

        tempA.m_I64[0] = prevRow[k - 1].m_I64[0];
        tempB.m_I64[0] = prevRow[k].m_I64[0];

        AddI64_Iavx(&result, &tempA, &tempB);

        row[k].m_I64[0] = result.m_I64[0];  // Используем результат сложения
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
            triangle[0][0].m_I64[0] = 1;  // Первая строка
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
            out << setw(8) << triangle[n][k].m_I64[0] << " ";
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