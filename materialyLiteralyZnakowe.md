# Literały znakowe w C++

## 1. Wprowadzenie

> **Główne założenie:** literał znakowy pozwala zapisać w kodzie **znak zamiast jego kodu liczbowego**. Piszemy `'A'`, a kompilator sam podstawia liczbę 65. Kod jest czytelny (`if (c == 'A')` zamiast `if (c == 65)`), nie trzeba znać tabeli kodów, a znaki niewidoczne (koniec linii, tabulator) i spoza ASCII (polskie litery, emoji) zapisuje się w jednolity sposób.

**Literał** to wartość zapisana wprost w kodzie: `42`, `3.14`, `true`. **Literał znakowy** to pojedynczy znak w **apostrofach**: `'A'`, `'7'`, `'+'`, `'\n'`.

Każdy znak ma kod liczbowy, np. w ASCII `'A'` = 65, `'a'` = 97, `'0'` = 48. Typ `char` to mała liczba całkowita (1 bajt), więc na znakach można liczyć, porównywać je i używać ich w `switch`.

Zastosowania: parsery i kalkulatory, walidacja danych, zamiana cyfr na liczby, formatowanie wyjścia (`'\t'`, `'\n'`), Unicode.

## 2. Znak to liczba

```cpp
#include <iostream>

int main() {
    char c = 'A';
    std::cout << c << '\n';                          // A
    std::cout << static_cast<int>(c) << '\n';        // 65
    std::cout << c + 1 << '\n';                      // 66
    std::cout << static_cast<char>(c + 1) << '\n';   // B
    std::cout << sizeof('A') << ' ' << sizeof("A") << '\n';  // 1 2
}
```

**Co się tu dzieje?**

- `char c = 'A';` – w zmiennej zapisuje się liczba 65.
- `std::cout << c` wypisuje **literę**, bo dla typu `char` strumień wypisuje znak.
- `static_cast<int>(c)` wypisuje **liczbę** 65, czyli kod znaku.
- `c + 1` daje 66, a nie `B`: w działaniach arytmetycznych `char` zamienia się na `int` (**promocja całkowita**).
- `static_cast<char>(c + 1)` przywraca typ `char`, więc wypisuje się `B`.
- `sizeof('A')` to 1, a `sizeof("A")` to 2: `"A"` jest **napisem**, czyli tablicą `{'A', '\0'}`.

## 3. Sekwencje ucieczki

Znaki niewidoczne lub mające specjalne znaczenie w składni zapisuje się **ukośnikiem wstecznym** `\` z literą lub kodem. Cała sekwencja to nadal **jeden znak**.

| Sekwencja | Znaczenie | Kod |
|--|--|--|
| `'\n'` | nowa linia | 10 |
| `'\t'` | tabulator | 9 |
| `'\0'` | znak o kodzie 0, kończy napisy w stylu C | 0 |
| `'\\'` | ukośnik wsteczny `\` | 92 |
| `'\''` | apostrof `'` | 39 |
| `'\"'` | cudzysłów (w literale znakowym wystarczy `'"'`) | 34 |
| `'\r'`, `'\a'`, `'\b'` | powrót karetki, sygnał dźwiękowy, cofnięcie | 13, 7, 8 |
| `'\101'` | kod **ósemkowy**, tu `A` | 65 |
| `'\x41'` | kod **szesnastkowy**, tu `A` | 65 |
| `u'\u017C'`, `U'\U0001F600'` | znak Unicode podany numerem | – |

**Mniej oczywiste wiersze:**

- **`'\r'`, `'\a'`, `'\b'`** to znaki sterujące: niczego nie rysują, tylko wydają polecenie terminalowi.
  - `'\r'` przenosi kursor na początek linii: `"12345\rAB"` wyświetli `AB345`.
  - `'\a'` to sygnał dźwiękowy (często ignorowany przez konsole).
  - `'\b'` cofa kursor o jedną pozycję: `"abc\bX"` wyświetli `abX`.
- **`\u017C`, `\U0001F600`**: numer znaku w Unicode (`ż` = U+017C, 😀 = U+1F600). `\u` przyjmuje dokładnie 4 cyfry szesnastkowe, `\U` dokładnie 8. Zapis składa się tylko ze znaków ASCII, więc działa przy każdym kodowaniu pliku.

