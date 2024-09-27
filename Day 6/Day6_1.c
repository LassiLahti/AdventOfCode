#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 255
#define MAX_ARR_SIZE 100

int main() {
    //Initial flush to make sure stdout is empty
    fflush(stdout);

    //Setup for timer and distance
    int timerIndex = 0;
    int distanceIndex = 0;
    char *timer = NULL;
    char *distance = NULL;
    int totalWays = 0;
    int currentWays = 0;
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

            strncpy(timer, separatorPos + 1, separatorLength);
            strncpy(distance, separatorPos + 1, separatorLength);

            char *token = strtok(timer, " ");
            //If on line 1 of file, fill timer array, if 2, fill distance array
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
    for (int i = 0; i < timerIndex; i++) {
        int timeHeld = 0;
        currentWays = 0;
        for (int j = 0; j < timerArr[i]; j++) {
            timeHeld = j;
            int sailTime = timerArr[i] - timeHeld;
            if (timeHeld * sailTime > distanceArr[i]) {
                currentWays += 1;
            }
        }
        if (totalWays == 0) {
            totalWays += currentWays;
        } else {
            totalWays *= currentWays;
        }
    }
    printf("Total winning variations = %d", totalWays);
    fflush(stdout);
}