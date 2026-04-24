/*
 * ============================================================
 * Experiment 5: Travelling Salesman Problem (TSP)
 *               — Held-Karp Dynamic Programming Algorithm
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: Sri Chandrasekharendra Saraswathi Viswa Mahavidyalaya
 * ============================================================
 *
 * Objective:
 *   Find the minimum-cost Hamiltonian cycle (visit every city
 *   exactly once and return to start) using the Held-Karp DP
 *   algorithm with bitmask subset representation.
 *
 * Algorithm (Held-Karp):
 *   Let g(i, S) = minimum cost of a path starting at city 0,
 *                  visiting all cities in subset S, ending at city i.
 *
 *   Recurrence:
 *     g(i, {}) = d[i][0]                         (return to start)
 *     g(i, S)  = min{ d[i][k] + g(k, S\{i}) }   for k in S
 *
 *   Final answer: g(0, {1, 2, ..., n-1})
 *
 * Bitmask Representation:
 *   Each subset of cities is stored as a bitmask integer.
 *   City k is in subset S  iff  (S >> k) & 1 == 1.
 *
 * Time Complexity  : O(n^2 * 2^n) — DP over all subsets
 * Space Complexity : O(n * 2^n)
 * Note             : TSP is NP-Hard; DP is exact but impractical for large n.
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

#define MAXN  15
#define INF   999999

int  n;
int  d[MAXN][MAXN];                 /* cost / distance matrix         */
int  dp[MAXN][1 << MAXN];          /* memoisation table              */

/**
 * g - Recursively computes minimum cost of visiting cities in S
 *     starting from city i, with memoisation.
 *
 * @i: Current city
 * @S: Bitmask of remaining cities to visit (city 0 excluded from S)
 *
 * Returns: Minimum path cost from city i through all cities in S back to 0.
 */
int g(int i, int S)
{
    /* Base case: no cities left — return directly to starting city (0) */
    if (S == 0)
        return d[i][0];

    /* Memoisation check */
    if (dp[i][S] != -1)
        return dp[i][S];

    int minCost = INF;

    /* Try each city k still in S as the next destination */
    for (int k = 1; k < n; k++) {
        if (S & (1 << k)) {                        /* city k is in S */
            int cost = d[i][k] + g(k, S & ~(1 << k));   /* remove k from S */
            if (cost < minCost)
                minCost = cost;
        }
    }

    return dp[i][S] = minCost;
}

int main()
{
    printf("============================================\n");
    printf("  Experiment 5: Travelling Salesman (TSP)  \n");
    printf("  Student ID  : 11249A174                  \n");
    printf("============================================\n\n");

    printf("Enter number of cities (max %d): ", MAXN);
    scanf("%d", &n);
    if (n <= 0 || n > MAXN) {
        printf("Error: n must be between 1 and %d.\n", MAXN);
        return 1;
    }

    printf("Enter the %d x %d cost matrix (row by row):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &d[i][j]);

    /* Initialise DP table with -1 (uncomputed) */
    memset(dp, -1, sizeof(dp));

    /* Build initial subset: all cities except city 0 (starting city) */
    int S = 0;
    for (int i = 1; i < n; i++)
        S |= (1 << i);

    int result = g(0, S);

    /* Print the cost matrix */
    printf("\nGiven Cost Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("  |");
        for (int j = 0; j < n; j++)
            printf(" %4d", d[i][j]);
        printf(" |\n");
    }

    printf("\n==========================================\n");
    printf("  Minimum TSP Tour Cost = %d\n", result);
    printf("==========================================\n");

    return 0;
}