```cpp
#include <iostream>

int main() {
    std::cout << "Imie\tWiek\n";
    std::cout << "Ala\t21\n";
    std::cout << '\'' << " oraz " << '"' << '\n';      // ' oraz "
    std::cout << "Powiedzial: \"Hej\"\n";              // Powiedzial: "Hej"
    std::cout << "C:\\Users\\student\n";               // C:\Users\student
    std::cout << '\x41' << '\101' << '\n';             // AA
    std::cout << static_cast<int>('\0') << ' '
              << static_cast<int>('0') << '\n';        // 0 48
}
```

**Co się tu dzieje?**

- `'\''` – apostrof w apostrofach wymaga `\`. Cudzysłów `'"'` nie wymaga, bo nie zamyka literału znakowego.
- `"Powiedzial: \"Hej\""` – w **napisie** jest odwrotnie: `\` wymaga cudzysłów.
- `"C:\\Users\\student"` – jeden ukośnik zapisuje się jako `\\`. Samo `\U` w `C:\Users` byłoby początkiem kodu Unicode i program by się nie skompilował.
- `'\0'` (kod 0) i `'0'` (kod 48) to różne znaki.

### Jak kompilator odczytuje kody liczbowe

**Kod ósemkowy** (`\101`) to numer znaku w systemie ósemkowym (cyfry 0–7). Wagi kolejnych pozycji to potęgi ósemki: 1, 8, 64 (zamiast 1, 10, 100).

| Zapis | Obliczenie | Wynik |
|--|--|--|
| `'\7'` | 7·1 | 7 |
| `'\12'` | 1·8 + 2·1 | 10, czyli `'\n'` |
| `'\101'` | 1·64 + 0·8 + 1·1 | 65, czyli `'A'` |

Kompilator bierze od 1 do 3 cyfr ósemkowych, nigdy więcej. Popularne `'\0'` to po prostu kod ósemkowy z jedną cyfrą. Cyfry 8 i 9 nie istnieją w tym systemie, więc `'\8'` jest błędne.

**Kod szesnastkowy** (`\x41`) to numer w systemie szesnastkowym (cyfry 0–9 i A–F, wagi 1, 16, 256): `41` = 4·16 + 1 = 65. Kompilator bierze **wszystkie** kolejne cyfry szesnastkowe, aż trafi na inny znak. Dlatego `\x` jest **zachłanne**.

```cpp
#include <iostream>

int main() {
    std::cout << static_cast<int>('\7') << ' '        // 7
              << static_cast<int>('\12') << ' '       // 10
              << static_cast<int>('\101') << '\n';    // 65
    std::cout << "\1011" << '\n';      // A1

    std::cout << "\x41Hej" << '\n';    // AHej
    std::cout << "\x41" "BC" << '\n';  // ABC
    std::cout << "\101BC" << '\n';     // ABC
}
```

**Co się tu dzieje?**

- `"\1011"` to `"A1"`: kod ósemkowy kończy się po trzech cyfrach, więc czwarta `1` jest zwykłym znakiem.
- `"\x41Hej"` działa, bo `H` nie jest cyfrą szesnastkową.
- `"\x41BC"` (nie ma go w programie) **nie** dałoby `"ABC"`: `B` i `C` to cyfry szesnastkowe, więc kompilator odczytuje jeden kod 0x41BC = 16828. Nie mieści się on w `char`, więc kompilator zgłasza błąd lub ostrzeżenie.
- Dwie ostatnie instrukcje to poprawne zapisy `"ABC"`: `"\x41" "BC"` (sąsiednie napisy kompilator skleja, a cudzysłów kończy kod) oraz `"\101BC"` (kod ósemkowy kończy się po 3 cyfrach). W C++23 można też napisać `"\x{41}BC"` (rozdział 8).

## 4. Prefiksy i Unicode

Prefiks przed apostrofem zmienia **typ** literału:

| Zapis | Typ | Od wersji | Co mieści |
|--|--|--|--|
| `'a'` | `char` | zawsze | 1 bajt, w praktyce ASCII |
| `u8'a'` | `char8_t` | C++17 (typ od C++20) | 1 bajt UTF-8, czyli też tylko ASCII |
| `u'ż'` | `char16_t` | C++11 | 2 bajty UTF-16, prawie wszystkie znaki |
| `U'😀'` | `char32_t` | C++11 | 4 bajty UTF-32, **każdy** znak Unicode |
| `L'ż'` | `wchar_t` | zawsze | 2 bajty na Windowsie, 4 na Linuksie |

```cpp
#include <iostream>

