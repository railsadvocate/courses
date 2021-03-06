#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void fill_array(int *array, char **numbers, int size);
void merge_sort(int *array, int p, int r);
void _merge(int *array, int p, int q, int r);
void print_results(int *array, int size);

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage: ./mergersort num1 [num2 num2 ... ]");
    exit(EXIT_FAILURE);
  }

  int *array = (int *) malloc (sizeof(int) * argc-1);
  fill_array(array, argv, argc-1);

  merge_sort(array, 0, argc-2);
  print_results(array, argc-1);
}

void merge_sort(int *array, int p, int r) {
  int q;
  if (p < r) {
    q = (p+r) / 2;
    merge_sort(array, p, q);
    merge_sort(array, q+1, r);
    _merge(array, p, q, r);
  }
}

void _merge(int *array, int p, int q, int r) {
  int counter;
  int left_size = q-p+1;
  int right_size = r-q;
  int left[left_size + 1];
  int right[right_size + 1];
  int i, j;
  for (i = 0; i < left_size; i++) {
    left[i] = array[p+i];
  }
  for (j = 0; j < right_size; j++) {
    right[j] = array[q+j+1];
  }
  left[left_size] = INT_MAX;
  right[right_size] = INT_MAX;
  i = j = 0;
  for (counter = p; counter < r + 1; counter++) {
    if (left[i] < right[j]) {
      array[counter] = left[i];
      i++;
    }
    else {
      array[counter] = right[j];
      j++;
    }
  }
}

void fill_array(int *array, char **numbers, int size) {
  int i;
  for (i = 0; i < size; i++) {
    array[i] = atoi(numbers[i+1]);
  }
}

void print_results(int *array, int size) {
  int i;
  dprintf(1, "sorted array = {");
  for (i = 0; i < size-1; i++) {
    dprintf(1, "%d,", array[i]);
  }
  dprintf(1, "%d}\n", array[i]);
}
