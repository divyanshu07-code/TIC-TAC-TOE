/*
 * TIC TAC TOE with Minimax AI 
 * -------------------------------------------------
 * Player is 'X', Computer (AI) is 'O'.
 *   1. Type a single number 1-9 for your move (numpad-style layout),
 *      instead of typing a row and a column.
 *   2. A "keypad" reference is shown so you always know which
 *      number maps to which cell.
 *   3. You can choose a difficulty: Easy / Medium / Hard.
 *        - Easy   -> AI plays completely randomly.
 *        - Medium -> AI plays well half the time, randomly otherwise.
 *        - Hard   -> AI plays a perfect game (Minimax), it will never lose.
 *   4. Bad input no longer breaks the program - it just asks again.
 *   5. You can play multiple rounds in a row, with a running score.
 
 * Compile:  gcc tictactoe.c -o tictactoe
 * Run:      ./tictactoe
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HUMAN 'X'
#define AI 'O'
#define EMPTY ' '

typedef enum { EASY = 1, MEDIUM = 2, HARD = 3 } Difficulty;

char board[3][3];
int scoreHuman = 0;
int scoreAI = 0;
int scoreDraw = 0;

/* ---------- Board utilities ---------- */

void initBoard(void) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = EMPTY;
}

/* Maps a 1-9 keypad number to a (row, col) pair.
 * Layout on screen:
 *   1 | 2 | 3
 *   4 | 5 | 6
 *   7 | 8 | 9
 */
void numberToCell(int number, int *row, int *col) {
    int index = number - 1;
    *row = index / 3;
    *col = index % 3;
}

void printBoard(void) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char cell = board[i][j];
            /* Show the position number as a hint on empty cells */
            if (cell == EMPTY) {
                int number = i * 3 + j + 1;
                printf(" %d ", number);
            } else {
                printf(" %c ", cell);
            }
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

/* Returns 1 if the given player has won */

int hasWon(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1;
    return 0;
}

/* Returns 1 if the board is completely filled */

int isBoardFull(void) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return 0;
    return 1;
}

/* Clears the rest of the current input line - keeps bad input
 * (letters, extra junk, etc.) from breaking later scanf() calls. */

void clearInputLine(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* ---------- Minimax Algorithm ---------- */


int minimax(int depth, int isMaximizing) {
    if (hasWon(AI))    return 10 - depth;
    if (hasWon(HUMAN)) return depth - 10;
    if (isBoardFull()) return 0;

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    int score = minimax(depth + 1, 0);
                    board[i][j] = EMPTY;
                    if (score > best) best = score;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    int score = minimax(depth + 1, 1);
                    board[i][j] = EMPTY;
                    if (score < best) best = score;
                }
            }
        }
        return best;
    }
}

/* Plays the AI's best possible move (perfect play) */

void playBestMove(void) {
    int bestScore = -1000;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int score = minimax(0, 0);
                board[i][j] = EMPTY;

                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    if (bestRow != -1) {
        board[bestRow][bestCol] = AI;
        printf("Computer plays cell %d\n", bestRow * 3 + bestCol + 1);
    }
}

/* Plays a uniformly random legal move */

void playRandomMove(void) {
    int emptyCells[9];
    int count = 0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                emptyCells[count++] = i * 3 + j;

    if (count == 0) return;

    int chosen = emptyCells[rand() % count];
    int row = chosen / 3;
    int col = chosen % 3;
    board[row][col] = AI;
    printf("Computer plays cell %d\n", chosen + 1);
}

/* Chooses how the computer moves based on the selected difficulty */

void computerMove(Difficulty difficulty) {
    switch (difficulty) {
        case EASY:
            playRandomMove();
            break;
        case MEDIUM:
            /* Half the time play perfectly, half the time play randomly */
            if (rand() % 2 == 0)
                playBestMove();
            else
                playRandomMove();
            break;
        case HARD:
        default:
            playBestMove();
            break;
    }
}

/* ---------- Human move handling ---------- */

int isValidMove(int row, int col) {
    if (row < 0 || row > 2 || col < 0 || col > 2) return 0;
    if (board[row][col] != EMPTY) return 0;
    return 1;
}

void humanMove(void) {
    int number, row, col;
    while (1) {
        printf("Your turn! Enter a number 1-9 (see the board above): ");
        if (scanf("%d", &number) != 1) {
            printf("That's not a number. Please try again.\n");
            clearInputLine();
            continue;
        }
        clearInputLine();

        if (number < 1 || number > 9) {
            printf("Please enter a number between 1 and 9.\n");
            continue;
        }

        numberToCell(number, &row, &col);

        if (isValidMove(row, col)) {
            board[row][col] = HUMAN;
            break;
        } else {
            printf("That cell is already taken. Try again.\n");
        }
    }
}

/* ---------- Helpers for menu input ---------- */

int askYesNo(const char *prompt) {
    int choice;
    while (1) {
        printf("%s (1 = Yes, 2 = No): ", prompt);
        if (scanf("%d", &choice) == 1 && (choice == 1 || choice == 2)) {
            clearInputLine();
            return choice == 1;
        }
        printf("Please enter 1 or 2.\n");
        clearInputLine();
    }
}

Difficulty askDifficulty(void) {
    int choice;
    while (1) {
        printf("Choose a difficulty:\n");
        printf("  1) Easy   - computer plays randomly\n");
        printf("  2) Medium - computer plays well about half the time\n");
        printf("  3) Hard   - computer plays a perfect game (never loses)\n");
        printf("Your choice: ");
        if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3) {
            clearInputLine();
            return (Difficulty)choice;
        }
        printf("Please enter 1, 2, or 3.\n");
        clearInputLine();
    }
}

/* ---------- Main game loop ---------- */

void playOneRound(Difficulty difficulty) {
    initBoard();
    int humanTurn = askYesNo("Do you want to go first?");

    printBoard();

    while (1){
        if (humanTurn){
            humanMove();
        } else{
            computerMove(difficulty);
        }
        printBoard();

        if (hasWon(HUMAN)) {
            printf("Congratulations! You win!\n");
            scoreHuman++;
            break;
        }
        if (hasWon(AI)) {
            printf("Computer wins! Better luck next time.\n");
            scoreAI++;
            break;
        }
        if (isBoardFull()) {
            printf("It's a draw!\n");
            scoreDraw++;
            break;
        }
        humanTurn = !humanTurn;
    }
    printf("Score  ->  You: %d   Computer: %d   Draws: %d\n", scoreHuman, scoreAI, scoreDraw);
}

int main(void) {
    srand((unsigned int)time(NULL));
    printf("=== TIC TAC TOE (You are X, Computer is O) ===\n");
    printf("Tip: on your turn, just type the number shown on the cell you want.\n");
    Difficulty difficulty = askDifficulty();

    do {
        playOneRound(difficulty);
    } while (askYesNo("\nPlay another round?"));

    printf("\nThanks for playing! Final score -> You: %d  Computer: %d  Draws: %d\n",
           scoreHuman, scoreAI, scoreDraw);
    return 0;
}
