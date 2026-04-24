/*
 * ============================================================
 * Experiment 3b: Bin Packing — First Fit (FF) Heuristic
 * ============================================================
 * Student ID : 11249A174
 * ============================================================
 */

#include <stdio.h>

void firstFit(int items[], int n, int capacity)
{
    int bin[n];
    int binCount = 0;

    for (int i = 0; i < n; i++)
        bin[i] = capacity;

    for (int i = 0; i < n; i++) {
        int placed = 0;

        for (int j = 0; j < binCount; j++) {
            if (bin[j] >= items[i]) {
                bin[j] -= items[i];
                printf("Item %d (weight: %d) placed in Bin %d\n",
                       i + 1, items[i], j + 1);
                placed = 1;
                break;
            }
        }

        if (!placed) {
            bin[binCount] -= items[i];
            printf("Item %d (weight: %d) placed in Bin %d\n",
                   i + 1, items[i], binCount + 1);
            binCount++;
        }
    }

    printf("Total bins used = %d\n", binCount);
}

int main()
{
    int n, capacity;

    printf("First Fit Bin Packing\n");
    printf("=====================\n");

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter bin capacity: ");
    scanf("%d", &capacity);

    int items[n];
    printf("Enter item sizes:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d", &items[i]);
        if (items[i] > capacity) {
            printf("Item size exceeds bin capacity. Re-enter.\n");
            i--;
        }
    }

    printf("\n");
    firstFit(items, n, capacity);

    return 0;
}
