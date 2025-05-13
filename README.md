# 🃏 Teen Patti - C++ Card Game

A graphical version of the popular Indian card game **Teen Patti**, built in **C++** using the **Raylib** library. Play against 3 bot opponents in a simple turn-based system with power card mechanics and pile logic.

## 📦 Features

- Human vs 3 Bot gameplay.
- Power cards (2, 5, 10) with special effects:
  - **2** – Play again.
  - **5** – Reverse order; next card must be less than 5.
  - **10** – Burns the pile.
- Hand, blind, and seen-blind card logic.
- Graphical card display using Raylib.
- Bot decision-making with a delay to simulate realism.

## 🎮 How to Play

1. Each player is dealt:
   - 3 hand cards
   - 3 blind cards
   - 3 seen-blind cards
2. On your turn, click a card to play it if valid.
3. If no valid card is available, pick up the pile.
4. When hand cards run out, seen-blind cards are picked up.
5. When those run out, blind cards are revealed one by one.
6. The first player to run out of all cards wins.

## 🛠️ Requirements

- C++17 or later
- [Raylib](https://www.raylib.com/) installed and linked properly

## 🧑‍💻 Build & Run

### 🖥️ Compile with g++

```bash
g++ main.cpp Card.cpp Deck.cpp Player.cpp BotPlayer.cpp -o TeenPatti -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
