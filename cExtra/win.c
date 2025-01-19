#include <stdio.h>
#include <windows.h>

// (using Windows console API)
#define FOREGROUND_BLUE 0x0001
#define FOREGROUND_GREEN 0x0002
#define FOREGROUND_RED 0x0004
#define FOREGROUND_INTENSITY 0x0008
#define BACKGROUND_BLUE 0x0010
#define BACKGROUND_GREEN 0x0020
#define BACKGROUND_RED 0x0040
#define BACKGROUND_INTENSITY 0x0080

void set_color(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
  // Example usage:
  set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Bright blue text
  printf("This is bright blue text.\n");

  set_color(FOREGROUND_RED | FOREGROUND_GREEN |
            FOREGROUND_INTENSITY); // Bright yellow text
  printf("This is bright yellow text.\n");

  set_color(FOREGROUND_GREEN); // Green text
  printf("This is green text.\n");

  set_color(FOREGROUND_RED | BACKGROUND_BLUE |
            BACKGROUND_INTENSITY); // Red on bright blue
  printf("This is red text on bright blue background.\n");

  set_color(
      FOREGROUND_RED | FOREGROUND_GREEN |
      FOREGROUND_BLUE); // Resets to default white text on black background
  printf("This is default text.\n");

  // Interactive part
  char input[256];
  printf("Enter some text: ");
  fgets(input, sizeof(input), stdin);

  printf("You entered: ");
  set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  printf("%s", input);
  set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

  return 0;
}
