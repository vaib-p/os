#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortAscending(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void bubbleSortDescending(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of integers: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the integers to be sorted:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { 
        printf("Parent process (PID %d) sorting the integers in ascending order using Bubble Sort...\n", getpid());

        bubbleSortAscending(arr, n);
        displayArray(arr, n);

        
        wait(NULL);

        printf("Parent process (PID %d) exiting.\n", getpid());
    } else { 
        printf("Child process (PID %d) sorting the integers in descending order using Bubble Sort...\n", getpid());

        bubbleSortDescending(arr, n);
        displayArray(arr, n);

        printf("Child process (PID %d) exiting.\n", getpid());

        
        exit(EXIT_SUCCESS);
    }

    return 0;
}

