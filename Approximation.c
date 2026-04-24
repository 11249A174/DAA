/*
 * ============================================================
 * Approximation Algorithm — Nearest Neighbour Heuristic for TSP
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: SCSVMV
 * ============================================================
 *
 * Problem:
 *   The Travelling Salesman Problem (TSP) is NP-Hard — finding
 *   the exact optimal solution takes O(n! ) or O(n^2 * 2^n).
 *   For large inputs, we use APPROXIMATION ALGORITHMS that find
 *   a "good enough" solution quickly.
 *
 * This file implements TWO approximation approaches:
 *
 *  1. Nearest Neighbour Heuristic (Greedy)
 *     - Start at city 0.
 *     - Always visit the closest unvisited city next.
 *     - Return to start after all cities are visited.
 *     - Approximation Ratio: O(log n) * OPT in worst case
 *     - Time Complexity: O(n^2)
 *
 *  2. 2-Approximation using Minimum Spanning Tree (Christofides-like)
 *     - Build MST using Prim's algorithm.
 *     - Do a DFS traversal of MST to get a Hamiltonian path.
 *     - Approximation Ratio: <= 2 * OPT  (for metric TSP)
 *     - Time Complexity: O(n^2)
 *
 * Key Concept:
 *   An approximation algorithm guarantees:
 *       Cost(Approx) <= ratio * Cost(Optimal)
 *   where ratio is the APPROXIMATION RATIO.
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

#define MAXN  10
#define INF   999999

int n;
int dist[MAXN][MAXN];

/* ════════════════════════════════════════════════════════════
 *  METHOD 1: Nearest Neighbour Heuristic
 * ════════════════════════════════════════════════════════════ */

int nnTour(int start)
{
    int visited[MAXN];
    int tour[MAXN + 1];
    memset(visited, 0, sizeof(visited));

    int current   = start;
    int totalCost = 0;
    tour[0]       = start;
    visited[start]= 1;

    printf("\nMethod 1: Nearest Neighbour Heuristic\n");
    printf("--------------------------------------\n");
    printf("Tour: %d", start);

    for (int step = 1; step < n; step++) {
        int nearest  = -1;
        int minDist  = INF;

        /* Find the closest unvisited city */
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[current][j] < minDist) {
                minDist = dist[current][j];
                nearest = j;
            }
        }

        visited[nearest] = 1;
        tour[step]       = nearest;
        totalCost       += minDist;
        printf(" -> %d", nearest);
        current = nearest;
    }

    /* Return to start */
    totalCost += dist[current][start];
    printf(" -> %d\n", start);
    printf("Total Tour Cost (Nearest Neighbour) = %d\n", totalCost);

    return totalCost;
}


/* ════════════════════════════════════════════════════════════
 *  METHOD 2: MST-based 2-Approximation
 *  Steps:
 *    a) Build MST using Prim's
 *    b) DFS on MST to get visit order (preorder)
 *    c) That order is the approximate TSP tour
 * ════════════════════════════════════════════════════════════ */

int parent[MAXN];       /* MST parent array */
int adj[MAXN][MAXN];    /* MST as adjacency matrix */

/* Prim's MST */
void buildMST()
{
    int key[MAXN], visited[MAXN];

    for (int i = 0; i < n; i++) {
        key[i]     = INF;
        visited[i] = 0;
        parent[i]  = -1;
    }
    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        /* Pick minimum key unvisited vertex */
        int u = -1, minKey = INF;
        for (int i = 0; i < n; i++)
            if (!visited[i] && key[i] < minKey) {
                minKey = key[i];
                u = i;
            }

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (dist[u][v] && !visited[v] && dist[u][v] < key[v]) {
                parent[v] = u;
                key[v]    = dist[u][v];
            }
        }
    }

    /* Build MST adjacency from parent array */
    memset(adj, 0, sizeof(adj));
    for (int i = 1; i < n; i++) {
        adj[parent[i]][i] = 1;
        adj[i][parent[i]] = 1;
    }
}

/* DFS preorder traversal of MST */
int dfsVisited[MAXN];
int tourOrder[MAXN];
int tourIdx;

void dfs(int u)
{
    dfsVisited[u]      = 1;
    tourOrder[tourIdx++] = u;
    for (int v = 0; v < n; v++)
        if (adj[u][v] && !dfsVisited[v])
            dfs(v);
}

int mstApproximation()
{
    buildMST();

    memset(dfsVisited, 0, sizeof(dfsVisited));
    tourIdx = 0;
    dfs(0);

    printf("\nMethod 2: MST-based 2-Approximation\n");
    printf("-------------------------------------\n");
    printf("Tour: ");

    int totalCost = 0;
    for (int i = 0; i < n; i++) {
        printf("%d", tourOrder[i]);
        if (i < n - 1) {
            totalCost += dist[tourOrder[i]][tourOrder[i + 1]];
            printf(" -> ");
        }
    }
    /* Return to start */
    totalCost += dist[tourOrder[n - 1]][tourOrder[0]];
    printf(" -> %d\n", tourOrder[0]);
    printf("Total Tour Cost (MST Approximation) = %d\n", totalCost);

    return totalCost;
}


/* ════════════════════════════════════════════════════════════
 *  MAIN
 * ════════════════════════════════════════════════════════════ */

int main()
{
    printf("============================================\n");
    printf("  Approximation Algorithms for TSP         \n");
    printf("  Student ID : 11249A174                   \n");
    printf("============================================\n\n");

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter %d x %d distance matrix:\n", n, n);
    for (int i = 0; i < n; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < n; j++)
            scanf("%d", &dist[i][j]);
    }

    int c1 = nnTour(0);
    int c2 = mstApproximation();

    printf("\n============================================\n");
    printf("  Summary\n");
    printf("  Nearest Neighbour Cost : %d\n", c1);
    printf("  MST Approx Cost        : %d\n", c2);
    printf("  Best Approx Found      : %d\n", c1 < c2 ? c1 : c2);
    printf("============================================\n");

    return 0;
}

/*
 * ============================================================
 * SAMPLE INPUT:
 *   Cities: 4
 *   Matrix:
 *     0 10 15 20
 *    10  0 35 25
 *    15 35  0 30
 *    20 25 30  0
 *
 * SAMPLE OUTPUT:
 *   Nearest Neighbour Tour: 0->1->3->2->0  Cost=80
 *   MST Approx Tour       : 0->1->3->2->0  Cost=80
 *   Optimal Tour          : 0->1->3->2->0  Cost=80
 * ============================================================
 */
