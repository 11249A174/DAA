/*
 * ============================================================
 * Experiment 6: Minimum Spanning Tree (MST)
 *               — Prim's & Kruskal's Algorithms
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: Sri Chandrasekharendra Saraswathi Viswa Mahavidyalaya
 * ============================================================
 *
 * Objective:
 *   Find the minimum spanning tree of a connected undirected
 *   weighted graph using both Prim's and Kruskal's algorithms.
 *
 * ── Prim's Algorithm ──────────────────────────────────────
 *   Grows the MST vertex by vertex.
 *   Key idea: Always pick the minimum-weight edge from visited
 *             vertices to unvisited vertices.
 *   Uses: Adjacency matrix + key[] array.
 *   Time Complexity: O(V^2)  (O(E log V) with priority queue)
 *
 * ── Kruskal's Algorithm ───────────────────────────────────
 *   Grows the MST edge by edge.
 *   Key idea: Sort all edges by weight; greedily add each edge
 *             if it does NOT create a cycle (checked via DSU).
 *   Uses: Edge list + Disjoint Set Union (Union-Find).
 *   Time Complexity: O(E log E)
 *
 * Space Complexity: O(V + E)
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

/* ══════════════════════════════════════════════════════════
 *  PRIM'S ALGORITHM
 * ══════════════════════════════════════════════════════════ */

#define MAXV 10
#define INF  999999

/**
 * minKey - Returns index of the unvisited vertex with the smallest key value.
 */
int minKey(int key[], int visited[], int V)
{
    int min = INF, min_index = 0;
    for (int i = 0; i < V; i++)
        if (!visited[i] && key[i] < min) {
            min       = key[i];
            min_index = i;
        }
    return min_index;
}

/**
 * primMST - Runs Prim's algorithm on the given adjacency matrix.
 * @graph : V x V adjacency matrix (0 means no edge)
 * @V     : Number of vertices
 */
void primMST(int graph[MAXV][MAXV], int V)
{
    int parent[MAXV];   /* MST tree structure    */
    int key[MAXV];      /* min edge weight so far */
    int visited[MAXV];  /* in-MST flag            */

    /* Step 1: Initialise */
    for (int i = 0; i < V; i++) {
        key[i]     = INF;
        visited[i] = 0;
    }

    /* Step 2: Start from vertex 0 */
    key[0]    = 0;
    parent[0] = -1;

    /* Step 3: Add V-1 edges to the MST */
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, visited, V);
        visited[u] = 1;

        /* Update keys for neighbours of u */
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v]    = graph[u][v];
            }
        }
    }

    /* Print MST */
    int total = 0;
    printf("\n--- Prim's MST ---\n");
    printf("  %-10s %-10s %-8s\n", "From", "To", "Weight");
    for (int i = 1; i < V; i++) {
        printf("  %-10d %-10d %-8d\n", parent[i], i, graph[i][parent[i]]);
        total += graph[i][parent[i]];
    }
    printf("  Total MST Cost (Prim's) = %d\n", total);
}


/* ══════════════════════════════════════════════════════════
 *  KRUSKAL'S ALGORITHM  (Disjoint Set Union)
 * ══════════════════════════════════════════════════════════ */

#define MAXE 50

int dsu_parent[MAXV];

/** findLeader - Path-compressed find for DSU. */
int findLeader(int v)
{
    while (dsu_parent[v] != v)
        v = dsu_parent[v];
    return v;
}

/** mergeSets - Union of two disjoint sets. */
void mergeSets(int u, int v)
{
    dsu_parent[findLeader(u)] = findLeader(v);
}

/** sortEdges - Bubble sort edges array by weight (ascending). */
void sortEdges(int edges[][3], int E)
{
    for (int i = 0; i < E - 1; i++)
        for (int j = 0; j < E - i - 1; j++)
            if (edges[j][2] > edges[j+1][2]) {
                for (int k = 0; k < 3; k++) {
                    int tmp      = edges[j][k];
                    edges[j][k]  = edges[j+1][k];
                    edges[j+1][k]= tmp;
                }
            }
}

/**
 * kruskalMST - Runs Kruskal's algorithm.
 * @edges : Array of [u, v, weight] edges
 * @E     : Number of edges
 * @V     : Number of vertices
 */
void kruskalMST(int edges[][3], int E, int V)
{
    sortEdges(edges, E);

    /* Initialise DSU */
    for (int i = 0; i < V; i++)
        dsu_parent[i] = i;

    int count = 0, cost = 0;
    printf("\n--- Kruskal's MST ---\n");
    printf("  %-10s %-10s %-8s\n", "From", "To", "Weight");

    for (int i = 0; i < E && count < V - 1; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        /* Add edge only if it doesn't form a cycle */
        if (findLeader(u) != findLeader(v)) {
            printf("  %-10d %-10d %-8d\n", u, v, w);
            mergeSets(u, v);
            cost  += w;
            count++;
        }
    }
    printf("  Total MST Cost (Kruskal's) = %d\n", cost);
}


/* ══════════════════════════════════════════════════════════
 *  MAIN
 * ══════════════════════════════════════════════════════════ */

int main()
{
    printf("============================================\n");
    printf("  Experiment 6: Minimum Spanning Tree      \n");
    printf("  Student ID  : 11249A174                  \n");
    printf("============================================\n\n");

    /* ── Prim's demo with hardcoded 5-vertex graph ── */
    int V = 5;
    int graph[MAXV][MAXV] = {
        {0, 2, 3, 0, 0},
        {2, 0, 5, 3, 0},
        {3, 5, 0, 0, 4},
        {0, 3, 0, 0, 2},
        {0, 0, 4, 2, 0}
    };

    printf("Graph adjacency matrix (0 = no edge):\n");
    for (int i = 0; i < V; i++) {
        printf("  |");
        for (int j = 0; j < V; j++)
            printf(" %2d", graph[i][j]);
        printf(" |\n");
    }

    primMST(graph, V);

    /* ── Kruskal's demo with same graph as edge list ── */
    int E = 6;
    int edges[MAXE][3] = {
        {0, 1, 2},
        {0, 2, 3},
        {1, 2, 5},
        {1, 3, 3},
        {2, 4, 4},
        {3, 4, 2}
    };

    kruskalMST(edges, E, V);

    return 0;
}
