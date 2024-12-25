#include "more.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define CONSTANT 10
void guessGame() {
  printf("%d", CONSTANT);
  int guess;
  int guessCounter = 1;
  printf("Welcome to guessing Game, Start by guessing a number b/w 0-100.\n");
  while (scanf("%d", &guess) != EOF && guessCounter != 5) {
    if (guess == 57) {
      printf("Good guess, you won.");
      break;
    } else {
      printf("Guess again it is more than half of 100 but less than 3/4 of "
             "it.\nGuess number: %d\n",
             guessCounter + 1);
    };
    guessCounter++;
  }
}

//
// void charIO() {
//   int c;
//   c = getchar();
//   while (c != EOF) {
//     putchar(c);
//     c = getchar();
//     if (c == *"A") {
//       break;
//     }
//   }
// }
//
// void charCount() {
//   long nc = 0;
//   int c;
//
//   // Read characters until EOF
//   while ((c = getchar()) != EOF) {
//     ++nc;
//   }
//
//   // Print the character count
//   printf("%ld\n", nc);
// }

void pb1_9() {
  int c;
  int lastCharWasBlank = 0;

  // Read characters from input until EOF
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      // Only print a blank if the last character was not a blank
      if (!lastCharWasBlank) {
        putchar(c);
        lastCharWasBlank = 1; // Mark that the last character was a blank
      }
    } else if (c == 'Q') { // Only for coming out of it;
      break;
    } else {
      // Print the character and reset blank flag
      putchar(c);
      lastCharWasBlank = 0;
    }
  }
}

void pb1_10(void) {
  int c;
  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      // Replace tab with \t
      putchar('\\');       // Print backslash
      putchar('t');        // Print 't'
    } else if (c == 'Q') { // Only for coming out of it;
      break;
    } else if (c == '\b') {
      // Replace backspace with \b
      putchar('\\'); // Print backslash
      putchar('b');  // Print 'b'
    } else if (c == '\\') {
      // Replace backslash with '\\'
      putchar('\\'); // Print first backslash
      putchar('\\'); // Print second backslash
    } else {
      // Print the character as is
      putchar(c);
    }
  }
}

int revNum(void) {
  printf("\nEnter a number to reverse it: ");
  int num;
  scanf("%d", &num);
  int revNum = 0;
  while (num) {
    revNum = revNum * 10 + num % 10;
    num /= 10;
  };
  return revNum;
}

void string() {
  char name[] = "Ajay Uadhyay";
  printf("%llu", strlen(name));
  char str1[] = "Hello";
  char str2[] = "Hello";
  char str3[] = "Hi";

  // Compare str1 and str2, and print the result
  printf("\n%d\n", strcmp(str1, str2)); // Returns 0 (the strings are equal)

  // Compare str1 and str3, and print the result
  printf("%d\n", strcmp(str1, str3)); // Returns -4 (the strings are not equal)
  char fullName[30];

  printf("\nType your full name: \n");
  fgets(fullName, sizeof(fullName), stdin);

  printf("\nHello %s", fullName);
}

void memAddr() {
  int myAge = 22;
  char name[] = "Ajay";
  int *ptr = &myAge;
  printf("%p \n%p %d", (void *)&name, (void *)ptr, *ptr);
}

void ptrArr(void) {
  int myNumbers[4] = {25, 50, 75, 100};
  int *ptr = myNumbers;
  int i;
  printf("\n-------PTRARR-------\n");
  for (i = 0; i < 4; i++) {
    printf("%d\n", *(ptr + i));
  };

  // Change the value of the first element to 13
  *myNumbers = 13;

  // Change the value of the second element to 17
  *(myNumbers + 1) = 17;

  // Get the value of the first element
  printf("%d\n", *myNumbers);

  // Get the value of the second element
  printf("%d\n", *(myNumbers + 1));
}

void cmath(void) {
  printf("\nSquare root of 169 is: %f", sqrt(169));
  printf("\n%f", ceil(1.4));
  printf("\n%f", floor(1.4));
  printf("\n%f", pow(4, 3));
}

int moreMain() {
  printf("\n-------W3SCHOOLS-------");
  const char NAME[] = "AJay";
  // bool comes from <stdbool.h>
  bool ch = false;
  printf("\nname is :%s, boolean is :%d ", NAME, ch);
  printf("Reversed number is: %d\n", revNum());
  string();
  memAddr();
  ptrArr();
  cmath();
  return 0;
}
