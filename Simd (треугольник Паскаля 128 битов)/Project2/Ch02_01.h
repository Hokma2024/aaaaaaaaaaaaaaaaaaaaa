#pragma once
#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>

// ��������� ��� ������������� 128-������� ����� ����� ��� 64-������
struct alignas(16) XmmVal
{
public:
    union
    {
        uint64_t m_U64[2]; // 128-������ ����� � ���� ���� 64-������
    };

    // ����� ��� ����������� 128-������� ����� � ������
    std::string ToStringU128() const
    {
        std::ostringstream oss;

        if (m_U64[1] > 0) // ���� ���� ������� �����, ��������� �
            oss << m_U64[1];

        oss << std::setfill('0') << std::setw(20) << m_U64[0];

        return oss.str();
    }
};
