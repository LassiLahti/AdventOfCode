#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
int main() {
  int total = 0;

  FILE *data = fopen("data.txt", "r");

  if (data == NULL) {
    perror("Error opening the file");
    return 1;
  }

  char **inputmatrix = NULL;
  char line[MAX_LINE_LENGTH];
  int row = 0, max_cols = 0;

  while (fgets(line, sizeof(line), data) != NULL) {

    line[strcspn(line, "\n")];

    char *new_row = strdup(line);

    if (new_row == NULL) {
      perror("Memory allocation error");
      fclose(data);
      for (int i = 0; i < row; i++) {
        free(inputmatrix[i]);
      }
      free(inputmatrix);
      return 1;
    }

    inputmatrix = realloc(inputmatrix, (row + 1) * sizeof(char *));
    inputmatrix[row] = new_row;

    int cols = strlen(line);
    if (cols > max_cols) {
      max_cols = cols;
    }

    row++;
  }
  fclose(data);
  // Check if input matrix has any symbol before, after, diagonal to, above or
  // under a number sequence
  for (int i = 0; i < row - 1; i++) {

    for (int j = 0; j < max_cols - 1; j++) {

      if (!isalnum(inputmatrix[i][j]) && inputmatrix[i][j] != '.') {
        // Check middles first so we know if there is a number before or after
        // left and right cases
        // top middle
        if (isdigit(inputmatrix[i - 1][j])) {
          int adder = 0;
          int k = j;
          int reversedNumber = 0;
          // If top right is a number but top left is not
          if (isdigit(inputmatrix[i - 1][j + 1]) &&
              !isdigit(inputmatrix[i - 1][j - 1])) {
            while (isdigit(inputmatrix[i - 1][k])) {
              adder = adder * 10 + (inputmatrix[i - 1][k++] - '0');
            }
          } else if (isdigit(inputmatrix[i - 1][j - 1]) &&
                     !isdigit(inputmatrix[i - 1][j + 1])) {
            while (isdigit(inputmatrix[i - 1][k])) {
              reversedNumber =
                  reversedNumber * 10 + (inputmatrix[i - 1][k--] - '0');
            }
            int originalNumber = 0;
            while (reversedNumber > 0) {
              originalNumber = originalNumber * 10 + reversedNumber % 10;
              reversedNumber /= 10;
            }
            adder = originalNumber;
          } else if (isdigit(inputmatrix[i - 1][j - 1]) &&
                     isdigit(inputmatrix[i - 1][j + 1])) {
            k = j - 1;
            while (isdigit(inputmatrix[i - 1][k])) {
              adder = adder * 10 + (inputmatrix[i - 1][k++] - '0');
            }
          }
          total += adder;
          // printf("FROM TOP MIDDLE total now : %d\n", total);
        }

        // bottom middle
        if (isdigit(inputmatrix[i + 1][j])) {
          int adder = 0;
          int k = j;
          int reversedNumber = 0;
          // If top right is a number but top left is not
          if (isdigit(inputmatrix[i + 1][j + 1]) &&
              !isdigit(inputmatrix[i + 1][j - 1])) {
            while (isdigit(inputmatrix[i + 1][k])) {
              adder = adder * 10 + (inputmatrix[i + 1][k++] - '0');
            }
          } else if (isdigit(inputmatrix[i + 1][j - 1]) &&
                     !isdigit(inputmatrix[i + 1][j + 1])) {
            while (isdigit(inputmatrix[i + 1][k])) {
              reversedNumber =
                  reversedNumber * 10 + (inputmatrix[i + 1][k--] - '0');
            }
            int originalNumber = 0;
            while (reversedNumber > 0) {
              originalNumber = originalNumber * 10 + reversedNumber % 10;
              reversedNumber /= 10;
            }
            adder = originalNumber;
          } else if (isdigit(inputmatrix[i + 1][j - 1]) &&
                     isdigit(inputmatrix[i + 1][j + 1])) {
            k = j - 1;
            while (isdigit(inputmatrix[i + 1][k])) {
              adder = adder * 10 + (inputmatrix[i + 1][k++] - '0');
            }
          }
          total += adder;
          // printf("FROM BOTTOM MIDDLE total now : %d\n", total);
        }

        // top left
        if (isdigit(inputmatrix[i - 1][j - 1])) {
          if (inputmatrix[i - 1][j] == '.') {
            int k = j - 1;
            int reversedNumber = 0;
            while (isdigit(inputmatrix[i - 1][k])) {
              reversedNumber =
                  reversedNumber * 10 + (inputmatrix[i - 1][k--] - '0');
            }
            int originalNumber = 0;
            while (reversedNumber > 0) {
              originalNumber = originalNumber * 10 + reversedNumber % 10;
              reversedNumber /= 10;
            }
            total += originalNumber;
          }
          // printf("FROM TOP LEFT total now : %d\n", total);
        }

        // top right
        if (isdigit(inputmatrix[i - 1][j + 1])) {
          if (inputmatrix[i - 1][j] == '.') {
            int k = j + 1;
            int adder = 0;
            while (isdigit(inputmatrix[i - 1][k])) {
              adder = adder * 10 + (inputmatrix[i - 1][k++] - '0');
            }
            total += adder;
          }
          // printf("FROM TOP RIGHT total now : %d\n", total);
        }

        // left
        if (isdigit(inputmatrix[i][j - 1])) {
          int k = j - 1;
          int reversedNumber = 0;
          while (isdigit(inputmatrix[i][k])) {
            reversedNumber = reversedNumber * 10 + (inputmatrix[i][k--] - '0');
          }
          int originalNumber = 0;
          while (reversedNumber > 0) {
            originalNumber = originalNumber * 10 + reversedNumber % 10;
            reversedNumber /= 10;
          }
          total += originalNumber;
          // printf("FROM LEFT total now : %d\n", total);
        }

        // right
        if (isdigit(inputmatrix[i][j + 1])) {
          int k = j + 1;
          int adder = 0;
          while (isdigit(inputmatrix[i][k])) {
            adder = adder * 10 + (inputmatrix[i][k++] - '0');
          }
          total += adder;
          // printf("FROM RIGHT total now : %d\n", total);
        }
        // bottom left
        if (isdigit(inputmatrix[i + 1][j - 1])) {
          if (inputmatrix[i + 1][j] == '.') {
            int k = j - 1;
            int reversedNumber = 0;
            while (isdigit(inputmatrix[i + 1][k])) {
              reversedNumber =
                  reversedNumber * 10 + (inputmatrix[i + 1][k--] - '0');
            }
            int originalNumber = 0;
            while (reversedNumber > 0) {
              originalNumber = originalNumber * 10 + reversedNumber % 10;
              reversedNumber /= 10;
            }
            total += originalNumber;
            // printf("FROM BOTTOM LEFT total now : %d\n", total);
          }
        }
        // bottom right
        if (isdigit(inputmatrix[i + 1][j + 1])) {
          if (inputmatrix[i + 1][j] == '.') {
            int k = j + 1;
            int adder = 0;
            while (isdigit(inputmatrix[i + 1][k])) {
              adder = adder * 10 + (inputmatrix[i + 1][k++] - '0');
            }
            total += adder;
          }
          // printf("FROM BOTTOM RIGHT total now : %d\n", total);
        }
      }
    }
  }

  printf("TOTAL : %d", total);
  free(inputmatrix);

  return 0;
}
