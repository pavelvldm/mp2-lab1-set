// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if ((Elem > -1) && (Elem < MaxPower))
		BitField.SetBit(Elem);
	else
		throw out_of_range("Do not exist");
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem > -1) && (Elem < MaxPower))
		BitField.ClrBit(Elem);
	else
		throw out_of_range("Do not exist");
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this != &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet Result(BitField | s.BitField);
	return Result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet Result(*this);
	Result.InsElem(Elem);
	return Result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet Result(*this);
	Result.DelElem(Elem);
	return Result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet Result(BitField & s.BitField);
	return Result;
}

TSet TSet::operator~(void) // дополнение
{
	TSet Result(~BitField);
	return Result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	cin >> s.BitField;

	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	cout << "MaxPower is " << s.MaxPower << endl;
	cout << "Characteristic vector of set is " << s.BitField;

	return ostr;
}
