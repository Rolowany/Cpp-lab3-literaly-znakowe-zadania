// Testy do zadania 4. NIE MODYFIKUJ tego pliku.
#include <gtest/gtest.h>

#include "zadanie4.hpp"

using namespace zad4;

TEST(Zadanie4_IleCyfr, Przyklady) {
    EXPECT_EQ(ile_cyfr("Ala ma 2 koty, 3 psy!"), 2);
    EXPECT_EQ(ile_cyfr("2026"), 4);
    EXPECT_EQ(ile_cyfr(""), 0);
}
TEST(Zadanie4_IleCyfr, SasiedzCyfrWTabeli) {
    // '/' jest tuż przed '0', a ':' tuż po '9'
    EXPECT_EQ(ile_cyfr("/0:9/"), 2);
}

TEST(Zadanie4_IleLiter, Przyklady) {
    EXPECT_EQ(ile_liter("Ala ma 2 koty, 3 psy!"), 12);
    EXPECT_EQ(ile_liter("123 !?"), 0);
    EXPECT_EQ(ile_liter(""), 0);
}
TEST(Zadanie4_IleLiter, Granice) {
    EXPECT_EQ(ile_liter("azAZ"), 4);
    // '@' przed 'A', '[' po 'Z', '`' przed 'a', '{' po 'z'
    EXPECT_EQ(ile_liter("@[`{"), 0);
}

TEST(Zadanie4_Policz, Przyklad) {
    const Statystyka s = policz("Ala ma 2 koty, 3 psy!");
    EXPECT_EQ(s.wielkie, 1);
    EXPECT_EQ(s.male, 11);
    EXPECT_EQ(s.cyfry, 2);
    EXPECT_EQ(s.spacje, 5);
}
TEST(Zadanie4_Policz, PustyTekst) {
    const Statystyka s = policz("");
    EXPECT_EQ(s.wielkie, 0);
    EXPECT_EQ(s.male, 0);
    EXPECT_EQ(s.cyfry, 0);
    EXPECT_EQ(s.spacje, 0);
}
TEST(Zadanie4_Policz, TylkoSpacjeIZnaki) {
    const Statystyka s = policz("  ?! ");
    EXPECT_EQ(s.spacje, 3);
    EXPECT_EQ(s.wielkie + s.male + s.cyfry, 0);
}
