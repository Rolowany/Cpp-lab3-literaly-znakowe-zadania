// Testy do zadania 5. NIE MODYFIKUJ tego pliku.
#include <gtest/gtest.h>

#include "zadanie5.hpp"

using namespace zad5;

TEST(Zadanie5_CyfraHex, Cyfry) {
    EXPECT_EQ(cyfra_hex('0'), 0);
    EXPECT_EQ(cyfra_hex('9'), 9);
}
TEST(Zadanie5_CyfraHex, Litery) {
    EXPECT_EQ(cyfra_hex('a'), 10);
    EXPECT_EQ(cyfra_hex('f'), 15);
    EXPECT_EQ(cyfra_hex('A'), 10);
    EXPECT_EQ(cyfra_hex('F'), 15);
}
TEST(Zadanie5_CyfraHex, Niepoprawne) {
    EXPECT_EQ(cyfra_hex('g'), -1);
    EXPECT_EQ(cyfra_hex('G'), -1);
    EXPECT_EQ(cyfra_hex(' '), -1);
    EXPECT_EQ(cyfra_hex('/'), -1);  // tuż przed '0'
    EXPECT_EQ(cyfra_hex(':'), -1);  // tuż po '9'
    EXPECT_EQ(cyfra_hex('@'), -1);  // tuż przed 'A'
    EXPECT_EQ(cyfra_hex('`'), -1);  // tuż przed 'a'
}

TEST(Zadanie5_HexNaLiczbe, Poprawne) {
    EXPECT_EQ(hex_na_liczbe("ff"), 255);
    EXPECT_EQ(hex_na_liczbe("1A3"), 419);
    EXPECT_EQ(hex_na_liczbe("0"), 0);
    EXPECT_EQ(hex_na_liczbe("10"), 16);
    EXPECT_EQ(hex_na_liczbe("7fffffff"), 2147483647);
}
TEST(Zadanie5_HexNaLiczbe, Niepoprawne) {
    EXPECT_EQ(hex_na_liczbe("zz"), -1);
    EXPECT_EQ(hex_na_liczbe(""), -1);
    EXPECT_EQ(hex_na_liczbe("1g"), -1);
    EXPECT_EQ(hex_na_liczbe("0x1F"), -1);
}

TEST(Zadanie5_LiczbaNaCyfreHex, Poprawne) {
    EXPECT_EQ(liczba_na_cyfre_hex(0), '0');
    EXPECT_EQ(liczba_na_cyfre_hex(9), '9');
    EXPECT_EQ(liczba_na_cyfre_hex(10), 'a');
    EXPECT_EQ(liczba_na_cyfre_hex(15), 'f');
}
TEST(Zadanie5_LiczbaNaCyfreHex, PozaZakresem) {
    EXPECT_EQ(liczba_na_cyfre_hex(16), '?');
    EXPECT_EQ(liczba_na_cyfre_hex(-1), '?');
}
