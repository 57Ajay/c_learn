#include <stdio.h>
#include <string.h>
struct myStructure {
  int Number;
  char letter;
  char Name[20];
};
enum Level { LOW, MEDIUM, HIGH };
int structMain(void) {
  struct myStructure myS;
  myS.Number = 4464;
  myS.letter = 'A';
  strcpy(myS.Name, "Ajay Upadhyay");
  struct myStructure mys2 = {22, 'U', "Ajay"};
  printf("\n%d\n%s", myS.Number, myS.Name);
  printf("\n%s", mys2.Name);
  enum Level myL;
  myL = MEDIUM;
  printf("\n%d", myL);
  return 0;
}
