#include <stdio.h>
#include <math.h>

int main() {
  int first = -1;
  int second = 0;
  int counter = 4;

  while(first < second) {
    first = 8 * (counter * counter);
    second = 64 * counter * (log((double)counter) / log(2.0));
    counter++;
  }
  dprintf(1, "n = %d\n", counter-1);
  dprintf(1, "8n^2   = %d\n64nlgn = %d\n", first, second);
}