int main() {
    char     a = 'a';
    char16_t z = u'ż';
    char32_t e = U'😀';

    std::cout << sizeof(a) << ' ' << sizeof(z) << ' ' << sizeof(e) << '\n';  // 1 2 4
    std::cout << std::hex << static_cast<int>(z) << ' '
              << static_cast<int>(e) << '\n';                                 // 17c 1f600
    std::cout << (z == u'\u017C') << '\n';                                    // 1
}
```

**Co się tu dzieje?**

- `sizeof` pokazuje rozmiar typów: `char` ma 1 bajt, `char16_t` 2 bajty, `char32_t` 4 bajty. Litera `ż` nie mieści się w 1 bajcie, dlatego potrzebny jest prefiks `u`, a emoji nie mieści się w 2 bajtach, dlatego `U`.
- W zmiennej zapisuje się numer znaku w Unicode. `std::hex` wypisuje go szesnastkowo: `17c` to U+017C (`ż`), a `1f600` to U+1F600 (😀).
- `z == u'\u017C'` daje 1: zapis literą i zapis numerem to ten sam znak.

## 5. Zastosowania praktyczne

### Zamiana cyfry na liczbę: `c - '0'`

```cpp
#include <cassert>
#include <iostream>
#include <string>

int naLiczbe(const std::string& tekst) {
    int wynik = 0;
    for (char c : tekst) {
        assert(c >= '0' && c <= '9');
        wynik = wynik * 10 + (c - '0');
    }
    return wynik;
}

int main() {
    std::cout << ('7' - '0') << '\n';                 // 7
    std::cout << naLiczbe("2026") + 1 << '\n';        // 2027

    char piatka = static_cast<char>('0' + 5);
    std::cout << piatka << '\n';                      // 5
}
```

**Co się tu dzieje?**

- `'7' - '0'` = 55 − 48 = **7**. Działa, bo standard C++ **gwarantuje**, że cyfry `'0'`…`'9'` mają kolejne kody.
- `naLiczbe("2026")` czyta cyfry od lewej. Mnożenie przez 10 przesuwa dotychczasowe cyfry w lewo i robi miejsce na nową: 2 → 20 → 202 → 2026.
- `'0' + 5` to operacja odwrotna: liczba 5 → znak `'5'`.

### Kalkulator ze `switch`

```cpp
#include <iostream>
#include <sstream>
#include <stdexcept>

double policz(double a, char op, double b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default:  throw std::invalid_argument("nieznany operator");
    }
}

int main() {
    std::istringstream wejscie("3 + 4\n10 / 4\n6 * 7");
    double a, b;
    char op;
    while (wejscie >> a >> op >> b) {
        std::cout << a << ' ' << op << ' ' << b << " = " << policz(a, op, b) << '\n';
    }
    // 3 + 4 = 7
    // 10 / 4 = 2.5
    // 6 * 7 = 42
}
```

**Co się tu dzieje?**

- Etykiety `case '+':` są możliwe, bo literał znakowy jest **stałą czasu kompilacji** (liczbą 43). Napis `"+"` nie może być etykietą `case`.
- `std::istringstream` udaje dane od użytkownika. `wejscie >> a >> op >> b` czyta liczbę, **jeden znak** (zmienna `char` wczytuje dokładnie jeden znak, pomijając spacje) i drugą liczbę.

### Zamiana liter i sprawdzanie hasła

```cpp
#include <iostream>
#include <string>

char naWielka(char c) {
    if (c >= 'a' && c <= 'z') {
        return static_cast<char>(c - 'a' + 'A');
    }
    return c;
}

bool silneHaslo(const std::string& haslo) {
    bool cyfra = false, wielka = false, specjalny = false;
    for (char c : haslo) {
        if (c >= '0' && c <= '9')                  cyfra = true;
        else if (c >= 'A' && c <= 'Z')             wielka = true;
        else if (c == '!' || c == '#' || c == '?') specjalny = true;
    }
    return haslo.size() >= 8 && cyfra && wielka && specjalny;
}

