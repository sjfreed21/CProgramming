#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

 
void adminMenu(array * a) {
  int err, opt=3; size_t indexUser; char user[50];
  printf("\nLogin Successful. Please Select from the Options Below:\n\n (1) Add Customer\n\n (2) Delete Customer\n\n (0) Log Out\n\n");
  err = scanf("%d",&opt);
  getchar();
  if(!err || opt > 2 || opt < 0) {printf("Invalid input. Please try again.\n"); adminMenu(a);}
  if(opt == 1) {err = newUser(a); if(err) printf("New User Creation failed.\n"); adminMenu(a);}
  if(opt == 2) {
    printf("Please input username to be deleted: ");
    err = scanf("%50s",user); if(!err) printf("Invalid username input.\n");
    err = checkUsername(a,user,&indexUser); if(err) printf("No username found.\n");
    err = userDelete(a,indexUser);
    if(err) printf("User Deletion failed.\n");
    if(!err) printf("User %s deleted.\n",user);
    adminMenu(a);
  }
  if(!opt) return;
}

int adminPass(array *a) {
  char user[6]; int pass, err;
  printf("Please input admin username and password.\n");
  printf("Username: "); err = scanf("%5s",user);
  if (!err) {printf("Invalid username input.\n"); adminPass(a);}
  if(!strcmp("exit",user)) return 0;
  printf("Password: "); err = scanf("%5d",&pass);
  if (!err) {printf("Invalid password input.\n"); adminPass(a);}
  err = strncmp(user,"Admin",6);
  if (err || pass != 1234) {printf("Incorrect. To return to previous menu, enter \"exit\" for username.");adminPass(a);} //admin fail case
  if (!err && pass == 1234) adminMenu(a);
  return 0;
}

int userMenu(array * a, size_t index) {
  int err, opt; size_t inUse;
  err = arrayNum(a,&inUse); if(err) {printf("Login Failed. No users detected.\n"); return 1;}
  printf("\nLogin Successful. Please Select from the Options Below:\n\n (1) Cash Deposit\n\n (2) Cash Withdrawal\n\n (3) View Customer Information\n\n (4) Edit Customer Information\n\n (5) Cash Transfer\n\n (0) Log Out\n\n");
  err = scanf("%d",&opt); if(!err || opt > 5 || opt < 0) {printf("Invalid input. Please try again.\n"); userMenu(a,index);}
  getchar();
  if(opt == 1) {err = deposit(a,index); if(err) printf("Deposit failed.\n"); userMenu(a,index);}
  if(opt == 2) {err = withdrawal(a,index); if(err) printf("Withdrawal failed.\n"); userMenu(a,index);}
  if(opt == 3) {err = printUserInfo(a,index); if(err) printf("Printing failed.\n"); userMenu(a,index);}
  if(opt == 4) {err = editUser(a,index); if(err) printf("Edit failed.\n"); userMenu(a,index);}
  if(opt == 5 && (int) inUse > 1) {
    char user1[50], user2[50]; size_t index1, index2, amt;
    printf("User transferring money FROM: "); err = scanf("%50s",user1);
    if(!err) printf("Invalid input.\n");
    printf("User transferring money TO: "); err = scanf("%50s",user2);
    if(!err) printf("Invalid input.\n");
    printf("Amount to transfer: "); scanf("%zu",&amt);
    err = checkUsername(a,user1,&index1); if(err) {printf("User 1 Lookup failed.\n");}
    err = checkUsername(a,user2,&index2); if(err) {printf("User 2 Lookup failed.\n");}
    err = cashTransfer(a,index1,index2,amt); if(err) {printf("Transfer failed.\n");}
    else if(!err) printf("Transfer Succesful.\n");
    userMenu(a,index);
  }
  else if(opt == 5 && (int) inUse <= 1) {printf("Unable to transfer funds. Insufficient number of users in the system.\n"); userMenu(a,index);}
  if(!opt) return 0;
  return 0;
}

int userPass(array * a) {
  char user[50]; int pass, err; size_t index;
  printf("Username: "); err = scanf("%50s",user); if(!err) {printf("Invalid username input.\n"); userPass(a);}
  if(!strcmp("exit",user)) return 0;
  printf("\nPassword: "); scanf("%d",&pass); if(!err) {printf("Invalid password input.\n"); userPass(a);}
  err = checkPasswordUsername(a,user,pass,&index);
  if(err) {printf("\nLogin Unsuccessful. Please Try Again. To return to previous menu, enter \"exit\" for username.\n"); userPass(a);}
  if(!err) userMenu(a,index);
  return 0;
}


int main(void){
  int opt, err, ret = 0; array * users = newArray();
  while(!ret){
    err = 0;
    printf("Welcome. Please Select from the Options Below: \n\n (1) Admin Mode\n\n (2) Customer Mode\n\n (0) Shut Down\n\n");
    err = scanf("%1d",&opt); if(!err || opt < -1 || opt > 3) printf("Invalid input. Please try again.\n");
    if(opt == 1) ret = adminPass(users);
    if(opt == 2) ret = userPass(users);
    if(opt == 0) ret = 1;
  }
  printf("Shutting down. Have a nice day!\n");
  deleteArray(users);
  return 0;
}


