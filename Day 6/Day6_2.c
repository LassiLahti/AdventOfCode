#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_LINE_LENGTH 255
#define MAX_ARR_SIZE 100

//Function to combine the time and distance arrays
uint64_t concatenate(int arr[], int index) {
    uint64_t realNum = 0;

    for (int i = 0; i < index; i++) {
        if (arr[i] >= 10 && arr[i] < 100) {
            realNum = realNum * 100 + arr[i];
        } else if (arr[i] >= 100 && arr[i] < 1000) {
            realNum = realNum * 1000 + arr[i];
        } else if (arr[i] >= 1000 && arr[i] < 10000) {
            realNum = realNum * 10000 + arr[i];
        }
    }
    return realNum;
}

int main() {
    //Initial flush to make sure stdout is empty
    fflush(stdout);

    //Setup for timer and distance
    int timerIndex = 0;
    int distanceIndex = 0;
    char *timer = NULL;
    char *distance = NULL;
    int timerArr[MAX_ARR_SIZE];
    int distanceArr[MAX_ARR_SIZE];

    //Constant separator to be used by strtok
    const char separator = ':';

    FILE *data = fopen("data.txt", "r");

    if (data == NULL) {
    perror("Error opening the file");
    return 1;
    }

    int linecounter = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), data) != NULL) {
        linecounter++;

        line[strcspn(line, "\n")];

        char *separatorPos = strchr(line, separator);
        if (separatorPos != NULL) {
            int separatorLength = strlen(separatorPos + 1);

            //Bad malloc, these need to be done based on line number
            timer = malloc(separatorLength + 1);
            distance = malloc(separatorLength + 1);

            strncpy(timer, line, separatorPos - line);
            strncpy(distance, separatorPos + 1, separatorLength);

            //If on line 1 of file, fill timer array, if 2, fill distance array
            char *token = strtok(line, " ");
            while (token != NULL) {
                if (isdigit(token[0])) {
                    if (linecounter == 1) {
                        timerArr[timerIndex++] = atoi(token);
                    } else if (linecounter == 2) {
                        distanceArr[distanceIndex++] = atoi(token);
                    } else {
                        printf("Error, linecounter out of range");
                        return -1;
                    }
                }
                token = strtok(NULL, " ");
            }

            //Free allocated memory
            free(timer);
            free(distance);
        }
    }

    //Calculation to check how many variations win
    uint64_t realTime = concatenate(timerArr, timerIndex);
    uint64_t realDistance = concatenate(distanceArr, distanceIndex);
    int totalWays = 0;
    uint64_t timeHeld = 0;

    for (uint64_t j = 0; j < realTime; j++) {
        timeHeld = j;
        long int sailTime = realTime - timeHeld;
        if (timeHeld * sailTime > realDistance) {
            totalWays += 1;
        }
    }

    printf("Total winning variations = %" PRIu64 "\n", totalWays);
    fflush(stdout);
}
