#include <stdio.h>
#include <stdlib.h>
// a function which which helps create a file and write to it

int main(void) {

  char fileName[10];
  char fileContent[1000];
  FILE *file;

  printf("Enter name of the file: ");
  scanf("%s", fileName);
  file = fopen(fileName, "w");
  if (file == NULL) {
    printf("Error creating/opening the file.\n");
    exit(1);
  }

  printf("File %s created successfully.\n", fileName);
  printf("Enter the contents of the file below: \n");
  getchar(); // This consumes the leftovers newline charectors like \n
  while (fgets(fileContent, sizeof(fileContent), stdin) != NULL) {
    if (fileContent[0] == '\n') {
      break;
    }
    fputs(fileContent, file);
  }
  fclose(file);
  printf("File saved successfully.\n");

  return 0;
}
