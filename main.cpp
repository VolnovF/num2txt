#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>

#include "words.h"

using digit_t = size_t;
using digits_t = std::vector<digit_t>;

int readNumber();
digits_t numberInDigits(int number);
std::string* digitsInStrings(const size_t* digits, const int size, const int number);
void printDigitsSector(const digits_t& digits, const int sector, const int radix, const Numerals& numerals, const СountableThing& thing);
void printСountableThing(const digit_t units, const СountableThing& thing);
void printUnits(const digit_t units, const Numerals& numerals, const СountableThing& thing);
void printTens(const digit_t tens, digit_t units, const Numerals& numerals, const СountableThing& thing);
void printHundreds(const digit_t hundreds, const digit_t tens, const digit_t units, const int sector, const Numerals& numerals, const СountableThing& thing);
size_t* numberInPtr(size_t& size, int number);

int main()
{
    const int inputNumber{ readNumber() };
    size_t digitsSize{ 0 };
    size_t* digits{ numberInPtr(digitsSize, inputNumber) };
    for (size_t i = 0; i < digitsSize; i++)
    {
        std::cout << digits[i];
    }
    std::cout << '\n';
    size_t wordsSize{ digitsSize + 1 };
    std::string* digitsWords{ new std::string[wordsSize] };
    digitsInStrings(digits, digitsSize, digitsWords, wordsSize, inputNumber);
    return 0;
}

int readNumber()
{
    std::cout << "Введите сумму рублей: ";
    int number;
    std::cin >> number;
    return number;
}

size_t* numberInDigitsPtr(
    size_t& size,
    int number)
{
    std::stack<digit_t> buf;
    for ( ;number != 0; number /= 10)
    {
        buf.push(static_cast<digit_t>( std::abs(number) % 10 ));
    }
    size = buf.size();
    size_t* digits = new size_t[size];
    for (size_t i = 0; i < size; i++)
    {
        digits[i] = buf.top();
        buf.pop();
    }
    return digits;
}

std::string* digitsInStrings(
    size_t* digits,
    const size_t digitsSize,
    std::string* strings,
    const size_t tringsSize,
    const int number)
{
    if ( number < 0 )
    {
        std::cout << "минус ";
    }
    else if ( number == 0 )
    {
        std::cout << "ноль рублей\n";
        return;
    }
    int radix{ static_cast<int>(digitsSize % 3) };
    int sectorsCount{ static_cast<int>((digitsSize - 1) / 3) };
    switch ( sectorsCount )
    {
    case 2: // миллионы -> сотни миллионов
        //printDigitsSector(digits, sectorsCount, radix, numeralsMale, million);
        --sectorsCount;
        radix = 0;
        [[fallthrough]]; 
    case 1: // тысячи -> сотни тысяч
        //printDigitsSector(digits, sectorsCount, radix, numeralsFemale, thousand);
        --sectorsCount;
        radix = 0;
        [[fallthrough]];
    case 0: // единицы -> сотни
        //printDigitsSector(digits, sectorsCount, radix, numeralsMale, rubel);
        radix = 0;
        [[fallthrough]];
    default:
        break;
    };
    std::cout << '\n';
}

/*
void printDigitsInText(const digits_t& digits, const int number)
{
    size_t size{ digits.size() };
    if ( number < 0 )
    {
        std::cout << "минус ";
    }
    else if ( number == 0 )
    {
        std::cout << "ноль рублей\n";
        return;
    }
    int radix{ static_cast<int>(size % 3) };
    int sectorsCount{ static_cast<int>((size - 1) / 3) };
    switch ( sectorsCount )
    {
    case 2: // миллионы -> сотни миллионов
        printDigitsSector(digits, sectorsCount, radix, numeralsMale, million);
        --sectorsCount;
        radix = 0;
        [[fallthrough]]; 
    case 1: // тысячи -> сотни тысяч
        printDigitsSector(digits, sectorsCount, radix, numeralsFemale, thousand);
        --sectorsCount;
        radix = 0;
        [[fallthrough]];
    case 0: // единицы -> сотни
        printDigitsSector(digits, sectorsCount, radix, numeralsMale, rubel);
        radix = 0;
        [[fallthrough]];
    default:
        break;
    };
    std::cout << '\n';
}

void printDigitsSector(const digits_t& digits, const int sector, const int radix, const Numerals& numerals, const СountableThing& thing)
{
    size_t size{ digits.size() };
    size_t unit{ size - static_cast<size_t>(1 + 3 * sector) };
    size_t ten{ size - static_cast<size_t>(2 + 3 * sector) };
    size_t hundred{ size - static_cast<size_t>(3 + 3 * sector) };
    switch ( radix )
    {
    case 0: // сотни
        //digit_t units{ digits[size - (1 + 3 * sector)] };
        //digit_t tens{ digits[size - (2 + 3 * sector)] };
        //digit_t hundreds{ digits[size - (3 + 3 * sector)] };
        printHundreds(digits[hundred], digits[ten], digits[unit], sector, numerals, thing);
        break;
    case 2: // десятки
        //digit_t units{ digits[size - (1 + 3 * sector)] };
        //digit_t tens{ digits[size - (2 + 3 * sector)] };
        printTens(digits[ten], digits[unit], numerals, thing);
        break;
    case 1: // единицы
        //digit_t units{ digits[size - (1 + 3 * sector)] };
        printUnits(digits[unit], numerals, thing);
        break;
    default:
        break;
    };
}

void printUnits(const size_t units, const Numerals& numerals, const СountableThing& thing)
{
    std::cout << numerals.units[ units ] << (units ? " " : "");
    printСountableThing(units, thing);
}
void printTens(const size_t tens, const size_t units, const Numerals& numerals, const СountableThing& thing)
{
    if (tens == 1)
    {
        std::cout << numerals.teens[ units ] << ' ';
        printСountableThing(0, thing);
        return;
    }
    std::cout << numerals.tens[ tens ] << (tens ? " " : "");
    printUnits(units, numerals, thing);
}
void printHundreds(const digit_t hundreds, const digit_t tens, const digit_t units, const int sector, const Numerals& numerals, const СountableThing& thing)
{
    if ((hundreds + tens + units) == 0 && (sector != 0))
    {
        return;
    }
    std::cout << numerals.hundreds[ hundreds ] << (hundreds ? " " : "");
    printTens(tens, units, numerals, thing);
}

void printСountableThing(const size_t units, const СountableThing& thing)
{
    switch ( units )
    {
    case 0:
    case 9:
    case 8:
    case 7:
    case 6:
    case 5:
        std::cout << thing.genitivePlural;
        break;
    case 4:
    case 3:
    case 2:
        std::cout << thing.genitiveSingular;
        break;
    case 1:
        std::cout << thing.nominativeSingular;
        break;
    default:
        break;
    };
    std::cout << ' ';
}
*/