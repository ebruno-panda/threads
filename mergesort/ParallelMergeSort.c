#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100

int array[SIZE];

void fillArrayWithRandomNumbers(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) array[i] = rand()%100;
}

void printArray(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) printf("%5d", arr[i]);
    printf("\n");
}

typedef struct StartEndIndexes {
    int start;
    int end;
} StartEndIndexes;

// Merges two subarrays arr[l..m] and arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    // Merge operation implementation
}

// Recursive function to perform merge sort on the array segment
void mergeSort(int arr[], int l, int r) {
    // Merge sort implementation
}

// Wrapper function for pthread creation
void* mergeSortThread(void* args) {
    StartEndIndexes* sei = (StartEndIndexes*)args;
    mergeSort(array, sei->start, sei->end);
    return NULL;
}

// Perform parallel merge sort using pthreads
void parallelMergeSort(int threads) {
    pthread_t thread_ids[threads];
    StartEndIndexes sei[threads];
    
    // Divide the array into equal segments for each thread
    int segment_size = SIZE / threads;
    for (int i = 0; i < threads; i++) {
        sei[i].start = i * segment_size;
        sei[i].end = (i == threads - 1) ? SIZE - 1 : (i + 1) * segment_size - 1;
        pthread_create(&thread_ids[i], NULL, mergeSortThread, (void*)&sei[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    // Merge the sorted segments
    for (int i = 1; i < threads; i++) {
        int mid = i * segment_size - 1;
        merge(array, 0, mid, sei[i].end);
    }
}

int main() {
    srand(time(0));
    StartEndIndexes sei;
    sei.start = 0;
    sei.end = SIZE - 1;
    
    // 1. Fill array with random numbers.
    fillArrayWithRandomNumbers(array);
    
    // 2. Print the array.
    printf("Unsorted array: ");
    printArray(array);
    
    // 3. Create and run parallel merge sort with 2 threads.
    int threads = 2;
    parallelMergeSort(threads);
    
    // 4. Print the sorted array.
    printf("Sorted array:   ");
    printArray(array);

    return 0;
}
