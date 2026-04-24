/*
 * ============================================================
 * Experiment 3a: Bin Packing — Best Fit (BF) Heuristic
 * ============================================================
 * Student ID : 11249A174
 * ============================================================
 */

#include <stdio.h>

void bestFit(int items[], int n, int capacity)
{
    int bin[n];
    int binCount = 0;

    for (int i = 0; i < n; i++)
        bin[i] = capacity;

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        int minSpace  = capacity + 1;

        for (int j = 0; j < binCount; j++) {
            if (bin[j] >= items[i] && (bin[j] - items[i]) < minSpace) {
                bestIndex = j;
                minSpace  = bin[j] - items[i];
            }
        }

        if (bestIndex != -1) {
            bin[bestIndex] -= items[i];
            printf("Item %d (weight: %d) placed in Bin %d\n",
                   i + 1, items[i], bestIndex + 1);
        } else {
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

    printf("Best Fit Bin Packing\n");
    printf("====================\n");

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
    bestFit(items, n, capacity);

    return 0;
}
