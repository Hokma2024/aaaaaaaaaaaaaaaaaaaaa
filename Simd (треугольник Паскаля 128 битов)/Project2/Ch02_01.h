#pragma once
#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>

// Структура для представления 128-битного числа через два 64-битных
struct alignas(16) XmmVal
{
public:
    union
    {
        uint64_t m_U64[2]; // 128-битное число в виде двух 64-битных
    };

    // Метод для конвертации 128-битного числа в строку
    std::string ToStringU128() const
    {
        std::ostringstream oss;

        if (m_U64[1] > 0) // Если есть старшая часть, учитываем её
            oss << m_U64[1];

        oss << std::setfill('0') << std::setw(20) << m_U64[0];

        return oss.str();
    }
};
