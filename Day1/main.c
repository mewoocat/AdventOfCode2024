// Run: gcc Day1.c -o Day1; ./Day1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArr(int arr[], int size){
    printf("[ ");
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

int main(int argc, char** argv){
    printf("Advent of Code 2024 Day 1\n");
    
    char* input = argv[1]; // First arg
    printf("Input %s\n", input);

    FILE *fptr; // Pointer to the file
    fptr = fopen("./input.txt", "r"); // Open in the file in read mode

    if(fptr == NULL){
        printf("Error opening file.");
        return -1;
    }

    const int lineSize = 40;
    char lineBuffer[lineSize];
    int lineCount = 0;

    // Calculate how many lines are in the file
    // While a line can be read
    while(fgets(lineBuffer, lineSize, fptr) != NULL){
        lineCount++;
    }
    rewind(fptr); // Reset position inidicator to beginning of the file

    // Initilize both lists using the line count
    // VLA's (Variable Length Arrays) are used here
    int arrayA[lineCount];
    int arrayB[lineCount];

    printf("Size of listA: %d\n", (int)sizeof(arrayA));

    int aNum;
    int bNum;
    int listPos = 0;
    char numBuffer[20];
    char* currentToken;
    char* dataFormat = "%d\t%d\n";
    
    while(fgets(lineBuffer, lineSize, fptr) != NULL){
        // Expected data format
        // num \t num \n    
        //currentToken = strtok(lineBuffer, "\t"); // Read the string of the number for list A

        // Read the values in as numbers
        sscanf(lineBuffer, dataFormat, &aNum, &bNum);
        //printf("a = %d and b = %d\n", aNum, bNum);

        arrayA[listPos] = aNum; 
        arrayB[listPos] = bNum;
        listPos++;
    }
    fclose(fptr); // Close the file

    printf("Num lines: %d\n", lineCount);

    printf("Printing list A...\n");
    printArr(arrayA, lineCount);
    printf("Printing list B...\n");
    printArr(arrayB, lineCount);
    
    return 0;
}
