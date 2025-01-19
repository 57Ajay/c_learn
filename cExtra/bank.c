#include <stdio.h>

typedef struct {
  char name[20];
  int account_number;
  char ifsc[10];
  float balance;
} Account;

typedef enum { SUCCESS, FAIL, PENDING } STATUS;

float get_balance(Account *account) { return account->balance; }

void deposit(Account *account, float amount) { account->balance += amount; }

void withdraw(Account *account, float amount) { account->balance -= amount; }

void transfer(Account *from, Account *to, float amount) {
  if (from->balance >= amount) {
    from->balance -= amount;
    to->balance += amount;
  }
}

int main(void) {
  Account accounts[] = {{"Ajay Upadhyay", 572002, "ajay572002", 100000.6969},
                        {"Satyam", 782010, "saty782010", 696969.69}};

  float ajay_balance = get_balance(&accounts[0]);
  float satyam_balance = get_balance(&accounts[1]);
  deposit(&accounts[0], 1000);
  float new_ajay_balance = get_balance(&accounts[0]);
  withdraw(&accounts[1], 69.69);
  float new_satyam_balance = get_balance(&accounts[1]);
  transfer(&accounts[0], &accounts[1], 1000);
  float satya_balance_new = get_balance(&accounts[1]);
  printf("All the details are below: \n");
  printf("Ajay's balance: %f\n", ajay_balance);
  printf("Satyam's balance: %f\n", satyam_balance);
  printf("Ajay's new balance: %f\n", new_ajay_balance);
  printf("Satyam's new balance: %f\n", new_satyam_balance);
  printf("Satyam's new balance after transfer: %f\n", satya_balance_new);
  return 0;
}
