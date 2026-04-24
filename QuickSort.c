/*
 * ============================================================
 * QuickSort — Divide and Conquer Sorting Algorithm
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: SCSVMV
 * ============================================================
 *
 * Problem:
 *   Sort an array of integers in ascending order using QuickSort.
 *
 * Algorithm:
 *   1. Choose a PIVOT element (last element used here).
 *   2. PARTITION the array:
 *        - Move all elements < pivot to the LEFT of pivot.
 *        - Move all elements > pivot to the RIGHT of pivot.
 *        - Pivot is now at its CORRECT final position.
 *   3. Recursively apply QuickSort to left and right sub-arrays.
 *   4. Base Case: sub-array has 0 or 1 element → already sorted.
 *
 * Partition Logic (Lomuto Scheme):
 *   - i tracks the boundary of elements smaller than pivot.
 *   - j scans through the array.
 *   - When arr[j] <= pivot: swap arr[i+1] and arr[j], increment i.
 *   - Finally place pivot at position i+1.
 *
 * Time Complexity:
 *   Best Case    : O(n log n)  — pivot always divides evenly
 *   Average Case : O(n log n)
 *   Worst Case   : O(n^2)      — already sorted array with last pivot
 *
 * Space Complexity : O(log n) — recursive call stack
 *
 * Advantage: In-place sorting, cache-friendly, fastest in practice.
 * ============================================================
 */

#include <stdio.h>

/* ── Swap two integers ── */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* ── Print the array ── */
void printArray(int arr[], int n)
{
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d%s", arr[i], i < n - 1 ? ", " : " ");
    printf("]\n");
}

/*
 * partition - Lomuto partition scheme.
 *   Places pivot (last element) at correct position.
 *   Returns the final index of the pivot.
 */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];   /* choose last element as pivot */
    int i     = low - 1;     /* boundary for smaller elements */

    printf("  Pivot = %d  |  Sub-array: ", pivot);
    for (int k = low; k <= high; k++)
        printf("%d ", arr[k]);
    printf("\n");

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    /* Place pivot in its correct position */
    swap(&arr[i + 1], &arr[high]);

    printf("  After partition: ");
    for (int k = low; k <= high; k++)
        printf("%d ", arr[k]);
    printf("  (pivot %d at index %d)\n\n", pivot, i + 1);

    return i + 1;   /* index of pivot after partitioning */
}

/*
 * quickSort - Recursively sorts arr[low..high].
 */
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        /* pi = partition index; arr[pi] is now at correct position */
        int pi = partition(arr, low, high);

        /* Sort elements before and after partition */
        quickSort(arr, low,  pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* ── Main ── */
int main()
{
    int n;

    printf("============================================\n");
    printf("  QuickSort — Divide and Conquer           \n");
    printf("  Student ID : 11249A174                   \n");
    printf("============================================\n\n");

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal Array : ");
    printArray(arr, n);

    printf("\n--- QuickSort Step-by-Step ---\n\n");
    quickSort(arr, 0, n - 1);

    printf("Sorted Array   : ");
    printArray(arr, n);

    printf("\n==========================================\n");
    printf("  Time  Complexity: O(n log n) average    \n");
    printf("  Space Complexity: O(log n) stack space  \n");
    printf("==========================================\n");

    return 0;
}

/*
 * ============================================================
 * SAMPLE INPUT:
 *   n = 6
 *   Elements: 64 34 25 12 22 11
 *
 * SAMPLE OUTPUT:
 *   Original Array : [ 64, 34, 25, 12, 22, 11 ]
 *
 *   Pivot = 11 | Sub-array: 64 34 25 12 22 11
 *   After partition: 11 34 25 12 22 64  (pivot 11 at index 0)
 *
 *   Pivot = 64 | Sub-array: 34 25 12 22 64
 *   After partition: 34 25 12 22 64  (pivot 64 at index 4)
 *   ...
 *
 *   Sorted Array   : [ 11, 12, 22, 25, 34, 64 ]
 * ============================================================
 */
