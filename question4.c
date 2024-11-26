#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 32  

//ArrayEditor define
typedef struct {
    int data[MAX_SIZE];  // Static array to hold the integers
    int size;            //how many elements are in the array 
} ArrayEditor;

//initialize array
void inArray(ArrayEditor *arr) {
    arr->size = 0;  //initially no elements in array
}

//function to read the array from the file
void readArrayFromFile(ArrayEditor *arr, const char *filename) {
    FILE *file = fopen(filename, "r");

    int element;
    while (fscanf(file, "%d", &element) != EOF) {
        if (arr->size < MAX_SIZE) {
            arr->data[arr->size++] = element;
        } else {
            printf("Array size exceeded the maximum limit.\n");
            break;
        }
    }

    fclose(file);
    printf("Array loaded from %s.\n", filename);
}

//function to write the array to the file
void writeArrayToFile(ArrayEditor *arr, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing.\n", filename);
        exit(1);
    }

    for (int i = 0; i < arr->size; i++) {
        fprintf(file, "%d\n", arr->data[i]);
    }

    fclose(file);
    printf("Array saved to %s.\n", filename);
}

//function to add an element to the array
void addElement(ArrayEditor *arr, int element) {
    if (arr->size < MAX_SIZE) {
        arr->data[arr->size++] = element;
        printf("Element %d added.\n", element);
    } else {
        printf("Array is full! Cannot add more elements.\n");
    }
}

//function to remove an element from the array
void removeElement(ArrayEditor *arr, int element) {
    int i, j;
    for (i = 0; i < arr->size; i++) {
        if (arr->data[i] == element) {
            for (j = i; j < arr->size - 1; j++) {
                arr->data[j] = arr->data[j + 1];  //shift elements left
            }
            arr->size--;  // & decrease the size
            printf("Element %d removed.\n", element);
            return;
        }
    }
    printf("Element %d not found in the array.\n", element);
}

//function to bubble sort the array in ascending order 
void sortArray(ArrayEditor *arr) {
    int temp;
    for (int i = 0; i < arr->size - 1; i++) {
        for (int j = 0; j < arr->size - i - 1; j++) {
            if (arr->data[j] > arr->data[j + 1]) {
                // Swap the elements
                temp = arr->data[j];
                arr->data[j] = arr->data[j + 1];
                arr->data[j + 1] = temp;
            }
        }
    }
    printf("Array sorted.\n");
}

//function to find the maximum value in the array
int findMax(ArrayEditor *arr) {
    if (arr->size == 0) {
        printf("Array is empty.\n");
        return -1;  // Returning -1 to indicate the array is empty
    }
    int max = arr->data[0];
    for (int i = 1; i < arr->size; i++) {
        if (arr->data[i] > max) {
            max = arr->data[i];
        }
    }
    return max;
}

//function to find the minimum value in the array
int findMin(ArrayEditor *arr) {
    if (arr->size == 0) {
        printf("Array is empty.\n");
        return -1;  // Returning -1 to indicate the array is empty
    }
    int min = arr->data[0];
    for (int i = 1; i < arr->size; i++) {
        if (arr->data[i] < min) {
            min = arr->data[i];
        }
    }
    return min;
}

//function to display the array
void displayArray(ArrayEditor *arr) {
    printf("Array contents: ");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}


int main() {
    ArrayEditor editor;
    inArray(&editor);  //initialize the editor

    // Read array from file
    readArrayFromFile(&editor, "arrayEdit.txt");

    int choice, element;

    while (1) {
        printf("\nInteger Array Editor Menu\n");
        printf("1. Add Element\n");
        printf("2. Remove Element\n");
        printf("3. Sort Array\n");
        printf("4. Find Min Value\n");
        printf("5. Find Max Value\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to add: ");
                scanf("%d", &element);
                addElement(&editor, element);
                break;

            case 2:
                printf("Enter the element to remove: ");
                scanf("%d", &element);
                removeElement(&editor, element);
                break;

            case 3:
                sortArray(&editor);
                break;

            case 4:
                element = findMin(&editor);
                if (element != -1)
                    printf("Min value: %d\n", element);
                break;

            case 5:
                element = findMax(&editor);
                if (element != -1)
                    printf("Max value: %d\n", element);
                break;

            case 6:
                //write updated array to file and exit
                writeArrayToFile(&editor, "EditedArray.txt");
                printf("Exiting the program.\n");
                exit(0);
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

        displayArray(&editor);  //show the updated array after each operation
    }

    return 0;
}





