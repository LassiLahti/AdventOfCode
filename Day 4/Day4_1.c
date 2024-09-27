#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 255
#define MAX_NUM_LENGTH 255

int main() {

  int totalPoints = 0;

  FILE *data = fopen("data.txt", "r");

  if (data == NULL) {
    perror("Error opening the file");
    return 1;
  }

  const char winToken = ':';
  const char cardToken = '|';

  char line[MAX_LINE_LENGTH];
  char *winningNum = NULL;
  char *cardNum = NULL;

  int winningNumInt;
  int cardNumInt;

  int winningnumArr[MAX_NUM_LENGTH];
  int cardNumArr[MAX_NUM_LENGTH];

  while (fgets(line, sizeof(line), data) != NULL) {

    char *winTokenPos = strchr(line, winToken);

    if (winTokenPos != NULL) {

      char *cardTokenPos = strchr(winTokenPos, cardToken);

      if (cardTokenPos != NULL) {

        int winningNumLength = cardTokenPos - winTokenPos - 1;
        int cardnumLength = strlen(cardTokenPos + 1);

        winningNum = malloc(winningNumLength + 1);
        cardNum = malloc(cardnumLength + 1);

        strncpy(winningNum, winTokenPos + 1, winningNumLength);
        strncpy(cardNum, cardTokenPos + 1, cardnumLength);

        int winningIndex = 0;
        int cardIndex = 0;

        char *token = strtok(winningNum, " ");

        while (token != NULL) {
          if (isdigit(token[0])) {
            winningnumArr[winningIndex++] = atoi(token);
          }
          token = strtok(NULL, " ");
        }

        token = strtok(cardNum, " ");
        while (token != NULL) {
          if (isdigit(token[0])) {
            cardNumArr[cardIndex++] = atoi(token);
          }
          token = strtok(NULL, " ");
        }

        int currentCardPoints = 0;
        int winflag = 0;

        for (int i = 0; i < winningIndex; i++) {
          for (int j = 0; j < cardIndex; j++) {
            if (winningnumArr[i] == cardNumArr[j]) {
              if (!winflag) {
                currentCardPoints += 1;
              } else if (winflag) {
                currentCardPoints *= 2;
              }
              winflag = 1;
              break;
            }
          }
        }

        totalPoints += currentCardPoints;
        free(winningNum);
        free(cardNum);
      }
    }
  }
  printf("TOTAL: %d\n", totalPoints);
  fclose(data);
  return 0;
}