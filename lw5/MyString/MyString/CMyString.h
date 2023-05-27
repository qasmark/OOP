#pragma once
#include <iostream>
#include <string>
#include <algorithm>

constexpr char SYMBOL_END_OF_STRING = '\0';

class CMyString
{
public:

	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������ � ����������� ������� ��������
	CMyString(const char* pString);

	// �����������, ���������������� ������ ������� �� ����������� ������� �������� �����
	CMyString(const char* pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const& other);

	// ������������ �����������
	CMyString(CMyString&& other) noexcept;

	// �����������, ���������������� ������ ������� �� ������ ����������� ���������� C++
	CMyString(std::string const& stlString);


	// ����������
	~CMyString();

	// ����� ������ ��� /0
	size_t GetLength() const;

	// ���������� ��������� �� ������ �������� ������
	const char* GetStringData() const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// ������� ������
	void Clear();


	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other) noexcept;
	CMyString& operator+=(CMyString const& other);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	friend std::istream& operator>>(std::istream& stream, CMyString& myString);

private:
	char* m_data;
	size_t m_length;
};

CMyString const operator+(CMyString const& myString1, CMyString const& myString2);

bool operator==(CMyString const& myString1, CMyString const& myString2);
bool operator!=(CMyString const& myString1, CMyString const& myString2);
bool operator>(CMyString const& myString1, CMyString const& myString2);
bool operator>=(CMyString const& myString1, CMyString const& myString2);
bool operator<(CMyString const& myString1, CMyString const& myString2);
bool operator<=(CMyString const& myString1, CMyString const& myString2);

std::ostream& operator<<(std::ostream& stream, CMyString const& myString);
std::istream& operator>>(std::istream& stream, CMyString& myString);