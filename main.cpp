#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>

#include "words.h"

using digit_t = size_t;
using stringDigits_t = const std::string**;

int readNumber();
stringDigits_t digitsInStringsDigits(
        const size_t* digits,
        const size_t digitsSize,
        size_t& wordsSize,
        const int number);
void setStringsSector(
        const size_t* digits,
        const size_t digitsSize,
        const int sector,
        const int radix,
        stringDigits_t words,
        size_t wordsSize,
        const Numerals& numerals,
        const СountableThing& thing);
void setСountableThing(
        const size_t units,
        stringDigits_t words,
        const size_t wordIndex,
        const СountableThing& thing);
void setStringUnits(
        const size_t units,
        stringDigits_t words,
        const size_t wordIndex,
        const Numerals& numerals,
        const СountableThing& thing);
void setStringTens(
        const size_t tens,
        const size_t units,
        stringDigits_t words,
        const size_t wordIndex,
        const Numerals& numerals,
        const СountableThing& thing);
void setStringHundreds(
        const digit_t hundreds,
        const digit_t tens,
        const digit_t units,
        const int sector,
        stringDigits_t words,
        const size_t wordIndex,
        const Numerals& numerals,
        const СountableThing& thing);
size_t* numberInDigitsPtr(
        size_t& size,
        int number);
void printStringsDigits(
        stringDigits_t words,
        size_t size);

int main()
{
    const int inputNumber{ readNumber() };
    size_t digitsSize{ 0 };
    size_t* digits{
        numberInDigitsPtr(digitsSize, inputNumber)
    };
    std::cout << '\n';
    size_t wordsSize{ 0 };
    stringDigits_t digitsWords{ 
        digitsInStringsDigits(
            digits, digitsSize,
            wordsSize, inputNumber)
    };
    printStringsDigits(
        digitsWords,
        wordsSize);
    delete[] digits;
    delete[] digitsWords;
    return 0;
}

void printStringsDigits(
        stringDigits_t words,
        size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (words[i])
        {
        std::cout << *words[i] << ' ';
        }
    }
    std::cout << '\n';
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
    if (number == 0)
    {
        size = 1;
        return nullptr;
    }
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

stringDigits_t digitsInStringsDigits(
        const size_t* digits,
        const size_t digitsSize,
        size_t& wordsSize,
        const int number)
{
    int radix{ static_cast<int>(digitsSize % 3) };
    int sectorsCount{ static_cast<int>((digitsSize - 1) / 3) };
    wordsSize = digitsSize + sectorsCount + 1;
    bool negative{ number < 0 };
    if ( negative )
    {
        wordsSize++;
    }

    stringDigits_t words{ new const std::string*[wordsSize] };
    /*for (size_t i = 0; i < wordsSize; i++)
    {
        words[i] = nullptr;
    }*/
    
    if ( number == 0 )
    {
        words[0] = &numeralsMale.units[0];
        words[1] = &rubel.genitivePlural;
        return words;
    }
    if ( negative )
    {
        words[0] = &minus;
    }
    switch ( sectorsCount )
    {
    case 2: // миллионы -> сотни миллионов
        setStringsSector(
            digits, digitsSize,
            sectorsCount, radix,
            words, wordsSize,
            numeralsMale, million);
        --sectorsCount;
        radix = 0;
        [[fallthrough]]; 
    case 1: // тысячи -> сотни тысяч
        setStringsSector(
            digits, digitsSize,
            sectorsCount, radix,
            words, wordsSize,
            numeralsFemale, thousand);
        --sectorsCount;
        radix = 0;
        [[fallthrough]];
    case 0: // единицы -> сотни
        setStringsSector(
            digits, digitsSize,
            sectorsCount, radix,
            words, wordsSize,
            numeralsMale, rubel);
        radix = 0;
        [[fallthrough]];
    default:
        break;
    };
    return words;
}

void setStringsSector(
        const size_t* digits,
        const size_t digitsSize,
        const int sector,
        const int radix,
        stringDigits_t words,
        size_t wordsSize,
        const Numerals& numerals,
        const СountableThing& thing)
{
    size_t unit{ digitsSize - static_cast<size_t>(1 + 3 * sector) };
    size_t ten{ digitsSize - static_cast<size_t>(2 + 3 * sector) };
    size_t hundred{ digitsSize - static_cast<size_t>(3 + 3 * sector) };
    size_t wordIndex;
    switch ( radix )
    {
    case 0: // сотни
        wordIndex = wordsSize - static_cast<size_t>(4 + 4 * sector);
        setStringHundreds(
            digits[hundred], digits[ten], digits[unit], sector,
            words, wordIndex,
            numerals, thing);
        break;
    case 2: // десятки
        wordIndex = wordsSize - static_cast<size_t>(3 + 4 * sector);
        setStringTens(
            digits[ten], digits[unit],
            words, wordIndex,
            numerals, thing);
        break;
    case 1: // единицы
        wordIndex = wordsSize - static_cast<size_t>(2 + 4 * sector);
        setStringUnits(
            digits[unit],
            words, wordIndex,
            numerals, thing);
        break;
    default:
        break;
    };
}

void setStringUnits(
        const size_t units,
        stringDigits_t words,
        const size_t wordIndex,
        const Numerals& numerals,
        const СountableThing& thing)
{
    words[wordIndex] = (units != 0 ? &numerals.units[ units ] : nullptr);
    setСountableThing(
        units,
        words, wordIndex + 1,
        thing);
}
void setStringTens(
        const size_t tens,
        const size_t units,
        stringDigits_t words,
        const size_t wordIndex,
        const Numerals& numerals,
        const СountableThing& thing)
{
    if (tens == 1)
    {
        words[wordIndex] = &numerals.teens[ tens ];
        words[wordIndex + 1] = nullptr;
        setСountableThing(
            0,
            words, wordIndex + 2,
            thing);
        return;
    }
    words[wordIndex] = (tens != 0 ? &numerals.tens[ tens ] : nullptr);
    setStringUnits(
        units, 
        words, wordIndex + 1,
        numerals, thing);
}
void setStringHundreds(
        const digit_t hundreds,
        const digit_t tens,
        const digit_t units,
        const int sector,
        stringDigits_t words,
        const size_t wordIndex,
        const Numerals& numerals,
        const СountableThing& thing)
{
    if ((hundreds + tens + units) == 0 && (sector != 0))
    {
        for (size_t i = 0; i < 4; i++)
        {
            words[wordIndex + i] = nullptr;
        }
        return;
    }
    words[wordIndex] = (hundreds != 0 ? &numerals.hundreds[ hundreds ] : nullptr);
    setStringTens(
        tens, units,
        words, wordIndex + 1,
        numerals, thing);
}

void setСountableThing(
        const size_t units,
        stringDigits_t words,
        const size_t wordIndex,
        const СountableThing& thing)
{
    switch ( units )
    {
    case 0:
    case 9:
    case 8:
    case 7:
    case 6:
    case 5:
        words[wordIndex] = &thing.genitivePlural;
        break;
    case 4:
    case 3:
    case 2:
        words[wordIndex] = &thing.genitiveSingular;
        break;
    case 1:
        words[wordIndex] = &thing.nominativeSingular;
        break;
    default:
        break;
    };
}
