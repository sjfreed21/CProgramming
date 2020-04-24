#ifndef ARRAY_H_
#define ARRAY_H_

typedef struct _array array;
typedef struct _user user;

/* Return a new array with no elements.
 * Return NULL if creation fails. */
array * newArray(void);
/* Free array a. */
void deleteArray(array * a);
/* Change the size of array a.
 * Return 0 if successful and -1 if resizing fails. */
int resizeArray(array * a, size_t newSize);
/* Write the size of array a to the location pointed by num.
 * Return 0 if succesful and -1 if a is an invalid pointer. */
int arrayNum(array const * a, size_t * num);
/* Add element e at the end of array a.  Return 0 if
 * successful and -1 otherwise. */
int arrayPushBack(array * a, user e);
/* Creates the new user and calls arrayPushBack. Returns 0 if 
 * successful and -1 if array a is invalid.*/
int newUser(array * a);
/* Prints the user at a->data[indexUser]'s information. Returns 0 if 
 * successful and -1 if array a or indexUser is invalid. */
int printUserInfo(array * a, size_t indexUser);
/* Scans through array a to find the index of the user whose username/password
 * matches the input. Returns 0 if successful or -1 if input is invalid or no user
 * can be found. */
int checkPasswordUsername(array * a, char * user, int pass, size_t * indexUser);
/* Scans through array a to find the index of the user whose username matches
 * the input. Returns 0 if successful or -1 if input is invalid or no user can be
 * found. */
int checkUsername(array * a, char * user, size_t * indexUser);
/* Retrieves the balance of the user at the given index. Returns 0 if successful or
 * -1 for malformed input. */
int userBalanceGet(array * a, size_t indexUser, size_t * balance);
/* Puts the input value into the balance of the user at the given index. Returns 0 if
 * successful or -1 for malformed input. */
int userBalancePut(array * a, size_t indexUser, int amount);
/* Allows an existing user to overwrite their old information. Returns 0 if successful
 * or -1 for malformed input. */
int editUser(array * a, size_t indexUser);
/* Transfers the amount input FROM user 1 TO user 2. Returns 0 if successful or -1
 * for malformed input. */
int cashTransfer(array * a, size_t indexUser1, size_t indexUser2, size_t amount);
/* Deletes the user at the given index. Returns 0 if successful or -1 for malformed
 * input. */
int userDelete(array * a, size_t indexUser);
/* Directly deposits the scanned (stdin) amount into the account of the user at the given index.
 * Returns 0 if successful or -1 for malformed input. */
int deposit(array * a, size_t indexUser);
/* Directly withdraws the scanned (stdin) amount from the account of the user at the given index.
 * Returns 0 if successful or -1 for malformed input. */
int withdrawal(array * a, size_t indexUser);
#endif
