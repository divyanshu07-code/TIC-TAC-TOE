# Tic Tac Toe (C, with Minimax AI)

A command-line Tic Tac Toe game written in C. You play as **X**, the
computer plays as **O**. Pick a difficulty, play as many rounds as you
like, and keep a running score.

## Features

- **Simple input** — just type a number 1-9 for the cell you want. The
  board shows you which number maps to which cell.
- **Three difficulty levels**
  - **Easy** — the computer moves randomly.
  - **Medium** — the computer plays well about half the time, and
    randomly the rest.
  - **Hard** — the computer plays a perfect game using the Minimax
    algorithm. It will never lose (best you can do is a draw).
- **Replay loop** — play multiple rounds without restarting the program.
- **Score tracking** — wins, losses, and draws are tallied across rounds.
- **Friendly input handling** — invalid input (letters, out-of-range
  numbers, taken cells) just prompts you to try again instead of
  crashing.

## Requirements

- A C compiler, e.g. `gcc`.

## Build

```bash
gcc tictactoe.c -o tictactoe
```

## Run

```bash
./tictactoe
```

## How to play

1. Choose a difficulty (1 = Easy, 2 = Medium, 3 = Hard).
2. Choose whether you want to go first.
3. On your turn, type the number of the cell you want to play, using
   this layout:
   

   ```
    1 | 2 | 3
   ---+---+---
    4 | 5 | 6
   ---+---+---
    7 | 8 | 9
   ```

5. Keep playing until someone gets three in a row (row, column, or
   diagonal) or the board fills up for a draw.
6. After each round, you'll be asked if you want to play again.

## How the AI works

The computer uses the **Minimax algorithm** to look ahead through every
possible sequence of moves and pick the one that leads to the best
outcome for itself, assuming you also play your best move at every
step. On **Hard**, it always uses this. On **Medium**, it uses it only
about half the time (and moves randomly otherwise) so it's beatable.
On **Easy**, it skips Minimax entirely and just picks a random open
cell.

## File overview

- `tictactoe.c` — the entire game: board logic, Minimax AI, input
  handling, and the main game loop.

## License

Feel free to use, modify, and share this project for any purpose.