int main() {
    std::string tekst = "Ala ma kota 123";
    for (char& c : tekst) {
        c = naWielka(c);
    }
    std::cout << tekst << '\n';                          // ALA MA KOTA 123

    std::cout << std::boolalpha
              << silneHaslo("haslo") << ' '              // false
              << silneHaslo("Tajne!2026") << '\n';       // true
}
```

**Co się tu dzieje?**

- `c >= 'a' && c <= 'z'` sprawdza, czy znak jest małą literą: w ASCII litery mają kolejne kody, więc wystarczy porównać zakres.
- `c - 'a' + 'A'` zamienia małą literę na wielką. Np. dla `'m'`: `'m' - 'a'` = 12 (pozycja w alfabecie), a `'A' + 12` = `'M'`.
- `silneHaslo` sprawdza każdy znak, porównując go z literałami: zakres `'0'…'9'` to cyfra, zakres `'A'…'Z'` to wielka litera, a `'!'`, `'#'`, `'?'` to znaki specjalne.
- Biblioteka standardowa ma gotowe funkcje do tego samego: `std::isdigit`, `std::isupper`, `std::toupper` z `<cctype>`. Znak przekazuje się do nich jako `static_cast<unsigned char>(c)`, bo ujemna wartość (rozdział 6) to dla nich niezdefiniowane zachowanie.

## 6. Pułapki

```cpp
#include <iostream>

int main() {
    char c = '\xFF';
    std::cout << static_cast<int>(c) << '\n';   // -1 (x86) lub 255 (ARM)

    int kod = 'AB';
    std::cout << kod << '\n';                   // 16706
}
```

**Co się tu dzieje?**

- **`char` może być ujemny.** `'\xFF'` to bajt 255. Na x86 (Windows, Linux) `char` ma znak i mieści wartości od -128 do 127, więc 255 zamienia się w **-1**. Na ARM (np. Android, Raspberry Pi) `char` nie ma znaku i zostaje **255**. Ten sam kod daje różne wyniki.
- **`'AB'` to dwa znaki w apostrofach.** Taki literał ma typ `int`, a jego wartość zależy od kompilatora (zwykle kody 0x41 i 0x42 sklejają się w 0x4142 = 16706). Kompilator ostrzega przed nim, w nowym kodzie się go nie używa.

Pułapki związane z Unicode:

- **Polska litera bez prefiksu.** W UTF-8 `ż` zajmuje 2 bajty, więc `'ż'` nie mieści się w `char`. Kompilator zgłasza błąd albo tylko ostrzega i zapisuje bezsensowną wartość. Poprawnie: `u'ż'` albo napis `"ż"`.
- **`u8` w C++20.** `u8"tekst"` ma od C++20 typ `const char8_t[]`, więc stary kod `const char* s = u8"tekst";` przestał się kompilować.

## 7. Przykłady zaawansowane

### Szyfr Cezara

```cpp
#include <iostream>
#include <string>

std::string cezar(std::string tekst, int przesuniecie) {
    for (char& c : tekst) {
        if (c >= 'a' && c <= 'z') {
            c = static_cast<char>('a' + (c - 'a' + przesuniecie + 26) % 26);
        } else if (c >= 'A' && c <= 'Z') {
            c = static_cast<char>('A' + (c - 'A' + przesuniecie + 26) % 26);
        }
    }
    return tekst;
}

int main() {
    std::string szyfr = cezar("Ala ma kota, Zenon tez!", 3);
    std::cout << szyfr << '\n';               // Dod pd nrwd, Chqrq whc!
    std::cout << cezar(szyfr, -3) << '\n';    // Ala ma kota, Zenon tez!
}
```

**Co się tu dzieje?**

- Szyfr Cezara przesuwa każdą literę o stałą liczbę pozycji w alfabecie (przy 3: `A` → `D`).
- `c - 'a'` zamienia literę na jej pozycję w alfabecie (0–25), np. `'z'` → 25.
- `% 26` „zawija” alfabet: `'z'` (25) + 3 = 28, a 28 % 26 = 2, czyli `'c'`. Dlatego `tez` → `whc`.
- `+ 26` zabezpiecza przesunięcie ujemne: dla `'a'` i -3 bez niego wyszłoby -3, a reszta z dzielenia liczby ujemnej w C++ jest ujemna.
- `'a' + pozycja` zamienia pozycję z powrotem na literę. Wielkie litery obsługuje się tak samo z `'A'`, a inne znaki (spacje, przecinki) zostają bez zmian.

### Znak jako parametr szablonu i `constexpr`

```cpp
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

template <char Separator>
std::vector<std::string> podziel(const std::string& tekst) {
    std::vector<std::string> czesci(1);
    for (char c : tekst) {
        if (c == Separator) czesci.emplace_back();
        else czesci.back() += c;
    }
    return czesci;
}

constexpr bool czySamogloska(char c) {
    for (char s : {'a', 'e', 'i', 'o', 'u', 'y'}) {
        if (c == s) return true;
    }
    return false;
}

