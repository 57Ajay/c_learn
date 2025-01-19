#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep function

// ANSI Color codes for better visibility
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define BOLD "\x1b[1m"

// Clear screen function for different operating systems
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

typedef struct {
  char name[20];
  int account_number;
  char ifsc[10];
  float balance;
} Account;

typedef enum { SUCCESS, FAIL } STATUS;

void showLoadingAnimation(const char *message) {
  printf("%s", CYAN);
  printf("%s", message);
  for (int i = 0; i < 3; i++) {
    printf(".");
    fflush(stdout);
    usleep(300000); // 300ms delay
  }
  printf("%s\n", RESET);
}

float get_balance(Account *account) { return account->balance; }

STATUS deposit(Account *account, float amount) {
  if (amount <= 0) {
    printf("%sDeposit amount must be positive.%s\n", RED, RESET);
    return FAIL;
  }
  account->balance += amount;
  return SUCCESS;
}

STATUS withdraw(Account *account, float amount) {
  if (amount <= 0) {
    printf("%sWithdrawal amount must be positive.%s\n", RED, RESET);
    return FAIL;
  }
  if (account->balance >= amount) {
    account->balance -= amount;
    return SUCCESS;
  } else {
    printf("%sInsufficient balance.%s\n", RED, RESET);
    return FAIL;
  }
}

STATUS transfer(Account *from, Account *to, float amount) {
  if (amount <= 0) {
    printf("%sTransfer amount must be positive.%s\n", RED, RESET);
    return FAIL;
  }
  if (from->balance >= amount) {
    from->balance -= amount;
    to->balance += amount;
    return SUCCESS;
  } else {
    printf("%sTransfer failed: Insufficient balance.%s\n", RED, RESET);
    return FAIL;
  }
}

Account *find_account(Account accounts[], int size, int account_number) {
  for (int i = 0; i < size; i++) {
    if (accounts[i].account_number == account_number) {
      return &accounts[i];
    }
  }
  return NULL;
}

void print_account_details(Account *account) {
  if (account != NULL) {
    printf("\n%s═════════ Account Details ═════════%s\n", YELLOW, RESET);
    printf("%s║%s Name: %s%s%s\n", YELLOW, RESET, CYAN, account->name, RESET);
    printf("%s║%s Account Number: %s%d%s\n", YELLOW, RESET, CYAN,
           account->account_number, RESET);
    printf("%s║%s IFSC: %s%s%s\n", YELLOW, RESET, CYAN, account->ifsc, RESET);
    printf("%s║%s Balance: %s₹%.2f%s\n", YELLOW, RESET, GREEN, account->balance,
           RESET);
    printf("%s═══════════════════════════════%s\n", YELLOW, RESET);
  } else {
    printf("%sAccount not found.%s\n", RED, RESET);
  }
}

void display_menu() {
  printf("\n%s╔════════ BANKING MENU ════════╗%s\n", MAGENTA, RESET);
  printf("%s║%s [B] Check Balance           %s║%s\n", MAGENTA, CYAN, MAGENTA,
         RESET);
  printf("%s║%s [D] Deposit                 %s║%s\n", MAGENTA, CYAN, MAGENTA,
         RESET);
  printf("%s║%s [W] Withdraw                %s║%s\n", MAGENTA, CYAN, MAGENTA,
         RESET);
  printf("%s║%s [T] Transfer                %s║%s\n", MAGENTA, CYAN, MAGENTA,
         RESET);
  printf("%s║%s [P] Print Account Details   %s║%s\n", MAGENTA, CYAN, MAGENTA,
         RESET);
  printf("%s║%s [E] Exit                    %s║%s\n", MAGENTA, CYAN, MAGENTA,
         RESET);
  printf("%s╚═══════════════════════════════╝%s\n", MAGENTA, RESET);
  printf("\n%sEnter your choice:%s ", BOLD, RESET);
}

