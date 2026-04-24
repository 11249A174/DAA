/*
 * ============================================================
 * Dijkstra's Shortest Path Algorithm
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: SCSVMV
 * ============================================================
 *
 * Problem:
 *   Given a weighted directed graph, find the shortest path
 *   from a source vertex to all other vertices.
 *
 * Algorithm:
 *   1. Set distance of source = 0, all others = INFINITY.
 *   2. Pick the unvisited vertex with minimum distance (u).
 *   3. Mark u as visited.
 *   4. For each unvisited neighbour v of u:
 *        if dist[u] + weight(u,v) < dist[v]
 *            update dist[v] = dist[u] + weight(u,v)
 *            set parent[v] = u
 *   5. Repeat steps 2-4 until all vertices are visited.
 *
 * Time Complexity  : O(V^2) with adjacency matrix
 *                    O((V + E) log V) with min-heap
 * Space Complexity : O(V)
 *
 * Constraint: Edge weights must be NON-NEGATIVE.
 * ============================================================
 */

#include <stdio.h>

#define MAXV   10
#define INF    999999

int V;   /* number of vertices */

/* ── Helper: find unvisited vertex with minimum distance ── */
int minDistance(int dist[], int visited[])
{
    int min = INF, min_index = 0;
    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] < min) {
            min       = dist[v];
            min_index = v;
        }
    return min_index;
}

/* ── Print shortest path from source to target ── */
void printPath(int parent[], int v)
{
    if (parent[v] == -1) {          /* reached source */
        printf("%d", v);
        return;
    }
    printPath(parent, parent[v]);
    printf(" -> %d", v);
}

/* ── Dijkstra's Algorithm ── */
void dijkstra(int graph[MAXV][MAXV], int src)
{
    int dist[MAXV];      /* shortest distance from src    */
    int visited[MAXV];   /* processed vertex flag         */
    int parent[MAXV];    /* to reconstruct path           */

    /* Initialise */
    for (int i = 0; i < V; i++) {
        dist[i]    = INF;
        visited[i] = 0;
        parent[i]  = -1;
    }
    dist[src] = 0;

    /* Process V-1 vertices */
    for (int count = 0; count < V - 1; count++) {

        /* Pick minimum distance unvisited vertex */
        int u = minDistance(dist, visited);
        visited[u] = 1;

        /* Relax edges from u */
        for (int v = 0; v < V; v++) {
            if (!visited[v]
                && graph[u][v] != 0
                && dist[u] != INF
                && dist[u] + graph[u][v] < dist[v])
            {
                dist[v]   = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    /* Print results */
    printf("\nDijkstra's Shortest Paths from Source vertex %d:\n", src);
    printf("%-10s %-12s %-20s\n", "Vertex", "Distance", "Path");
    printf("------------------------------------------\n");
    for (int i = 0; i < V; i++) {
        printf("%-10d ", i);
        if (dist[i] == INF)
            printf("%-12s ", "UNREACHABLE");
        else
            printf("%-12d ", dist[i]);
        printPath(parent, i);
        printf("\n");
    }
}

/* ── Main ── */
int main()
{
    int graph[MAXV][MAXV];

    printf("============================================\n");
    printf("  Dijkstra's Shortest Path Algorithm        \n");
    printf("  Student ID : 11249A174                   \n");
    printf("============================================\n\n");

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (%d x %d)\n", V, V);
    printf("(Enter 0 if no direct edge between vertices)\n");
    for (int i = 0; i < V; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);
    }

    int src;
    printf("Enter source vertex (0 to %d): ", V - 1);
    scanf("%d", &src);

    dijkstra(graph, src);

    return 0;
}

/*
 * ============================================================
 * SAMPLE INPUT:
 *   Vertices: 5
 *   Matrix:
 *     0 10  0  0 5
 *    10  0  1  0 2
 *     0  1  0  4 0
 *     0  0  4  0 0
 *     5  2  0  0 0
 *   Source: 0
 *
 * SAMPLE OUTPUT:
 *   Vertex  Distance    Path
 *   0       0           0
 *   1       7           0 -> 4 -> 1
 *   2       8           0 -> 4 -> 1 -> 2
 *   3       12          0 -> 4 -> 1 -> 2 -> 3
 *   4       5           0 -> 4
 * ============================================================
 */