int main() {
    for (const auto& s : podziel<';'>("Ala;21;Krakow")) {
        std::cout << '[' << s << ']';                    // [Ala][21][Krakow]
    }
    std::cout << '\n';

    static_assert(czySamogloska('e') && !czySamogloska('k'));
}
```

**Co się tu dzieje?**

- Literał znakowy jest stałą czasu kompilacji, więc może być **parametrem szablonu**: `podziel<';'>` tworzy wersję funkcji, w której separatorem jest `';'`. Ten sam szablon obsłuży np. `podziel<','>`.
- `czySamogloska` porównuje znak z listą literałów `{'a', 'e', 'i', 'o', 'u', 'y'}`.
- Dzięki `constexpr` funkcję można wywołać podczas kompilacji, a `static_assert` sprawdza wynik, zanim program w ogóle się uruchomi.

### Ręczne kodowanie UTF-8

```cpp
#include <iostream>
#include <string>

std::string doUtf8(char32_t z) {
    std::string bajty;
    if (z < 0x80) {
        bajty += static_cast<char>(z);
    } else if (z < 0x800) {
        bajty += static_cast<char>(0xC0 | (z >> 6));
        bajty += static_cast<char>(0x80 | (z & 0x3F));
    } else if (z < 0x10000) {
        bajty += static_cast<char>(0xE0 | (z >> 12));
        bajty += static_cast<char>(0x80 | ((z >> 6) & 0x3F));
        bajty += static_cast<char>(0x80 | (z & 0x3F));
    } else {
        bajty += static_cast<char>(0xF0 | (z >> 18));
        bajty += static_cast<char>(0x80 | ((z >> 12) & 0x3F));
        bajty += static_cast<char>(0x80 | ((z >> 6) & 0x3F));
        bajty += static_cast<char>(0x80 | (z & 0x3F));
    }
    return bajty;
}

void pokazBajty(char32_t z) {
    for (char b : doUtf8(z)) {
        std::cout << std::hex << static_cast<int>(static_cast<unsigned char>(b)) << ' ';
    }
    std::cout << std::dec << '\n';
}

int main() {
    pokazBajty(U'A');     // 41
    pokazBajty(U'ż');     // c5 bc
    pokazBajty(U'😀');    // f0 9f 98 80
    std::cout << doUtf8(U'ż') << doUtf8(U'😀') << '\n';   // ż😀
}
```

**Co się tu dzieje?**

- Ten przykład wyjaśnia, dlaczego `'ż'` nie mieści się w `char` (rozdział 6). UTF-8 zapisuje numer znaku na 1–4 bajtach, zależnie od jego wielkości:

| Numer znaku | Bajty | Przykład |
|--|--|--|
| do 0x7F | 1 | `A` (0x41) → `41` |
| do 0x7FF | 2 | `ż` (0x17C) → `c5 bc` |
| do 0xFFFF | 3 | np. `€` (0x20AC) |
| powyżej | 4 | 😀 (0x1F600) → `f0 9f 98 80` |

- `z >> 6` i `z & 0x3F` dzielą numer znaku na porcje po 6 bitów. Pierwszy bajt (`0xC0`, `0xE0`, `0xF0`) mówi, ile bajtów ma znak, a kolejne zaczynają się od `0x80`.
- `static_cast<unsigned char>(b)` przy wypisywaniu to ta sama ochrona co w rozdziale 6: bajt `0xbc` w zwykłym `char` na x86 byłby ujemny (-68). Taką właśnie bezsensowną wartość może dostać błędne `'ż'` bez prefiksu.

## 8. Dla dociekliwych

- **W języku C `'A'` ma typ `int`, a w C++ typ `char`.** W C `sizeof('A')` to 4, w C++ to 1. C++ zmienił to ze względu na przeciążanie funkcji: `f('A')` powinno wywołać `f(char)`, a nie `f(int)`.
- **Skąd `'\?'`?** Dawniej istniały **trigrafy**, trzyznakowe zamienniki znaków niedostępnych na niektórych klawiaturach: `??/` oznaczało `\`, a `??!` oznaczało `|`. Napis `"Co??!"` zamieniał się w `"Co|"`, więc pisano `"Co?\?!"`. Trigrafy usunięto w C++17, a `\?` zostało.
- **Litery nie muszą mieć kolejnych kodów.** Standard gwarantuje to tylko dla cyfr. W kodowaniu EBCDIC (komputery mainframe IBM) między `'i'` a `'j'` są inne znaki, więc sprawdzanie zakresu `'a'…'z'` z rozdziału 5 jest poprawne tylko w ASCII/UTF-8, czyli w praktyce prawie wszędzie.

### Własny literał dla znaku (C++11)

```cpp
#include <iostream>

