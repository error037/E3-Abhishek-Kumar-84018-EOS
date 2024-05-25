#include <stdio.h>
#include <pthread.h>

// Define the array size
#define ARRAY_SIZE 10

// Function to perform selection sort
void selection_sort(int *array, int size) {
    int i, j, min_idx, temp;
    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < size; j++) {
            if (array[j] < array[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = array[min_idx];
            array[min_idx] = array[i];
            array[i] = temp;
        }
    }
}

// Thread function
void* sort_thread(void *arg) {
    int *array = (int *)arg;
    selection_sort(array, ARRAY_SIZE);
    pthread_exit(NULL);
}

int main() {
    // Initialize the array
    int array[ARRAY_SIZE] = {29, 10, 14, 37, 13, 15, 50, 18, 36, 2};

    // Create the thread
    pthread_t tid;
    pthread_create(&tid, NULL, sort_thread, (void*)array);

    // Wait for the sorting thread to complete
    pthread_join(tid, NULL);

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

