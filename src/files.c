#include <stdio.h>

void fileHandle(void) {
  FILE *fptr;
  // Open a file in writing mode
  fptr = fopen("f.txt", "w");
  // Write some text to the file and delete the extsting content
  // if any data exists on file before;
  // we can use append with "a" instead of "w";
  fprintf(fptr, "Some text");
  fclose(fptr);
  fptr = fopen("f.txt", "a");
  fprintf(fptr, "\nSome more text");
  // Close the file
  fclose(fptr);
}

void readFile() {
  FILE *filePtr;
  filePtr = fopen("f.txt", "r");
  if (filePtr == NULL) {
    printf("File does not exist");
  }
  // char fstr[100];
  char fstr2[100];
  // fgets(fstr, 100, filePtr);
  while (fgets(fstr2, 100, filePtr)) {
    printf("%s", fstr2);
  }
  fclose(filePtr);
  // printf("\nSingle line: %s", fstr);
}

int fmain() {
  fileHandle();
  readFile();
  return 0;
}
