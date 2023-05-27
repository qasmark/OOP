#pragma once
#include <iostream>
#include <string>
#include <algorithm>

constexpr char SYMBOL_END_OF_STRING = '\0';

class CMyString
{
public:

	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки с завершающим нулевым символом
	CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из символьного массива заданной длины
	CMyString(const char* pString, size_t length);

	// конструктор копирования
	CMyString(CMyString const& other);

	// перемещающий конструктор
	CMyString(CMyString&& other) noexcept;

	// конструктор, инициализирующий строку данными из строки стандартной библиотеки C++
	CMyString(std::string const& stlString);


	// деструктор
	~CMyString();

	// длина строки без /0
	size_t GetLength() const;

	// возвращает указатель на массив символов строки
	const char* GetStringData() const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// Очистка строки
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