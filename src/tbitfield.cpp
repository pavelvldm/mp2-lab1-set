// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

const int sizeTELEM = sizeof(TELEM) * 8;		// размер TELEM в битах 
const int pow32 = 5;							// степень, в которую нужно возвести 2, чтобы получить размер TELEM в битах

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = ((BitLen - 1) >> pow32) + 1;
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else 
		throw out_of_range("Wrong value of len");
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;

	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	if (pMem != nullptr)
		delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > -1) && (n < BitLen))
		return n >> pow32;
	else 
		throw out_of_range("Wrong value of n");
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n > -1) && (n < BitLen))
		return 1 << (n - ((n >> pow32) << pow32));
	else 
		throw out_of_range("Wrong value of n");
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	else 
		throw out_of_range("Wrong value of n");
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
	else 
		throw out_of_range("Wrong value of n");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int Result;
	if ((n > -1) && (n < BitLen))
	{
		Result = pMem[GetMemIndex(n)] & GetMemMask(n);
		if (Result) 
			return 1;
		else 
			return 0;
	}
	else 
		throw out_of_range("Wrong value of n");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;

		delete[] pMem;
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) 
		return 0;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i]) 
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf) 
		return 0;
	else 
		return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen > bf.BitLen)
	{
		TBitField Result(BitLen);

		for (int i = 0; i < bf.MemLen; i++)
			Result.pMem[i] = pMem[i] | bf.pMem[i];

		for (int i = bf.MemLen; i < MemLen; i++)
			Result.pMem[i] = pMem[i];

		return Result;
	}
	else
	{
		TBitField Result(bf.BitLen);

		for (int i = 0; i < MemLen; i++)
			Result.pMem[i] = pMem[i] | bf.pMem[i];

		for (int i = MemLen; i < bf.MemLen; i++)
			Result.pMem[i] = bf.pMem[i];

		return Result;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen > bf.BitLen)
	{
		TBitField Result(BitLen);

		for (int i = 0; i < bf.MemLen; i++)
			Result.pMem[i] = pMem[i] & bf.pMem[i];

		for (int i = bf.MemLen; i < MemLen; i++)
			Result.pMem[i] = 0;

		return Result;
	}
	else
	{
		TBitField Result(bf.BitLen);

		for (int i = 0; i < MemLen; i++)
			Result.pMem[i] = pMem[i] & bf.pMem[i];

		for (int i = MemLen; i < bf.MemLen; i++)
			Result.pMem[i] = 0;

		return Result;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField Result(*this);

	for (int i = 0; i < BitLen; i++)
		if (GetBit(i)) 
			Result.ClrBit(i);
		else 
			Result.SetBit(i);

	return Result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int Value;

	for (int i = 0; i < bf.BitLen; i++)
	{
		cin >> Value;
		if (Value == 1)
			bf.SetBit(i);
		else if (Value == 0)
			bf.ClrBit(i);
		else throw out_of_range("Wrong value");
	}

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		cout << bf.GetBit(i);

	return ostr;
}
