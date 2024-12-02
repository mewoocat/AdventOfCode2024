// Compile and run: gcc Day1.c -o Day1; ./Day1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printArr(int* arr, int startIndex, int size){
    printf("[ ");
    for (int i = startIndex; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void swapArrElements(int* arr, int indexA, int indexB){
    // Swap value at left index with value at right index
    int temp = arr[indexA];
    arr[indexA] = arr[indexB];
    arr[indexB] = temp;
}

int hoarePartition(int* arr, int leftBound, int rightBound){
    printf("Entering hoarePartition...\n");

    int pivotIndex = leftBound; // Pivot around first element
    int pivot = arr[pivotIndex];
    int leftIndex = leftBound + 1;
    int rightIndex = rightBound;

    printArr(arr, leftBound, rightBound + 1);
    
    // Paritioning
    // Moving all elements lesser than the pivot to the left of it and all
    // elements greater than the pivot to the right of it
    while(leftIndex < rightIndex){
        //sleep(1);
        printf("Left-starting: %d, Right-starting: %d\n", leftIndex, rightIndex);
        printf("leftIndex value: %d\n", arr[leftIndex]);
        printf("rightIndex value: %d\n", arr[rightIndex]);
        printf("pivotIndex value: %d\n", pivot);
        while(arr[leftIndex] <= pivot && leftIndex < rightBound){
            leftIndex++;
            printf("Left index is now %d\n", leftIndex);
        }
        while(arr[rightIndex] > pivot && rightIndex > leftBound){
            rightIndex--;
            printf("Right index is now %d\n", rightIndex--);
        }
        // Now the left and right indexes should either be poiting to 
        // elements that need to be swaped or they have crossed meaning
        // that the left and right side of the array are already sorted
        printf("Done searching indexes\n");

        // If indexes haven't crossed 
        if(leftIndex < rightIndex){
            printf("Indexes have not crossed\n");
            printf("Swapping %d with %d\n", arr[leftIndex], arr[rightIndex]);
            // Swap value at left index with value at right index
            swapArrElements(arr, leftIndex, rightIndex);
        }
    }
    // Swap pivot with element at right index
    if(arr[rightIndex] < pivot){
        swapArrElements(arr, pivotIndex, rightIndex);
    }

    // The new index where the pivot was placed
    int splitIndex = rightIndex;

    // Base case
    // If array has 1 or 0 elements
    return splitIndex;
}

// Sorts the array from lowest to highest using Quick Sort
void sortArr(int* arr, int leftBound, int rightBound){
    if (leftBound < rightBound){
        int splitIndex = hoarePartition(arr, leftBound, rightBound);
        // Recursive call 
        printf("Sorting left\n");
        sortArr(arr, leftBound, splitIndex - 1);
        printf("Sorting right\n");
        sortArr(arr, splitIndex + 1, rightBound);
    }
}

int main(int argc, char** argv){
    printf("Advent of Code 2024 Day 1\n");
    
    char* input = argv[1]; // First arg
    printf("Input %s\n", input);

    FILE *fptr; // Pointer to the file
    fptr = fopen("./input2.txt", "r"); // Open in the file in read mode

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
    printArr(arrayA, 0, lineCount);
    printf("Printing list B...\n");
    printArr(arrayB, 0, lineCount);
    
    /*
    printf("Printing list A modified...\n"); 
    swapArrElements(arrayA, 0, 1);
    */

    printf("Sorting arrays\n");

    sortArr(arrayA, 0, lineCount - 1);
    printf("Printing list A sorted...\n");
    printArr(arrayA, 0, lineCount);

    sortArr(arrayB, 0, lineCount - 1);
    printf("Printing list B...\n");
    printArr(arrayB, 0, lineCount);

    int total = 0;

    for (int i = 0; i < lineCount; i++){
        total += abs(arrayA[i] - arrayB[i]);
    }

    printf("Result: %d\n", total);
    
    return 0;
}
