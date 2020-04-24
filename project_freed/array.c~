#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

struct _array {
  size_t capacity; /* elements allocated */
  size_t inUse;    /* elements currently in use */
  user * data;    /* actual data */
};

struct _user {
  char name[50];
  char address[50];
  int age;
  long int phone_num;
  double balance;
  char username[50];
  int password;
  double account_num;
};

array * newArray(void) {
  array * a;
  a = (array *) malloc(sizeof(array));
  if (!a) return NULL;
  a->capacity = 1; /* parsimonious */
  a->inUse = 0;
  a->data = (user *) malloc(sizeof(user) * a->capacity);
  if (!a->data) {
    free(a);
    return NULL;
  }
  return a;
}

void deleteArray(array * a) {
  if (a) {
    free(a->data);
    free(a);
  }
}

int resizeArray(array * a, size_t newSize) {
  if (!a) return -1;
  if (newSize > a->capacity) {
    /* To avoid too many calls to realloc, we choose the larger of
     * twice the current size and the new requested size. */
    size_t newCapacity = 2 * a->capacity;
    if (newCapacity < newSize)
      newCapacity = newSize;
    user * tmp = (user *) realloc(a->data, newCapacity * sizeof(user));
    /* If the allocation fails, leave the array alone. */
    if (!tmp) return -1;
    a->data = tmp;
    a->capacity = newCapacity;
  }
  /* Here we are guaranteed that newSize <= a->capacity. */
  a->inUse = newSize;
  return 0;
}

int arrayNum(array const * a, size_t * num) {
  if (!a || !num) return -1;
  *num = a->inUse;
  return 0;
}

int arrayPushBack(array * a, user e) {
  if (!a) return -1;
  if (resizeArray(a, a->inUse + 1)) return -1;
  /* Now we have space. */
  a->data[a->inUse-1] = e;
  return 0;
}

int newUser(array * a){
  if(!a) return -1;
  user * e = malloc(sizeof(user)); int err;
  if(!e) return -1;
  printf("Legal name: "); err = scanf("%50[^\n]s",e->name); getchar(); if(!err) return -1;
  printf("Address: "); err = scanf("%50[^\n]s",e->address); getchar(); if(!err) return -1;
  printf("Age: "); err = scanf("%2d",&e->age); if(!err) return -1;
  printf("Phone Number: "); err = scanf("%10ld",&e->phone_num); if(!err) return -1;
  e->balance = 0;
  printf("Username: "); err = scanf("%50s",e->username); if(!err) return -1;
  printf("Password (must be digits only): "); err = scanf("%d",&e->password); if (!err) return -1;
  e->account_num = (e->phone_num * 5) / 2;
  err = arrayPushBack(a,*e); if(err) return -1;
  return 0;
}

int printUserInfo(array * a, size_t indexUser){
  if (!a || (int) indexUser < 0) return -1;
  printf("Legal name: %s\n",a->data[indexUser].name);
  printf("Address: %s\n",a->data[indexUser].address);
  printf("Age: %d \n",a->data[indexUser].age);
  printf("Phone Number: %ld \n",a->data[indexUser].phone_num);
  printf("Balance: $%f \n",a->data[indexUser].balance);
  printf("Username: %s \n",a->data[indexUser].username);
  printf("Account Number: %10f \n\n", a->data[indexUser].account_num);
  printf("Press enter to return to menu. ");
  char scan; if(scanf("%c",&scan)) return 0;
  return 0;
}

int checkPasswordUsername(array * a, char * user, int pass, size_t * indexUser){
  if(!a || !user || !indexUser) return -1;
  size_t tail;
  for(tail = 0; tail <=  a->inUse; tail++){
    int check1 = strcmp(user,a->data[tail].username);
    int check2 = (pass == a->data[tail].password);
    if(!check1 && check2) {*indexUser = tail; return 0;}
  }
  return -1;
}

int checkUsername(array * a, char * user, size_t * indexUser){
  if(!a || !user || !indexUser) return -1;
  size_t tail;
  for(tail = 0; tail <= a->inUse; tail++){
    int check = strcmp(user, a->data[tail].username);
    if(!check) {*indexUser = tail; return 0;}
  }
  return -1;
}

int userBalanceGet(array * a, size_t indexUser, size_t * balance){
  if(!a || (int) indexUser < 0) return -1;
  *balance = a->data[indexUser].balance;
  return 0;  
}

int userBalancePut(array * a, size_t indexUser, int amount){
  if(!a || (int) indexUser < 0) return -1;
  a->data[indexUser].balance = amount;
  return 0;
}

int editUser(array * a, size_t indexUser){
  if(!a || (int) indexUser < 0) return -1;
  user * e = &a->data[indexUser]; int pass, err;
  printf("Please re-enter password for security check: "); scanf("%d",&pass); getchar();
  if(pass != e->password) {printf("Incorrect password, please try again.\n"); editUser(a,indexUser);}
  printf("New address: "); err = scanf("%50[^\n]s",e->address); getchar(); if(!err) return -1;
  printf("New phone number: "); err = scanf("%10ld",&e->phone_num); if(!err) return -1;
  printf("New username: "); err = scanf("%50s",e->username); if(!err) return -1;
  printf("New password (must be digits only): "); err = scanf("%d",&e->password); if(!err) return -1;
  e->account_num = (e->phone_num * 5) / 2;
  return 0;
}

int cashTransfer(array * a, size_t indexUser1, size_t indexUser2, size_t amount){
  if(!a || (int) indexUser1 < 0 || (int) indexUser2 < 0) return -1;
  a->data[indexUser1].balance -= (long) amount;
  a->data[indexUser2].balance += (long) amount;
  return 0;
}

int userDelete(array * a, size_t indexUser){
  if(!a || (int) indexUser < 0 || (int) indexUser > (int) a->inUse) return -1;
  size_t i;
  for(i = indexUser; i < a->inUse; i++){
    user * user1 = &a->data[i];
    user * user2 = &a->data[i+1];
    strcpy(user1->name,user2->name);
    strcpy(user1->address,user2->address);
    user1->age = user2->age;
    user1->phone_num = user2->phone_num;
    user1->balance = user2->balance;
    strcpy(user1->username,user2->username);
    user1->password = user2->password;
    user1->account_num = user2->account_num;
  }
  a->inUse--;
  return 0;
}

int deposit(array * a, size_t indexUser){
  if(!a || (int) indexUser < 0) return -1;
  size_t bal; long amt; int err;
  userBalanceGet(a,indexUser,&bal);
  printf("Your current balance is $%zu.\nHow much would you like to deposit? ",bal);
  scanf("%ld",&amt);
  if(amt < 0){
    printf("Invalid input. Balance cannot be negative.\n");
    err = deposit(a,indexUser); if(!err) return 0;
  }
  userBalancePut(a,indexUser,(long) bal+amt);
  printf("Your new balance is $%ld.\n\n",(long) bal+amt);
  return 0;
}

int withdrawal(array * a, size_t indexUser){
  if(!a || (int) indexUser < 0) return -1;
  size_t bal; long amt; int err;
  userBalanceGet(a,indexUser,&bal);
  printf("Your current balance is $%zu.\nHow much would you like to withdraw? ",bal);
  scanf("%ld",&amt);
  if(amt > (long) bal){
    printf("Invalid input. Balance cannot be negative.\n");
    err = withdrawal(a,indexUser); if(!err) return 0;
  }
  userBalancePut(a,indexUser,(long) bal-amt);
  printf("Your new balance is $%ld.\n\n",(long) bal-amt);
  return 0;
}
  
