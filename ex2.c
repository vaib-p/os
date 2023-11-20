#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  
    char *sortedArray = argv[1];
    int n=sizeof(sortedArray);
    printf("Reversed Array of Sorted Array: ");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", sortedArray[i]);
    }
    printf("\n");

    return 0;
}

