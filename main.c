#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTS 100
#define HYBRID_THRESHOLD 10

void performBubbleSort(int numbers[], int count, int *passCount);
void performSelectionSort(int numbers[], int count, int *passCount);
void performInsertionSort(int numbers[], int count, int *passCount);
void quickSort(int numbers[], int start, int end, int *steps);
int partitionArray(int numbers[], int start, int end, int *steps);
void mergeSort(int numbers[], int left, int right, int *passCount);
void merge(int numbers[], int left, int mid, int right, int *passCount);
void heapSort(int numbers[], int count, int *passCount);
void createHeap(int numbers[], int count, int root);
void hybridSort(int numbers[], int left, int right, int *passCount);
void insertionSortForHybrid(int numbers[], int left, int right, int *passCount);
int validateSize(int size);
int processInput(char *rawInput, int numbers[], int count);
void waitForEnter();

int main() {
    printf("==========================================\n");
    printf("John Austin L. Gonzales | BSIT 2-4\n");
    printf("Machine Problem: Sorting Algorithms\n");
    printf("==========================================\n\n");

    int selection, total, passCount = 0;
    int numbers[MAX_ELEMENTS];
    char inputBuffer[1024];

    while (1) {
        printf("Choose a Sorting Algorithm:\n");
        printf("[1] Bubble Sort\n");
        printf("[2] Selection Sort\n");
        printf("[3] Insertion Sort\n");
        printf("[4] Merge Sort\n");
        printf("[5] Quick Sort\n");
        printf("[6] Heap Sort\n");
        printf("[7] Hybrid Sort\n");
        printf("------------------------------------------\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &selection);

        if (selection >= 1 && selection <= 7) {
            break;
        } else {
            printf("\nError: Invalid choice. Please try again.\n\n");
        }
    }

    while (1) {
        printf("\nHow many numbers do you want to sort? ");
        scanf("%d", &total);

        if (validateSize(total)) {
            break;
        } else {
            printf("\nError: Invalid size. Must be greater than 1.\n");
        }
    }

    printf("\nInput %d numbers separated by spaces: ", total);
    getchar();
    fgets(inputBuffer, sizeof(inputBuffer), stdin);

    if (!processInput(inputBuffer, numbers, total)) {
        printf("\nError: Invalid input. Please ensure you provide exactly %d numbers.\n", total);
        return 1;
    }

    printf("\nStarting sorting process with \"%s\"...\n",
           (selection == 1) ? "Bubble Sort" :
           (selection == 2) ? "Selection Sort" :
           (selection == 3) ? "Insertion Sort" :
           (selection == 4) ? "Merge Sort" :
           (selection == 5) ? "Quick Sort" :
           (selection == 6) ? "Heap Sort" : "Hybrid Sort");

    switch (selection) {
        case 1: performBubbleSort(numbers, total, &passCount); break;
        case 2: performSelectionSort(numbers, total, &passCount); break;
        case 3: performInsertionSort(numbers, total, &passCount); break;
        case 4: mergeSort(numbers, 0, total - 1, &passCount); break;
        case 5: {
            int steps = 0;
            quickSort(numbers, 0, total - 1, &steps);
            passCount = steps;
            break;
        }
        case 6: heapSort(numbers, total, &passCount); break;
        case 7: hybridSort(numbers, 0, total - 1, &passCount); break;
    }

    printf("\nTotal passes: %d\n", passCount);
    printf("\nSorted Numbers:\n");
    for (int i = 0; i < total; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}

int validateSize(int size) {
    return size > 1;
}

int processInput(char *rawInput, int numbers[], int count) {
    int index = 0;
    char *token = strtok(rawInput, " ");
    while (token != NULL) {
        if (index >= count) return 0;
        numbers[index++] = atoi(token);
        token = strtok(NULL, " ");
    }
    return index == count;
}

void waitForEnter() {
    printf("Press Enter to continue...");
    getchar();
}

// Bubble Sort implementation
void performBubbleSort(int numbers[], int count, int *passCount) {
    int temp, isSorted;

    for (int i = 0; i < count - 1; i++) {
        isSorted = 1;

        printf("\nPass %d: ", i + 1);

        for (int j = 0; j < count - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                isSorted = 0;
            }
        }

        for (int k = 0; k < count; k++) {
            printf("%d ", numbers[k]);
        }
        printf("\n");

        (*passCount)++;

        if (isSorted) {
            printf("\nThe array is already sorted. Stopping early.\n");
            break;
        }

        waitForEnter();
    }
}

// Selection Sort implementation
void performSelectionSort(int numbers[], int count, int *passCount) {
    for (int i = 0; i < count - 1; i++) {
        int smallestIndex = i;

        for (int j = i + 1; j < count; j++) {
            if (numbers[j] < numbers[smallestIndex]) {
                smallestIndex = j;
            }
        }

        int temp = numbers[i];
        numbers[i] = numbers[smallestIndex];
        numbers[smallestIndex] = temp;

        printf("\nPass %d: ", i + 1);
        for (int k = 0; k < count; k++) {
            printf("%d ", numbers[k]);
        }
        printf("\n");

        (*passCount)++;
        waitForEnter();
    }
}

// Insertion Sort implementation
void performInsertionSort(int numbers[], int count, int *passCount) {
    for (int i = 1; i < count; i++) {
        int current = numbers[i];
        int j = i - 1;

        while (j >= 0 && numbers[j] > current) {
            numbers[j + 1] = numbers[j];
            j--;
        }

        numbers[j + 1] = current;

        printf("\nPass %d: ", i);
        for (int k = 0; k < count; k++) {
            printf("%d ", numbers[k]);
        }
        printf("\n");

        (*passCount)++;
        waitForEnter();
    }
}

// Quick Sort implementation
void quickSort(int numbers[], int start, int end, int *steps) {
    if (start < end) {
        printf("\nCurrent Subarray: ");
        for (int i = start; i <= end; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");

        int pivot = partitionArray(numbers, start, end, steps);
        quickSort(numbers, start, pivot - 1, steps);
        quickSort(numbers, pivot + 1, end, steps);
    }
}

int partitionArray(int numbers[], int start, int end, int *steps) {
    int pivot = numbers[end];
    int i = start - 1, temp;

    for (int j = start; j < end; j++) {
        if (numbers[j] <= pivot) {
            i++;
            temp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = temp;
        }
    }

    temp = numbers[i + 1];
    numbers[i + 1] = numbers[end];
    numbers[end] = temp;

    printf("\nPass %d: ", ++(*steps));
    for (int k = start; k <= end; k++) {
        printf("%d ", numbers[k]);
    }
    printf("\n");

    waitForEnter();
    return i + 1;
}

// Merge Sort implementation
void mergeSort(int numbers[], int left, int right, int *passCount) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(numbers, left, mid, passCount);
        mergeSort(numbers, mid + 1, right, passCount);
        merge(numbers, left, mid, right, passCount);
    }
}

