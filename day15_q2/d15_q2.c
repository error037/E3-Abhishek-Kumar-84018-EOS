#include <stdio.h>
#include <pthread.h>

// Define the struct to hold the array and its size
struct array {
    int *arr;
    int size;
};

// Bubble sort function
void bubble_sort(int *arr, int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Thread function to sort the array
void* sort_thread(void *arg) {
    struct array *arr_struct = (struct array*)arg;
    bubble_sort(arr_struct->arr, arr_struct->size);
    pthread_exit(NULL);
}

int main() {
    // Initialize the array
    int arr[] = {29, 10, 14, 37, 13, 15, 50, 18, 36, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    // Create the struct and assign values
    struct array arr_struct;
    arr_struct.arr = arr;
    arr_struct.size = size;

    // Create the thread
    pthread_t tid;
    pthread_create(&tid, NULL, sort_thread, (void*)&arr_struct);

    // Wait for the sorting thread to complete
    pthread_join(tid, NULL);

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}


