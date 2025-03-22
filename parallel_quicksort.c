#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Swap function for Quicksort
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for Quicksort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Serial Quicksort function
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Merge function for combining sorted subarrays
void merge(int* arr, int* left, int left_size, int* right, int right_size) {
    int i = 0, j = 0, k = 0;
    
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    
    while (i < left_size) arr[k++] = left[i++];
    while (j < right_size) arr[k++] = right[j++];
}

// Parallel Quicksort using MPI
void parallelQuicksort(int* arr, int size, int rank, int num_procs) {
    int local_size = size / num_procs;
    int* local_array = (int*)malloc(local_size * sizeof(int));
    
    // Scatter data from master to all processes
    MPI_Scatter(arr, local_size, MPI_INT, local_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    // Each process sorts its local portion
    quicksort(local_array, 0, local_size - 1);
    
    // Gather sorted subarrays at root process
    MPI_Gather(local_array, local_size, MPI_INT, arr, local_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    // Final merge at root process
    if (rank == 0) {
        int* sorted_array = (int*)malloc(size * sizeof(int));
        int* temp = (int*)malloc(size * sizeof(int));
        
        for (int i = 0; i < size; i++) temp[i] = arr[i];

        for (int step = local_size; step < size; step *= 2) {
            for (int i = 0; i < size; i += 2 * step) {
                if (i + step < size) {
                    merge(temp + i, arr + i, step, arr + i + step, step);
                }
            }
            for (int i = 0; i < size; i++) arr[i] = temp[i];
        }

        free(sorted_array);
        free(temp);
    }

    free(local_array);
}

int main(int argc, char* argv[]) {
    int rank, num_procs, size = 16;
    int arr[16] = {34, 7, 23, 32, 5, 62, 32, 43, 1, 9, 45, 99, 12, 56, 78, 11};
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (rank == 0) {
        printf("Unsorted array: ");
        for (int i = 0; i < size; i++) printf("%d ", arr[i]);
        printf("\n");
    }

    parallelQuicksort(arr, size, rank, num_procs);

    if (rank == 0) {
        printf("Sorted array: ");
        for (int i = 0; i < size; i++) printf("%d ", arr[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

