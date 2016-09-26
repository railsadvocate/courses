#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void fill_array(int *array, char **numbers, int size);
void mergesort(int *array, int p, int r);
void merge(int *array, int p, int q, int r);
void print_results(int *array, int size);
void append_array(int *master, int *temp, int master_index, int temp_index);

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage: ./mergersort num1 [num2 num2 ... ]");
    exit(EXIT_FAILURE);
  }

  int *array = (int *) malloc (sizeof(int) * argc-1);
  fill_array(array, argv, argc-1);

  mergesort(array, 0, argc-1);
  print_results(array, argc-1);
}

void mergesort(int *array, int p, int r) {
  int q;
  if (p < r) {
    q = r / 2;
    mergesort(array, p, q);
    mergesort(array, q+1, r);
    merge(array, p, q, r);
  }
}

void merge(int *array, int p, int q, int r) {
  int counter;
  int left[q-p+2];
  int right[r-q+1];
  int i, j;
  for (i = 0; i < q-p+1; i++) {
    left[i] = array[i];
  }
  for (j = 0; j < r-q; j++) {
    right[j] = array[i++];
  }
  left[q-p+1] = INT_MAX;
  right[r-q] = INT_MAX;
  i = j = 0;
  counter = p;
  while (left[i] != INT_MAX && right[j] != INT_MAX) {
    if (left[i] < right[j]) {
      array[counter++] = left[i++];
    }
    else {
      array[counter++] = right[j++];
    }
  }
  if (left[i] == INT_MAX) {
    append_array(array, right, counter, j);
  }
  else {
    append_array(array, left, counter, i);
  }
}

void append_array(int *master, int *temp, int master_index, int temp_index) {
  while (temp[temp_index] != INT_MAX) {
    master[master_index++] = temp[temp_index++];
  }
}

void fill_array(int *array, char **numbers, int size) {
  int i;
  for (i = 1; i < size; i++) {
    array[i-1] = atoi(numbers[i]);
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
