#include <ctype.h>
#include <stdio.h>

typedef struct {
  char name[20];
  int account_number;
  char ifsc[10];
  float balance;
} Account;

typedef enum { SUCCESS, FAIL, PENDING } STATUS;

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

int main(void) {
  Account accounts[] = {{"Ajay Upadhyay", 572002, "ajay572002", 100000.70},
                        {"Satyam", 782010, "saty782010", 696969.69},
                        {"Aman", 782011, "aman782011", 696969.69}};

  int len = sizeof(accounts) / sizeof(accounts[0]);
  char userInput;
  printf("Welcome to the bank!\n\n");

  while (1) {
    printf("\nChoose an appropriate option:\n");
    printf("b: Check balance\n");
    printf("d: Deposit\n");
    printf("w: Withdraw\n");
    printf("t: Transfer\n");
    printf("e: Exit\n");
    printf("Enter your choice: ");
    if (scanf(" %c", &userInput) != 1) {
      printf("Invalid input.\n");
      continue;
    }

    switch (tolower(userInput)) {
    case 'b': {
      printf("Enter account number: ");
      int accountNumber;
      if (scanf("%d", &accountNumber) != 1) {
        printf("Invalid input.\n");
        break;
      }
      if (find_account(accounts, len, accountNumber) == NULL) {
        printf("Account not found.\n");
      }
      for (int i = 0; i < len; i++) {
        if (accounts[i].account_number == accountNumber) {
          printf("Balance for %s: %.2f\n", accounts[i].name,
                 get_balance(&accounts[i]));
          break;
        }
      }
      break;
    }

    case 'd': {
      printf("Enter account number: ");
      int accountNumber;
      if (scanf("%d", &accountNumber) != 1) {
        printf("Invalid input.\n");
        break;
      }
      if (find_account(accounts, len, accountNumber) == NULL) {
        printf("Account not found.\n");
      }
      printf("Enter amount to deposit: ");
      float amount;
      if (scanf("%f", &amount) != 1) {
        printf("Invalid input.\n");
        break;
      }
      for (int i = 0; i < len; i++) {
        if (accounts[i].account_number == accountNumber) {
          if (deposit(&accounts[i], amount) == SUCCESS) {
            printf("Deposit successful. New balance: %.2f\n",
                   get_balance(&accounts[i]));
          }
          break;
        }
      }
      break;
    }

    case 'w': {
      printf("Enter account number: ");
      int accountNumber;
      if (scanf("%d", &accountNumber) != 1) {
        printf("Invalid input.\n");
        break;
      }
      if (find_account(accounts, len, accountNumber) == NULL) {
        printf("Account not found.\n");
      }
      printf("Enter amount to withdraw: ");
      float amount;
      if (scanf("%f", &amount) != 1) {
        printf("Invalid input.\n");
        break;
      }
      for (int i = 0; i < len; i++) {
        if (accounts[i].account_number == accountNumber) {
          if (withdraw(&accounts[i], amount) == SUCCESS) {
            printf("Withdrawal successful. New balance: %.2f\n",
                   get_balance(&accounts[i]));
          }
          break;
        }
      }
      break;
    }

    case 't': {
      printf("Enter account number to transfer from: ");
      int fromAccount;
      if (scanf("%d", &fromAccount) != 1) {
        printf("Invalid input.\n");
        break;
      }
      if (find_account(accounts, len, fromAccount) == NULL) {
        printf("Account not found.\n");
      }
      printf("Enter account number to transfer to: ");
      int toAccount;
      if (scanf("%d", &toAccount) != 1) {
        printf("Invalid input.\n");
        break;
      }
      if (find_account(accounts, len, toAccount) == NULL) {
        printf("Account not found.\n");
      }
      printf("Enter transfer amount: ");
      float amount;
      if (scanf("%f", &amount) != 1) {
        printf("Invalid input.\n");
        break;
      }
      int fromIndex = -1, toIndex = -1;
      for (int i = 0; i < len; i++) {
        if (accounts[i].account_number == fromAccount) {
          fromIndex = i;
        }
        if (accounts[i].account_number == toAccount) {
          toIndex = i;
        }
      }
      if (fromIndex != -1 && toIndex != -1) {
        if (transfer(&accounts[fromIndex], &accounts[toIndex], amount) ==
            SUCCESS) {
          printf("Transfer successful.\n");
        }
      }
      break;
    }

    case 'e':
      printf("Exiting the program. Thank you!\n");
      return 0;

    default:
      printf("Invalid option. Please try again.\n");
    }
  }
}