void merge(int numbers[], int left, int mid, int right, int *passCount) {
    int n1 = mid - left + 1, n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = numbers[left + i];
    for (int i = 0; i < n2; i++) R[i] = numbers[mid + 1 + i];

    int i = 0, j = 0, k = left;

    printf("\nMerge Pass %d: ", ++(*passCount));
    printf("\nLeft Subarray: ");
    for (int x = 0; x < n1; x++) printf("%d ", L[x]);
    printf("\nRight Subarray: ");
    for (int x = 0; x < n2; x++) printf("%d ", R[x]);
    printf("\n\nMerging process: ");

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            numbers[k] = L[i];
            printf("%d ", numbers[k]);
            i++;
        } else {
            numbers[k] = R[j];
            printf("%d ", numbers[k]);
            j++;
        }
        k++;
    }

    while (i < n1) numbers[k++] = L[i++];
    while (j < n2) numbers[k++] = R[j++];
    printf("\nMerged Array: ");
    for (int x = left; x <= right; x++) printf("%d ", numbers[x]);
    printf("\n");
    waitForEnter();
}

// Heap Sort implementation
void heapSort(int numbers[], int count, int *passCount) {
    for (int i = count / 2 - 1; i >= 0; i--) {
        createHeap(numbers, count, i);
    }

    for (int i = count - 1; i > 0; i--) {
        int temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;

        createHeap(numbers, i, 0);

        printf("\nPass %d: ", ++(*passCount));
        for (int k = 0; k < count; k++) {
            printf("%d ", numbers[k]);
        }
        printf("\n");

        waitForEnter();
    }
}

void createHeap(int numbers[], int count, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < count && numbers[left] > numbers[largest]) largest = left;
    if (right < count && numbers[right] > numbers[largest]) largest = right;

    if (largest != root) {
        int temp = numbers[root];
        numbers[root] = numbers[largest];
        numbers[largest] = temp;
        createHeap(numbers, count, largest);
    }
}

/* =========================== HYBRID SORT FUNCTIONS =========================== */

/*
Hybrid Sort: Mixes Merge Sort and Insertion Sort for faster results.
1. Uses Merge Sort for big chunks of data (divide and conquer).
2. Switches to Insertion Sort for small chunks (faster for small arrays).
3. Combines both strategies for the best performance.

Advantages:
- **Faster for small data**: Insertion Sort is quick on small chunks.
- **Smart strategy**: Merge Sort handles big chunks, Insertion Sort handles small ones.
- **Better performance**: Overall faster since it picks the right method for the right data size.
*/

void hybridSort(int numbers[], int left, int right, int *passCount) {
    // If the chunk is small, use Insertion Sort
    if (right - left + 1 <= HYBRID_THRESHOLD) {
        insertionSortForHybrid(numbers, left, right, passCount);
        return;
    }

    // If the chunk is big, use Merge Sort
    int mid = left + (right - left) / 2;
    hybridSort(numbers, left, mid, passCount);
    hybridSort(numbers, mid + 1, right, passCount);
    merge(numbers, left, mid, right, passCount);
}

// Insertion Sort for small chunks of data
void insertionSortForHybrid(int numbers[], int left, int right, int *passCount) {
    for (int i = left + 1; i <= right; i++) {
        int current = numbers[i];
        int j = i - 1;

        while (j >= left && numbers[j] > current) {
            numbers[j + 1] = numbers[j];
            j--;
        }

        numbers[j + 1] = current;

        // Show the current array after each insertion sort pass
        printf("\nHybrid Pass %d: ", ++(*passCount));
        for (int k = left; k <= right; k++) {
            printf("%d ", numbers[k]);
        }
        printf("\n");

        waitForEnter();  // Wait for Enter before moving to the next pass
    }
}