constexpr int operator""_cyfra(char c) {
    return c - '0';
}

int main() {
    static_assert('7'_cyfra == 7);
    std::cout << '4'_cyfra + '2'_cyfra << '\n';   // 6
}
```

**Co się tu dzieje?**

- `operator""_cyfra` to **własny sufiks** literału, tak jak `500ms` z `<chrono>`. Gdy kompilator widzi `'7'_cyfra`, wywołuje tę funkcję z argumentem `'7'`.
- W środku jest trik `c - '0'`, więc `'7'_cyfra` daje 7.
- `'4'_cyfra + '2'_cyfra` = 4 + 2 = **6**. Bez sufiksu `'4' + '2'` dałoby 52 + 50 = 102.
- Własne sufiksy muszą zaczynać się od `_`. Sufiksy bez `_` (`s`, `ms`, `h`) są zarezerwowane dla biblioteki standardowej.

### Nowe sekwencje ucieczki w C++23

```cpp
#include <iostream>

int main() {
    std::cout << '\x{41}' << '\o{101}' << '\N{LATIN CAPITAL LETTER A}' << '\n'; // AAA
    static_assert(U'\u{1F600}' == U'\U0001F600');
}
```

**Co się tu dzieje?**

- `'\x{41}'` to kod szesnastkowy w nawiasach. Nawiasy wyznaczają koniec kodu, więc problem zachłannego `\x` znika.
- `'\o{101}'` to kod ósemkowy w nawiasach (`o` od *octal*).
- `'\N{LATIN CAPITAL LETTER A}'` to znak podany **oficjalną nazwą** z Unicode.
- `U'\u{1F600}'` – w nawiasach można podać dowolną liczbę cyfr, więc nie trzeba wybierać między `\u` (4 cyfry) a `\U` (8 cyfr).

## 9. Podsumowanie & Definicje

Literał znakowy to czytelny zapis liczby, która reprezentuje znak. Na co dzień wystarcza `'a'` typu `char` i kilka sekwencji ucieczki (`'\n'`, `'\t'`, `'\0'`, `'\\'`, `'\''`). Prefiksy `u8`, `u`, `U`, `L` są potrzebne przy znakach spoza ASCII. Najważniejsze pułapki: `c + 1` daje `int`, znakowość `char` zależy od platformy, `\x` jest zachłanne, a polska litera bez prefiksu nie mieści się w `char`.

| Pojęcie | Prosta definicja |
|--|--|
| Literał | Wartość zapisana wprost w kodzie, np. `42`, `'A'`, `"tekst"`. |
| Literał znakowy | Pojedynczy znak w apostrofach, np. `'A'`. Typ `char` lub inny, zależnie od prefiksu. |
| `'A'` a `"A"` | Znak (1 bajt) a napis, czyli tablica `{'A', '\0'}` (2 bajty). |
| ASCII | Tabela kodów 0–127 podstawowych znaków, np. `'A'` = 65, `'0'` = 48. |
| Unicode / UTF-8 / UTF-16 / UTF-32 | Numeracja wszystkich znaków świata i trzy sposoby zapisu tych numerów w bajtach. |
| Sekwencja ucieczki | Zapis zaczynający się od `\` dla znaków, których nie da się wpisać wprost, np. `'\n'`. |
| Kod ósemkowy / szesnastkowy | Znak podany numerem: `'\101'` (1–3 cyfry 0–7) lub `'\x41'` (dowolnie wiele cyfr 0–9, A–F). |
| Promocja całkowita | Automatyczna zamiana `char` na `int` w działaniach, stąd `'A' + 1` = 66. |
| Prefiks literału | `u8`, `u`, `U`, `L` przed apostrofem; daje typ `char8_t`, `char16_t`, `char32_t`, `wchar_t`. |
| Literał wieloznakowy | `'AB'`, typ `int`, wartość zależna od kompilatora. |

## Źródła

- cppreference, *Character literal*: https://cppreference.com/cpp/language/character_literal
- Microsoft Learn, *String and character literals (C++)*: https://learn.microsoft.com/pl-pl/cpp/cpp/string-and-character-literals-cpp?view=msvc-170
- P1854R4, *Making non-encodable string literals ill-formed*: https://open-std.org/JTC1/sc22/wg21/docs/papers/2023/p1854r4.pdf
