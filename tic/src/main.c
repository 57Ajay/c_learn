#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_SIZE 3

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = ' ';
    }
  }
}

void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      printf("%c", board[i][j]);
      if (j < BOARD_SIZE - 1) {
        printf("|");
      }
    }
    printf("\n");
    if (i < BOARD_SIZE - 1) {
      printf("-+-+-");
      printf("\n");
    }
  }
}

void makeMove(char board[BOARD_SIZE][BOARD_SIZE], char player) {
  int row, col;
  while (1) {
    printf("Player %c, enter your move (row column: -> EX: 1(space)2): ",
           player);
    scanf("%d %d", &row, &col);

    row--;
    col--;

    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
      printf("Invalid row or column. Please enter values between 1 and 3.\n");
    } else if (board[row][col] != ' ') {
      printf("That cell is already taken. Please choose an empty cell.\n");
    } else {
      break;
    }
  }
  board[row][col] = player;
  printf("\n\n");
}

int checkWin(char board[BOARD_SIZE][BOARD_SIZE], char player) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[i][0] == player && board[i][1] == player &&
        board[i][2] == player) {
      return 1;
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (board[0][i] == player && board[1][i] == player &&
          board[2][i] == player) {
        return 1;
      }
    }
    if (board[0][0] == player && board[1][1] == player &&
        board[2][2] == player) {
      return 1;
    }
    if (board[0][2] == player && board[1][1] == player &&
        board[2][0] == player) {
      return 1;
    }
  }
  return 0;
}

int wouldWin(char board[BOARD_SIZE][BOARD_SIZE], int row, int col,
             char player) {
  char tempBoard[BOARD_SIZE][BOARD_SIZE];
  // Create a copy of the board
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      tempBoard[i][j] = board[i][j];
    }
  }

  // Make the hypothetical move on the temporary board
  tempBoard[row][col] = player;

  // Check if this move results in a win
  return checkWin(tempBoard, player);
}

void makeAIMove(char board[BOARD_SIZE][BOARD_SIZE], char player) {
  int row, col;

  // 1. Win: Check if the AI can win in the next move
  for (row = 0; row < BOARD_SIZE; row++) {
    for (col = 0; col < BOARD_SIZE; col++) {
      if (board[row][col] == ' ' && wouldWin(board, row, col, player)) {
        board[row][col] = player;
        return;
      }
    }
  }

  // 2. Block: Check if the opponent can win in the next move and block them
  char opponent = (player == 'X') ? 'O' : 'X';
  for (row = 0; row < BOARD_SIZE; row++) {
    for (col = 0; col < BOARD_SIZE; col++) {
      if (board[row][col] == ' ' && wouldWin(board, row, col, opponent)) {
        board[row][col] = player;
        return;
      }
    }
  }

  // 3. Center: Take the center if it's available
  if (board[1][1] == ' ') {
    board[1][1] = player;
    return;
  }
  // 4. Corners:
  int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
  for (int i = 0; i < 4; ++i) {
    int cornerRow = corners[i][0];
    int cornerCol = corners[i][1];
    if (board[cornerRow][cornerCol] == ' ') {
      board[cornerRow][cornerCol] = player;
      return;
    }
  }

  // 5. Random: Make a random move among the remaining empty cells
  while (1) {
    row = rand() % BOARD_SIZE;
    col = rand() % BOARD_SIZE;
    if (board[row][col] == ' ') {
      board[row][col] = player;
      return;
    }
  }
  printf("\n\n");
}

int main(void) {
  printf("Welcome to Tic-Tac-Toe!\n");
  char board[BOARD_SIZE][BOARD_SIZE];
  initializeBoard(board);
  srand(time(NULL));

  int gameMode;
  printf("Choose game mode:\n1. Player vs Player\n2. Player vs AI\n");
  scanf("%d", &gameMode);
  while (gameMode != 1 && gameMode != 2) {
    printf("Choose correct game mode:\n1. Player vs Player\n2. Player vs AI\n");
    scanf("%d", &gameMode);
  }

  for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
    char player = (i % 2 == 0) ? 'X' : 'O';

    if (gameMode == 2 && player == 'O') {
      printf("\n\nAI's turn\n");
      makeAIMove(board, player);
    } else {
      makeMove(board, player);
    }

    displayBoard(board);

    if (i >= 4) {
      if (checkWin(board, player)) {
        printf("Player %c wins!\n", player);
        return 0;
      }
    }
    if (i == BOARD_SIZE * BOARD_SIZE - 1) {
      printf("It's a draw!\n");
      return 0;
    }
  }

  return 0;
}
