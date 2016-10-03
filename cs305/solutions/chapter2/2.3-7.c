/*problem
-------
Describe a O(nlgn)-time algorithm that, given a set S of n integers and another integer x, determines whether or not there exists two elements in S whose sum is exactly x.

S = {1,5,8,15,2,0}
x = 9

set_sum(A, x)
    for i in 0..S.length
    	j = binary_search(A, 0, A.length-1, i, x)
    	if j != -1
       	   return true

binary_search(A, low, high, i, key)
    mid = (low + high) / 2
    j = -1
    if A[mid] + i == key
        return mid
    else
	if (low != mid)
           j = binary_search(A, low, mid, i, x)
	   if (j != -1)
	       return j
        if (high != mid)
           j = binary_search(A, mid+1, high, x)
	   if (j != -1)
	      return j
	return -1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NO_FILE 0
#define READ_FROM_FILE 1
#define SPACE ' '
#define BUFSIZE 1024

/* function definitions */
void fill_array(int *array, char **argv, int argc, int flag);
int set_sum(int *array, int key, int size);
void parse_line_to_array(int *array, int *array_index, char *line, int num_numbers);
int binary_search(int *array, int low, int high, int i, int key);

int main(int argc, char **argv) {
  int file_mask = 0;
  int *array = (int *) malloc (sizeof(int) * argc - 1);
  int result;
  if (argc < 2) {
    fprintf(stderr, "usage: insertion_sort [num1 num2 ... numn] | -f filename\n");
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "-f") == 0) {
    file_mask = file_mask | READ_FROM_FILE;
  }
  
  fill_array(array, argv, argc, file_mask);
  result = set_sum(array, atoi(argv[1]), argc-2);
  if (result != -1) {
    dprintf(1, "The set contains two integers that add up to %d\n", atoi(argv[1]));
  }
  else {
    dprintf(1, "The set does not contain two integers that add up to %d\n", atoi(argv[1]));
  }
  
  exit(EXIT_SUCCESS);
}

int set_sum(int *array, int key, int size) {
  int i;
  int j;
  for (i = 0; i < size; i++) {
    j = binary_search(array, 0, size, i, key);
    if (j != -1) {
      return j;
    }
  }
  return -1;
}

int binary_search(int *array, int low, int high, int i, int key) {
  int mid = (low + high) / 2;
  int j = -1;
  if (array[mid] + i == key) {
    return mid;
  }
  else {
    if (low != mid) {
      j = binary_search(array, low, mid, i, key);
      if (j != -1) {
	return j;
      }
    }
    if (high != mid) {
      j = binary_search(array, mid+1, high, i, key);
      if (j != -1) {
	return j;
      }
    }
    return -1;
  }
}

void print_final_array(int *array, int size) {
  int i;
  dprintf(1, "sorted array = {");
  for (i = 0; i < size; i++) {
    if (i == size - 1) {
      dprintf(1, "%d}\n", array[i]);
    }
    else {
      dprintf(1, "%d, ", array[i]);
    }
  }
}

void fill_array(int *array, char **argv, int argc, int flag) {
  int i;
  for (i = 2; i < argc; i++) {
    array[i-1] = atoi(argv[i]);
  }
}

void parse_line_to_array(int *array, int *array_index, char *line, int num_numbers) {
  char *number;
  int line_index = 0;
  int i;
  for (i = 0; i < num_numbers; i++) {
    dprintf(1, "hi\n");
    number = &line[line_index];
    while(line[line_index] != SPACE) {
      line_index++;
    }
    line[line_index] = '\0';
    dprintf(1, "number = %d\n", atoi(number));
    array[(*array_index)++] = atoi(number);
    line_index++;
  }
}

