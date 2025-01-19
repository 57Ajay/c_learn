#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
  srand(time(NULL));
  printf("Guess the number between 0-10.\n");
  int guess = rand() % 11;
  for (int i = 0; i < 3; i++) {
    int userGuess;
    printf("Guess %d:", i + 1);
    scanf("%d", &userGuess);
    if (userGuess == guess) {
      printf("You win in %d guesses.", i + 1);
      break;
    }
  }
  return 0;
}
