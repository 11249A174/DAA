/*
 * ============================================================
 * Experiment 4: Fractional Knapsack using Greedy Method
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: Sri Chandrasekharendra Saraswathi Viswa Mahavidyalaya
 * ============================================================
 *
 * Objective:
 *   Maximize the total value placed in a knapsack of capacity W by
 *   applying the Greedy Choice Property: always pick the item with
 *   the highest value-to-weight (profit-per-weight) ratio first.
 *   Fractions of items are allowed.
 *
 * Algorithm:
 *   1. Compute profit-per-weight ratio for every item: ppw = value / weight.
 *   2. Sort items in descending order of ppw.
 *   3. Greedily add items:
 *        - If item fits entirely, take it whole.
 *        - Otherwise, take the fraction that fills the remaining capacity.
 *   4. Report total accumulated profit.
 *
 * Key Insight:
 *   Greedy is OPTIMAL for the Fractional Knapsack.
 *   It is NOT optimal for the 0/1 Knapsack (requires Dynamic Programming).
 *
 * Time Complexity  : O(n log n) — dominated by sorting step
 * Space Complexity : O(n)
 * ============================================================
 */

#include <stdio.h>

/* Item structure */
struct Item {
    int   id;       /* original item number (1-indexed) */
    int   weight;
    int   value;
    float ppw;      /* profit per unit weight */
};

/**
 * sortByRatio - Bubble sort items by ppw in descending order.
 */
void sortByRatio(struct Item items[], int n)
{
    struct Item temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (items[j].ppw < items[j + 1].ppw) {
                temp       = items[j];
                items[j]   = items[j + 1];
                items[j+1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    float capacity;

    printf("============================================\n");
    printf("  Experiment 4: Fractional Knapsack        \n");
    printf("  Student ID  : 11249A174                  \n");
    printf("============================================\n\n");

    printf("Enter number of items     : ");
    scanf("%d", &n);
    if (n <= 0) { printf("Error: n must be positive.\n"); return 1; }

    struct Item items[n];

    printf("Enter weight and value of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("  Item %d (weight value): ", i + 1);
        scanf("%d %d", &items[i].weight, &items[i].value);
        items[i].id  = i + 1;
        items[i].ppw = (float)items[i].value / items[i].weight;
    }

    printf("Enter knapsack capacity   : ");
    scanf("%f", &capacity);

    /* Sort by value-to-weight ratio */
    sortByRatio(items, n);

    printf("\n--- Items sorted by Value/Weight ratio ---\n");
    printf("  %-6s %-8s %-8s %-10s\n", "Item", "Weight", "Value", "Ratio");
    for (int i = 0; i < n; i++)
        printf("  %-6d %-8d %-8d %-10.2f\n",
               items[i].id, items[i].weight, items[i].value, items[i].ppw);

    printf("\n--- Knapsack Selection ---\n");

    float totalProfit  = 0.0;
    float remaining    = capacity;

    for (int i = 0; i < n && remaining > 0; i++) {
        if (remaining >= items[i].weight) {
            /* Take the whole item */
            totalProfit += items[i].value;
            remaining   -= items[i].weight;
            printf("  Item %d: taken FULLY   (weight=%d, value=%d)  | Remaining capacity: %.2f\n",
                   items[i].id, items[i].weight, items[i].value, remaining);
        } else {
            /* Take a fraction */
            float fraction = remaining / items[i].weight;
            float gained   = items[i].ppw * remaining;
            totalProfit   += gained;
            printf("  Item %d: taken %.2f%%  (fraction=%.4f, value gained=%.2f)  | Remaining capacity: 0.00\n",
                   items[i].id, fraction * 100, fraction, gained);
            remaining = 0;
        }
    }

    printf("\n==========================================\n");
    printf("  Maximum Profit = %.2f\n", totalProfit);
    printf("==========================================\n");

    return 0;
}
