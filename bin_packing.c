/*
 * ============================================================
 * Experiment 3: Bin Packing — First Fit & Best Fit Heuristics
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: Sri Chandrasekharendra Saraswathi Viswa Mahavidyalaya
 * ============================================================
 *
 * Objective:
 *   Implement and compare two greedy heuristics for the NP-Hard
 *   Bin Packing problem: First Fit (FF) and Best Fit (BF).
 *
 * Problem:
 *   Given n items with sizes and bins of fixed capacity C,
 *   pack all items using the minimum number of bins.
 *
 * First Fit (FF):
 *   For each item, place it in the FIRST bin that has enough space.
 *   If no bin fits, open a new bin.
 *
 * Best Fit (BF):
 *   For each item, place it in the bin that leaves the LEAST remaining
 *   space after placement (tightest fit). Open new bin if needed.
 *
 * Time Complexity  : O(n^2) for both (can be O(n log n) with advanced DS)
 * Heuristic Ratio  : Both guarantee <= 1.7 * OPT + 2 bins
 * ============================================================
 */

#include <stdio.h>

/* ── First Fit ───────────────────────────────────────────── */
void firstFit(int items[], int n, int capacity)
{
    int bin[n];          /* remaining capacity of each bin */
    int binCount = 0;

    /* Initialise all bins to full capacity */
    for (int i = 0; i < n; i++)
        bin[i] = capacity;

    printf("\n--- First Fit Result ---\n");

    for (int i = 0; i < n; i++) {
        int placed = 0;

        /* Try existing bins in order */
        for (int j = 0; j < binCount; j++) {
            if (bin[j] >= items[i]) {
                bin[j] -= items[i];
                printf("  Item %d (size %d) --> Bin %d  [Remaining: %d]\n",
                       i + 1, items[i], j + 1, bin[j]);
                placed = 1;
                break;          /* First Fit: stop at first match */
            }
        }

        /* Open a new bin if item didn't fit anywhere */
        if (!placed) {
            bin[binCount] -= items[i];
            printf("  Item %d (size %d) --> Bin %d  [Remaining: %d]  (new bin)\n",
                   i + 1, items[i], binCount + 1, bin[binCount]);
            binCount++;
        }
    }

    printf("  Total bins used (First Fit) = %d\n", binCount);
}

/* ── Best Fit ────────────────────────────────────────────── */
void bestFit(int items[], int n, int capacity)
{
    int bin[n];
    int binCount = 0;

    for (int i = 0; i < n; i++)
        bin[i] = capacity;

    printf("\n--- Best Fit Result ---\n");

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        int minSpace  = capacity + 1;   /* sentinel: larger than any valid space */

        /* Find the bin that leaves the least remaining space */
        for (int j = 0; j < binCount; j++) {
            if (bin[j] >= items[i] && (bin[j] - items[i]) < minSpace) {
                bestIndex = j;
                minSpace  = bin[j] - items[i];
            }
        }

        if (bestIndex != -1) {
            bin[bestIndex] -= items[i];
            printf("  Item %d (size %d) --> Bin %d  [Remaining: %d]\n",
                   i + 1, items[i], bestIndex + 1, bin[bestIndex]);
        } else {
            /* No suitable bin — open a new one */
            bin[binCount] -= items[i];
            printf("  Item %d (size %d) --> Bin %d  [Remaining: %d]  (new bin)\n",
                   i + 1, items[i], binCount + 1, bin[binCount]);
            binCount++;
        }
    }

    printf("  Total bins used (Best Fit)  = %d\n", binCount);
}

/* ── Main ────────────────────────────────────────────────── */
int main()
{
    int n, capacity;

    printf("============================================\n");
    printf("  Experiment 3: Bin Packing (FF & BF)      \n");
    printf("  Student ID  : 11249A174                  \n");
    printf("============================================\n\n");

    printf("Enter number of items   : ");
    scanf("%d", &n);

    printf("Enter bin capacity      : ");
    scanf("%d", &capacity);

    int items[n];

    printf("Enter item sizes (each <= %d):\n", capacity);
    for (int i = 0; i < n; i++) {
        printf("  Item %d: ", i + 1);
        int sz;
        scanf("%d", &sz);
        if (sz > capacity) {
            printf("  Warning: Item size exceeds capacity — re-enter.\n");
            i--;
            continue;
        }
        items[i] = sz;
    }

    firstFit(items, n, capacity);
    bestFit (items, n, capacity);

    return 0;
}
