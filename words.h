#ifndef WORDS_H
#define WORDS_H

#include <array>
#include <string>

const std::string minus{ "минус" };

struct СountableThing
{
    std::string nominativeSingular; // Именительный падеж единственного числа
    std::string genitiveSingular;   // Родительный падеж единственного числа
    std::string genitivePlural;     // Родительный падеж множественного числа
};
const СountableThing rubel
{
    "рубль"  ,
    "рубля"  ,
    "рублей"
};
const СountableThing thousand
{
    "тысяча"  ,
    "тысячи"  ,
    "тысяч"
};
const СountableThing million
{
    "миллион"   ,
    "миллиона"  ,
    "миллионов"
};

struct Numerals
{
    std::array<std::string, 10> units;
    std::array<std::string, 10> tens;     // первые два элемента не используются, на их месте пустые строки
    std::array<std::string, 10> teens;    // числа от 10 до 19 включительно
    std::array<std::string, 10> hundreds; // первый элемент - пустая строка как в tens
};
const Numerals numeralsMale // числа мужского рода
{
    {
        "ноль"  ,
        "один"  ,
        "два"   ,
        "три"   ,
        "четыре", 
        "пять"  ,
        "шесть" ,
        "семь"  ,
        "восемь",
        "девять"
    },
    {
        ""           , // 0 - значит десятков нет
        ""           , // 1 - десяток один, нужные слова в teens
        "двадцать"   ,
        "тридцать"   ,
        "сорок"      ,
        "пятдесят"   ,
        "шестьдесят" ,
        "семьдесят"  ,
        "восемьдесят",
        "девяносто"
    },
    {
        "десять"        ,
        "одиннадцать"   ,
        "двенадцать"    ,
        "тринадцать"    ,
        "четырнадцать"  ,
        "пятнадцать"    ,
        "шестнадцать"   ,
        "семнадцать"    ,
        "восемнадцать"  ,
        "девятнадцать"
    },
    {
        ""         , // 0 - значит сотен нет
        "сто"      ,
        "двести"   ,
        "тристо"   ,
        "четыресто", 
        "пятьсот"  ,
        "шестьсот" ,
        "семьсот"  ,
        "восемьсот",
        "девятьсот"
    }
};
const Numerals numeralsFemale // числа женского рода
{
    {
        ""   ,
        "одна"  ,
        "две"   ,
        "три"   ,
        "четыре", 
        "пять"  ,
        "шесть" ,
        "семь"  ,
        "восемь",
        "девять"
    },
    {
        ""           , // 0 - значит десятков нет
        ""           , // 1 - десяток один, нужные слова в teens
        "двадцать"   ,
        "тридцать"   ,
        "сорок"      ,
        "пятдесят"   ,
        "шестьдесят" ,
        "семьдесят"  ,
        "восемьдесят",
        "девяносто"
    },
    {
        "десять"        ,
        "одиннадцать"   ,
        "двенадцать"    ,
        "тринадцать"    ,
        "четырнадцать"  ,
        "пятнадцать"    ,
        "шестнадцать"   ,
        "семнадцать"    ,
        "восемнадцать"  ,
        "девятнадцать"
    },
    {
        ""         , // 0 - значит сотен нет
        "сто"      ,
        "двести"   ,
        "тристо"   ,
        "четыресто", 
        "пятьсот"  ,
        "шестьсот" ,
        "семьсот"  ,
        "восемьсот",
        "девятьсот"
    }
};


/*
const std::array<std::string, 10> unitsWord
{
    "ноль"  ,
    "один"  ,
    "два"   ,
    "три"   ,
    "четыре", 
    "пять"  ,
    "шесть" ,
    "семь"  ,
    "восемь",
    "девять"
};

const std::array<std::string, 10> tensWord
{
    ""           , // 0 - значит десятков нет
    ""           , // 1 - десяток один, нужные слова в teensWord
    "двадцать"   ,
    "тридцать"   ,
    "сорок"      ,
    "пятдесят"   ,
    "шестьдесят" ,
    "семьдесят"  ,
    "восемьдесят",
    "девяносто"
};

const std::array<std::string, 10> teensWord
{
    "десять",
    "одиннадцать",
    "двенадцать",
    "тринадцать",
    "четырнадцать",
    "пятнадцать",
    "шестнадцать",
    "семнадцать",
    "восемнадцать",
    "девятнадцать"
};
*/

#endif