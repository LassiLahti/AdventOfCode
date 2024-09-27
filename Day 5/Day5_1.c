#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_INPUT_LENGTH 100
#define MAX_MAP_ROWS 100
struct Map {
    char rows[MAX_MAP_ROWS][MAX_LINE_LENGTH];
    int row_count;
};

int main() {
    FILE *data = fopen("data.txt", "r");

    if (data == NULL) {
        perror("Error opening the file");
        return 1;
    }

    int seeds[MAX_INPUT_LENGTH];

    struct Map maps[7];
    int mapIndex = -1;
    char line[MAX_LINE_LENGTH];
    int lineCounter = 0;
    int mapline = 0;
    while (fgets(line, sizeof(line), data) != NULL) {
        // Extract the seed numbers
        if (lineCounter == 0) {
            int numCount = 0;
            char *token = strtok(line, " \t\n");
            while (token != NULL) {
                char *endptr;
                int num = strtol(token, &endptr, 10);
                if (*endptr == '\0') {
                    seeds[numCount] = num;
                    numCount++;
                }
                token = strtok(NULL, " \t\n");
            }
            if (numCount == 0) {
                fprintf(stderr, "No integers found in the line: %s", line);
            }
            for (int i = 0; i < numCount; i++){
                printf("SEEDS %d: %d\n",i, seeds[i]);
            }
        }else if (line != NULL){
            while (fgets(line, sizeof(line), data) != NULL) {
                if (strstr(line, "map:") != NULL) {
                    mapIndex++;
                    maps[mapIndex].row_count = 0;
                } else {
                    if (maps[mapIndex].row_count < MAX_MAP_ROWS) {
                        strcpy(maps[mapIndex].rows[maps[mapIndex].row_count], line);
                        maps[mapIndex].row_count++;
                    } else {
                        fprintf(stderr, "Max number of rows exceeded for map %d\n", mapIndex + 1);
                    }
                }
            }
        }

        lineCounter++;
    }

    fclose(data);

    for (int i = 0; i <= mapIndex; i++) {
        int destination, source, length;
        printf("Map %d:\n", i + 1);
        for (int j = 0; j < maps[i].row_count; j++) {
            printf("%s\n", maps[i].rows[j]);
            char *currentRow = maps[i].rows[j];
            if (sscanf(currentRow, "%d %d %d", &destination, &source, &length) == 3) {
                printf("destination %d, source %d, length %d\n", destination, source, length);
            } else {
                fprintf(stderr, "Error parsing line: %s", currentRow);
            }
        }
        printf("\n");
    }


    return 0;
}
