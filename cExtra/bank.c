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

int main(void) {
  Account accounts[] = {{"Ajay Upadhyay", 572002, "ajay572002", 100000.70},
                        {"Satyam", 782010, "saty782010", 696969.69}};

  printf("Initial balances:\n");
  printf("Ajay's balance: %.2f\n", get_balance(&accounts[0]));
  printf("Satyam's balance: %.2f\n\n", get_balance(&accounts[1]));

  if (deposit(&accounts[0], 1000) == SUCCESS) {
    printf("Deposit successful. Ajay's new balance: %.2f\n",
           get_balance(&accounts[0]));
  }

  if (withdraw(&accounts[1], 69.69) == SUCCESS) {
    printf("Withdrawal successful. Satyam's new balance: %.2f\n",
           get_balance(&accounts[1]));
  }

  if (transfer(&accounts[0], &accounts[1], 1000) == SUCCESS) {
    printf("Transfer successful.\n");
    printf("Ajay's balance after transfer: %.2f\n", get_balance(&accounts[0]));
    printf("Satyam's balance after transfer: %.2f\n",
           get_balance(&accounts[1]));
  }

  return 0;
}
