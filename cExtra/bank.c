#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char name[20];
  int account_number;
  char ifsc[10];
  float balance;
} Account;

typedef enum { SUCCESS, FAIL } STATUS;

float get_balance(Account *account) { return account->balance; }

STATUS deposit(Account *account, float amount) {
  if (amount <= 0) {
    printf("Deposit amount must be positive.\n");
    return FAIL;
  }
  account->balance += amount;
  return SUCCESS;
}

STATUS withdraw(Account *account, float amount) {
  if (amount <= 0) {
    printf("Withdrawal amount must be positive.\n");
    return FAIL;
  }
  if (account->balance >= amount) {
    account->balance -= amount;
    return SUCCESS;
  } else {
    printf("Insufficient balance.\n");
    return FAIL;
  }
}

STATUS transfer(Account *from, Account *to, float amount) {
  if (amount <= 0) {
    printf("Transfer amount must be positive.\n");
    return FAIL;
  }
  if (from->balance >= amount) {
    from->balance -= amount;
    to->balance += amount;
    return SUCCESS;
  } else {
    printf("Transfer failed: Insufficient balance.\n");
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
    printf("Account Details:\n");
    printf("Name: %s\n", account->name);
    printf("Account Number: %d\n", account->account_number);
    printf("IFSC: %s\n", account->ifsc);
    printf("Balance: %.2f\n", account->balance);
  } else {
    printf("Account not found.\n");
  }
}

int main(void) {
  Account accounts[] = {{"Ajay Upadhyay", 572002, "ajay572002", 100000.70},
                        {"Satyam", 782010, "saty782010", 696969.69},
                        {"Aman", 782011, "aman782011", 696969.69}};

  int len = sizeof(accounts) / sizeof(accounts[0]);
  char userInput;

  printf("Welcome to the bank!\n\n");

  while (1) {
    printf("\nChoose an option:\n");
    printf("b: Check balance\n");
    printf("d: Deposit\n");
    printf("w: Withdraw\n");
    printf("t: Transfer\n");
    printf("p: Print Account Details\n");
    printf("e: Exit\n");
    printf("Enter your choice: ");

    if (scanf(" %c", &userInput) != 1) {
      printf("Invalid input. Please enter a character.\n");
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
      printf("Enter account number: ");
      if (scanf("%d", &accountNumber) != 1) {
        printf("Invalid account number input.\n");
        while (getchar() != '\n')
          ;
        break;
      }
      acc = find_account(accounts, len, accountNumber);
      if (acc == NULL) {
        printf("Account not found\n");
        break;
      }

      if (userInput == 'b') {
        printf("Balance for %s: %.2f\n", acc->name, get_balance(acc));
      } else if (userInput == 'd') {
        printf("Enter amount to deposit: ");
        if (scanf("%f", &amount) != 1) {
          printf("Invalid amount input.\n");
          while (getchar() != '\n')
            ;
          break;
        }
        if (deposit(acc, amount) == SUCCESS) {
          printf("Deposit successful. New balance: %.2f\n", get_balance(acc));
        }
      } else if (userInput == 'w') {
        printf("Enter amount to withdraw: ");
        if (scanf("%f", &amount) != 1) {
          printf("Invalid amount input.\n");
          while (getchar() != '\n')
            ;
          break;
        }
        if (withdraw(acc, amount) == SUCCESS) {
          printf("Withdrawal successful. New balance: %.2f\n",
                 get_balance(acc));
        }
      } else if (userInput == 'p') {
        print_account_details(acc);
      }
      break;

    case 't':
      printf("Enter account number to transfer from: ");
      if (scanf("%d", &accountNumber) != 1) {
        printf("Invalid input for from account.\n");
        while (getchar() != '\n')
          ;
        break;
      }
      acc = find_account(accounts, len, accountNumber);
      if (acc == NULL) {
        printf("Sender Account not found\n");
        break;
      }

      printf("Enter account number to transfer to: ");
      if (scanf("%d", &toAccount) != 1) {
        printf("Invalid input for to account.\n");
        while (getchar() != '\n')
          ;
        break;
      }
      toAcc = find_account(accounts, len, toAccount);
      if (toAcc == NULL) {
        printf("Receiver Account not found\n");
        break;
      }
      printf("Enter transfer amount: ");
      if (scanf("%f", &amount) != 1) {
        printf("Invalid amount input.\n");
        while (getchar() != '\n')
          ;
        break;
      }

      if (transfer(acc, toAcc, amount) == SUCCESS) {
        printf("Transfer successful.\n");
      }
      break;

    case 'e':
      printf("Exiting the program. Thank you!\n");
      exit(0);

    default:
      printf("Invalid option. Please try again.\n");
    }
  }
  return 0;
}
