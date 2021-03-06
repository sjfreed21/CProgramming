#include <stdio.h>
#include <assert.h>

int minmax(int x, int y, int *min, int *max) {
  if (min == NULL || max == NULL)
    return -1;
  else
    if (x < y) {
      *min = x;
      *max = y;
      return 0;
    }
    else {
      *min = y;
      *max = x;
      return 0;
    }
}

int main(void) {
  int a, b;
  int rv = minmax(1,10,&a,&b);
  assert(rv == 0 && a < b);
  int c = NULL, d = NULL;
  rv = minmax(2,5,c,d);
  assert(rv == -1);
  rv = minmax(-19,18,&a,&b);
  assert(rv == 0 && a < b);
  rv = minmax(-175,-14,&a,&b);
  assert(rv == 0 && a < b); 
  printf("All Clear \n");
}
