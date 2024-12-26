#include "files.h"
#include "memMngmnt.h"
#include "more.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct {
  float fahrenheit;
  float celsius;
} Temp;

Temp *tempTable(int l, int u, int s, int *size) {
  int count = (u - l) / s + 1;
  *size = count;
  Temp *table = (Temp *)malloc(count * sizeof(Temp));
  if (table == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  for (float far = l; far <= u; far += s) {
    table[i].fahrenheit = far;
    table[i].celsius = (5.0 / 9.0) * (far - 32.0);
    i++;
  }

  return table;
}

int main(void) {
  int size;
  int lower = 0, upper = 300, step = 20;

  Temp *results = tempTable(lower, upper, step, &size);

  printf("-------------\n");
  for (int i = 0; i < size; i++) {
    printf("%4.0f %6.1f\n", results[i].fahrenheit, results[i].celsius);
  }
  printf("-------------\n");

  free(results);
  printf("----more.c----\n");
  // guessGame();
  printf("\n");
  // pb1_9();
  // pb1_10();
  moreMain();
  printf("\n----files.c----\n");
  fmain();
  printf("\n----structs.c----\n");
  structMain();
  printf("\n----MemoryManagement.c----\n");
  memMngmntMain();
  return 0;
}
