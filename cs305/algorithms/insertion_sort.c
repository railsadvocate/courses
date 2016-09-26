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
void insertion_sort(int *array, int size);
void print_final_array(int *array, int size);
void parse_line_to_array(int *array, int *array_index, char *line, int num_numbers);

int main(int argc, char **argv) {
  int file_mask = 0;
  int *array = (int *) malloc (sizeof(int) * argc - 1);
  if (argc < 2) {
    fprintf(stderr, "usage: insertion_sort [num1 num2 ... numn] | -f filename\n");
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "-f") == 0) {
    file_mask = file_mask | READ_FROM_FILE;
  }
  
  fill_array(array, argv, argc, file_mask);
  insertion_sort(array, argc-1);
  
  print_final_array(array, argc-1);
  exit(EXIT_SUCCESS);
}

void insertion_sort(int *array, int size) {
  int key, i, j;
  for (j = 1; j < size; j++) {
    key = array[j];
    i = j - 1;
    while (i >= 0 && array[i] > key) {
      array[i+1] = array[i];
      i--;
    }
    array[i+1] = key;
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
  int i, index;
  int num_numbers;
  char *line = (char *) malloc (sizeof(char) * BUFSIZE);
  FILE *file;
  if (flag & READ_FROM_FILE) {
    file = fopen("data", "r");
    fgets(line, BUFSIZE, file);
    num_numbers = atoi(line);
    array = (int *) malloc (sizeof(int) * num_numbers);

    i = index = 0;
    memset(line, 0, BUFSIZE);
    while ((fgets(line, BUFSIZE, file)) != NULL) {
      parse_line_to_array(array, &index, line, num_numbers);
    }
    print_final_array(array, num_numbers);
    if (!feof(file)) {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  else {
    for (i = 1; i < argc; i++) {
      array[i-1] = atoi(argv[i]);
    }
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
