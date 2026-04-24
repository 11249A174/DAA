/*
 * ============================================================
 * Kruskal's Algorithm — Minimum Spanning Tree (MST)
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: SCSVMV
 * ============================================================
 *
 * Problem:
 *   Given a connected, undirected, weighted graph find a
 *   spanning tree with the minimum possible total edge weight.
 *
 * Algorithm (Kruskal's):
 *   1. List all edges and sort them by weight (ascending).
 *   2. Initialise each vertex as its own disjoint set (DSU).
 *   3. For each edge (u, v, w) in sorted order:
 *        - If u and v belong to DIFFERENT sets (no cycle):
 *            * Add edge to MST.
 *            * Union the two sets.
 *        - Skip if they are in the SAME set (would form cycle).
 *   4. Stop when MST has V-1 edges.
 *
 * Disjoint Set Union (DSU / Union-Find):
 *   - find(v)      : Find the root/leader of v's set.
 *   - union(u, v)  : Merge the sets containing u and v.
 *
 * Time Complexity  : O(E log E)  — sorting dominates
 * Space Complexity : O(V + E)
 * ============================================================
 */

#include <stdio.h>

#define MAXV   20
#define MAXE   100

/* Edge structure */
struct Edge {
    int u, v, weight;
};

int V, E;                    /* vertices, edges         */
struct Edge edges[MAXE];     /* edge list               */
struct Edge mst[MAXE];       /* selected MST edges      */
int dsu_parent[MAXV];        /* DSU parent array        */
int dsu_rank[MAXV];          /* DSU rank (for union by rank) */

/* ── DSU: Find with Path Compression ── */
int find(int x)
{
    if (dsu_parent[x] != x)
        dsu_parent[x] = find(dsu_parent[x]);   /* path compression */
    return dsu_parent[x];
}

/* ── DSU: Union by Rank ── */
void unionSets(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return;

    /* Attach smaller rank tree under larger rank tree */
    if (dsu_rank[rootX] < dsu_rank[rootY])
        dsu_parent[rootX] = rootY;
    else if (dsu_rank[rootX] > dsu_rank[rootY])
        dsu_parent[rootY] = rootX;
    else {
        dsu_parent[rootY] = rootX;
        dsu_rank[rootX]++;
    }
}

/* ── Sort edges by weight (Bubble Sort) ── */
void sortEdges()
{
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                struct Edge temp = edges[j];
                edges[j]         = edges[j + 1];
                edges[j + 1]     = temp;
            }
        }
    }
}

/* ── Kruskal's Main Logic ── */
void kruskal()
{
    /* Initialise DSU */
    for (int i = 0; i < V; i++) {
        dsu_parent[i] = i;
        dsu_rank[i]   = 0;
    }

    /* Sort all edges by weight */
    sortEdges();

    printf("\nEdges sorted by weight:\n");
    printf("%-6s %-6s %-8s\n", "From", "To", "Weight");
    printf("----------------------\n");
    for (int i = 0; i < E; i++)
        printf("%-6d %-6d %-8d\n", edges[i].u, edges[i].v, edges[i].weight);

    /* Build MST */
    int mstCount = 0;
    int totalCost = 0;

    printf("\nKruskal's MST Construction:\n");
    printf("%-6s %-6s %-8s %-10s\n", "From", "To", "Weight", "Action");
    printf("----------------------------------\n");

    for (int i = 0; i < E && mstCount < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            /* Different sets — no cycle — add to MST */
            mst[mstCount++] = edges[i];
            unionSets(u, v);
            totalCost += w;
            printf("%-6d %-6d %-8d ADDED\n", u, v, w);
        } else {
            /* Same set — would form cycle — skip */
            printf("%-6d %-6d %-8d SKIPPED (cycle)\n", u, v, w);
        }
    }

    /* Print final MST */
    printf("\n==========================================\n");
    printf("  Kruskal's MST Result\n");
    printf("  %-6s %-6s %-8s\n", "From", "To", "Weight");
    printf("  ----------------------\n");
    for (int i = 0; i < mstCount; i++)
        printf("  %-6d %-6d %-8d\n", mst[i].u, mst[i].v, mst[i].weight);
    printf("  ----------------------\n");
    printf("  Total MST Cost = %d\n", totalCost);
    printf("==========================================\n");
}

/* ── Main ── */
int main()
{
    printf("============================================\n");
    printf("  Kruskal's Algorithm — Minimum Span Tree  \n");
    printf("  Student ID : 11249A174                   \n");
    printf("============================================\n\n");

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges   : ");
    scanf("%d", &E);

    printf("Enter each edge as: u v weight\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    kruskal();

    return 0;
}

/*
 * ============================================================
 * SAMPLE INPUT:
 *   Vertices : 5
 *   Edges    : 6
 *   Edge list:
 *     0 1 2
 *     0 2 3
 *     1 2 5
 *     1 3 3
 *     2 4 4
 *     3 4 2
 *
 * SAMPLE OUTPUT:
 *   MST Edges:
 *   0 -- 1  Weight: 2
 *   3 -- 4  Weight: 2
 *   0 -- 2  Weight: 3
 *   1 -- 3  Weight: 3
 *   Total MST Cost = 10
 * ============================================================
 */
