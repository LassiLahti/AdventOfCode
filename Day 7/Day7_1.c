#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_RANKS 13
#define MAX_LIST_LENGTH 2084
#define MAX_ARRAY_SIZE 100

int main(){
    
    char pairArray[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    int pairCountArray[MAX_ARRAY_SIZE];
    int totalWinnings = 0;
    
    // Ranks as characters and integers
    char ranks[MAX_RANKS] = {'2', '3', '4', '5', '6', '7', '8', 
			  '9', 'T', 'J', 'Q', 'K', 'A'};
    
    int rankInt[MAX_RANKS] = {2, 3, 4, 5, 6, 7, 8,
                9, 10, 11, 12, 13, 14};

    FILE *data = fopen("data.txt", "r");

    if (data == NULL) {
        perror("Error opening the file");
        return 1;
    }
    char line[MAX_LINE_LENGTH];
    const char separator = ' ';
    int lineCounter = 0;
    int pairCount = 0;

    while (fgets(line, sizeof(line), data) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        lineCounter++;
        pairCount = 0;
        //Separate current hand from bid
        /*
        char *bidPos = strchr(line, separator);
        int bid = atoi(bidPos);
        char *hand = strtok(line, " ");
        printf("HAND = %s\n", hand);
        printf("BID = %d\n", bid);
        */
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                if(i != j){
                    if(line[i] == line[j]){
                        pairCount++;
                    }
                }else{
                    break;
                }
            }
        }
        size_t lineLength = strlen(line);
        strcpy(pairArray[lineCounter - 1], line);
        pairCountArray[lineCounter - 1] = pairCount;
    }
    for (int i = 0; i <lineCounter; i++){
        printf("Hand and bid = %s, Pairs = %d\n", pairArray[i], pairCountArray[i]);
    }
    int pairsToCheck[] = {0, 1, 2, 3, 4, 6, 10};

    int length = sizeof(pairsToCheck) / sizeof(pairsToCheck[0]);
    for (int pairIndex = 0; pairIndex < length; pairIndex++){
        printf("-----------------------");
        
        int numToCheck = pairsToCheck[pairIndex];
        int handRank = 0;
        int indexesFound[MAX_ARRAY_SIZE];
        int rankIndexCounter[MAX_RANKS];

        int indexCounter = 0;
        printf("CURRENT PAIR AMOUNT = %d\n", numToCheck);
        for (int i = 0; i < lineCounter; i++){
            if(pairCountArray[i] == numToCheck){
                indexesFound[indexCounter++] = i;
                printf("INDEXES = %d\n", i);
            }
            
        }

        for (int i = 0; i < indexCounter; i++){
            char *currentHand = pairArray[indexesFound[i]];
            printf("CURRENT HAND AND BID = %s\n", currentHand);
            for (int j = 0; j < 5; j++){
                int winningFlag = 0;
                printf("character %d of current hand and bid\n", j);
                for (int k = 0; k < indexCounter; k++){
                    if(j != k){

                    }

                }
            }
        }
    }
}