int main(void) {
  Account accounts[] = {{"Ajay Upadhyay", 572002, "ajay572002", 100000.70},
                        {"Satyam", 782010, "saty782010", 696969.69},
                        {"Aman", 782011, "aman782011", 696969.69}};

  int len = sizeof(accounts) / sizeof(accounts[0]);
  char userInput;

  clearScreen();
  printf("%s%s╔═════════════════════════════════╗\n", BOLD, BLUE);
  printf("║     WELCOME TO THE BANK!        ║\n");
  printf("╚═════════════════════════════════╝%s\n", RESET);

  while (1) {
    display_menu();

    if (scanf(" %c", &userInput) != 1) {
      printf("%sInvalid input. Please enter a character.%s\n", RED, RESET);
      while (getchar() != '\n')
        ;
      continue;
    }
    userInput = tolower(userInput);

    int accountNumber, toAccount;
    float amount;
    Account *acc, *toAcc;

    switch (userInput) {
    case 'b':
    case 'd':
    case 'w':
    case 'p':
      printf("%sEnter account number:%s ", YELLOW, RESET);
      if (scanf("%d", &accountNumber) != 1) {
        printf("%sInvalid account number input.%s\n", RED, RESET);
        while (getchar() != '\n')
          ;
        break;
      }

      showLoadingAnimation("Processing");
      acc = find_account(accounts, len, accountNumber);

      if (acc == NULL) {
        printf("%sAccount not found%s\n", RED, RESET);
        break;
      }

      switch (userInput) {
      case 'b':
        printf("%sBalance for %s%s%s: %s₹%.2f%s\n", BLUE, GREEN, acc->name,
               BLUE, GREEN, get_balance(acc), RESET);
        break;

      case 'd':
        printf("%sEnter amount to deposit:%s ", YELLOW, RESET);
        if (scanf("%f", &amount) != 1) {
          printf("%sInvalid amount input.%s\n", RED, RESET);
          while (getchar() != '\n')
            ;
          break;
        }
        showLoadingAnimation("Processing deposit");
        if (deposit(acc, amount) == SUCCESS) {
          printf("%sDeposit successful. New balance: ₹%.2f%s\n", GREEN,
                 get_balance(acc), RESET);
        }
        break;

      case 'w':
        printf("%sEnter amount to withdraw:%s ", YELLOW, RESET);
        if (scanf("%f", &amount) != 1) {
          printf("%sInvalid amount input.%s\n", RED, RESET);
          while (getchar() != '\n')
            ;
          break;
        }
        showLoadingAnimation("Processing withdrawal");
        if (withdraw(acc, amount) == SUCCESS) {
          printf("%sWithdrawal successful. New balance: ₹%.2f%s\n", GREEN,
                 get_balance(acc), RESET);
        }
        break;

      case 'p':
        print_account_details(acc);
        break;
      }
      break;

    case 't':
      printf("%sEnter account number to transfer from:%s ", YELLOW, RESET);
      if (scanf("%d", &accountNumber) != 1) {
        printf("%sInvalid input for from account.%s\n", RED, RESET);
        while (getchar() != '\n')
          ;
        break;
      }

      showLoadingAnimation("Verifying sender account");
      acc = find_account(accounts, len, accountNumber);
      if (acc == NULL) {
        printf("%sSender Account not found%s\n", RED, RESET);
        break;
      }

      printf("%sEnter account number to transfer to:%s ", YELLOW, RESET);
      if (scanf("%d", &toAccount) != 1) {
        printf("%sInvalid input for to account.%s\n", RED, RESET);
        while (getchar() != '\n')
          ;
        break;
      }

      showLoadingAnimation("Verifying receiver account");
      toAcc = find_account(accounts, len, toAccount);
      if (toAcc == NULL) {
        printf("%sReceiver Account not found%s\n", RED, RESET);
        break;
      }

      printf("%sEnter transfer amount:%s ", YELLOW, RESET);
      if (scanf("%f", &amount) != 1) {
        printf("%sInvalid amount input.%s\n", RED, RESET);
        while (getchar() != '\n')
          ;
        break;
      }

      showLoadingAnimation("Processing transfer");
      if (transfer(acc, toAcc, amount) == SUCCESS) {
        printf("%sTransfer successful!%s\n", GREEN, RESET);
        printf("%sNew balance for %s: ₹%.2f%s\n", BLUE, acc->name, acc->balance,
               RESET);
        printf("%sNew balance for %s: ₹%.2f%s\n", BLUE, toAcc->name,
               toAcc->balance, RESET);
      }
      break;

    case 'e':
      printf("%sThank you for using our banking system. Goodbye!%s\n", GREEN,
             RESET);
      exit(0);

    default:
      printf("%sInvalid option. Please try again.%s\n", RED, RESET);
    }
  }
  return 0;
}
