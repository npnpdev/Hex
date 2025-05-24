# Hex

[English](#english-version) | [Polski](#wersja-polska)

---

## English Version

### Project Description

Command-line C++ application for analyzing Hex board positions and answering queries about board size, pawn counts, validity, game-over status, reachability of positions, and win-in-N-moves scenarios against naive or perfect opponents.

### Key Features

* **BOARD\_SIZE / PAWNS\_NUMBER**: computes board dimensions (1–11) and total pawns (0–121)
* **State Validation**: checks pawn-count balance and historical plausibility (IS\_BOARD\_CORRECT, IS\_BOARD\_POSSIBLE)
* **Game Over Detection**: BFS-based path search for Red (top–bottom) or Blue (left–right) victory (IS\_GAME\_OVER)
* **Naive Opponent Analysis**: simulates 1–2 moves to determine if Red/Blue can force a win against worst-play (CAN\_\*\_WITH\_NAIVE\_OPPONENT)
* **Perfect Opponent Analysis**: minimax search up to depth 4 to determine forced wins against optimal defense (CAN\_\*\_WITH\_PERFECT\_OPPONENT)
* **Query Dispatcher**: parses textual queries and outputs answers per specification

### Technologies

* **Language**: C++17
* **Libraries & APIs**: STL (vector, string, iostream), `<cmath>`
* **Algorithms**: BFS for connectivity, naive simulation, minimax game tree search
* **Build**: any C++17-compatible compiler

### Project Structure

```text
src/
├─ constants.h          ← definitions (MAX_SIZE, player symbols, queries)
├─ main.cpp             ← input parsing, board construction, query handler
└─ utils.cpp/.h (opt.)  ← BFS, board-possible check, win-in-N-moves logic
```

### Example Results

```text
BOARD_SIZE
→ 11

PAWNS_NUMBER
→ 54

IS_BOARD_CORRECT
→ YES

IS_GAME_OVER
→ NO

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
→ YES

CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
→ NO
```

---

## Wersja polska

### Opis projektu

Konsolowa aplikacja C++ do analizy pozycji na planszy Hex oraz udzielania odpowiedzi na zapytania o rozmiar planszy, liczbę pionów, poprawność stanu, zakończenie gry, osiągalność stanu i wygrane w N ruchach przeciw naiwnemu lub doskonałemu przeciwnikowi.

### Kluczowe funkcje

* **BOARD\_SIZE / PAWNS\_NUMBER**: oblicza wymiary planszy (1–11) i całkowitą liczbę pionów (0–121)
* **Walidacja stanu**: sprawdza balans pionów i historyczną spójność (IS\_BOARD\_CORRECT, IS\_BOARD\_POSSIBLE)
* **Detekcja końca gry**: wyszukiwanie ścieżki BFS dla czerwonego (góra–dół) lub niebieskiego (lewo–prawo) zwycięstwa (IS\_GAME\_OVER)
* **Analiza naiwnym przeciwnikiem**: symuluje 1–2 ruchy, czy Czerwony/Niebieski może wymusić wygraną przy najgorszej grze (CAN\_\*\_WITH\_NAIVE\_OPPONENT)
* **Analiza doskonałym przeciwnikiem**: minimax do głębokości 4 dla wygranej przeciw optymalnej obronie (CAN\_\*\_WITH\_PERFECT\_OPPONENT)
* **Dispatcher zapytań**: parsuje zapytania i zwraca odpowiedzi zgodnie ze specyfikacją

### Technologie

* **Język**: C++17
* **Biblioteki i API**: STL (vector, string, iostream), `<cmath>`
* **Algorytmy**: BFS, prosta symulacja, minimax dla drzewa gry
* **Kompilacja**: dowolny kompilator zgodny z C++17

### Struktura projektu

```text
src/
├─ constants.h          ← definicje (MAX_SIZE, symbole graczy, zapytania)
├─ main.cpp             ← parsowanie wejścia, budowa planszy, obsługa zapytań
└─ utils.cpp/.h (opt.)  ← BFS, sprawdzanie możliwego stanu, logika wygranej w N ruchach
```

### Przykładowe wyniki

```text
BOARD_SIZE
→ 11

PAWNS_NUMBER
→ 54

IS_BOARD_CORRECT
→ YES

IS_GAME_OVER
→ NO

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
→ YES

CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
→ NO
```

---

## Autor

Igor Tomkowicz
📧 [npnpdev@gmail.com](mailto:npnpdev@gmail.com)
GitHub: [npnpdev](https://github.com/npnpdev)
LinkedIn: [igor-tomkowicz](https://www.linkedin.com/in/igor-tomkowicz-a5760b358/)

## License

MIT License – see [LICENSE](LICENSE) for details.
