#include <stdio.h>
#include <math.h>

int main() {
  int first = 0;
  int second = -1;
  int counter = 1;
  while(second < first) {
    first = 100 * (counter * counter);
    second = pow(2, counter);
    counter++;
  }
  dprintf(1, "n = %d\n", counter-1);
  dprintf(1, "100n^2 = %d\n2^n    = %d\n", first, second); 
}
