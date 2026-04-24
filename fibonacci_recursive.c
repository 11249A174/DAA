/*
 * ============================================================
 * Experiment 2b: Fibonacci Term Using Recursive Method
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: Sri Chandrasekharendra Saraswathi Viswa Mahavidyalaya
 * ============================================================
 *
 * Objective:
 *   Compute the nth Fibonacci term using tree recursion and
 *   compare its inefficiency (overlapping subproblems) against
 *   the iterative approach.
 *
 * Mathematical Definition:
 *   F(0) = 0,  F(1) = 1
 *   F(n) = F(n-1) + F(n-2),  for n >= 2
 *
 * Algorithm:
 *   1. Read n and validate (n >= 0).
 *   2. If n <= 1, return n (base condition).
 *   3. Otherwise, return fib(n-1) + fib(n-2)  [recursive call].
 *   4. Print the full series using helper loop calling fib(i).
 *
 * Time Complexity  : O(2^n) — Tree recursion (exponential growth)
 * Space Complexity : O(n)   — Recursive call stack depth
 * Recurrence       : T(n) = T(n-1) + T(n-2) + c
 *
 * NOTE: Overlapping subproblems cause repeated recomputation.
 *       e.g., fib(5) recomputes fib(3) twice, fib(2) three times.
 *       Prefer the iterative version for large n.
 * ============================================================
 */

#include <stdio.h>

/**
 * fib - Computes the nth Fibonacci number recursively.
 * @n: Index of the Fibonacci term (0-indexed)
 *
 * Returns: The Fibonacci value at index n.
 */
int fib(int n)
{
    /* Base Condition: F(0) = 0, F(1) = 1 */
    if (n <= 1)
        return n;

    /*
     * Recursive Step: F(n) = F(n-1) + F(n-2)
     * Each call branches into two more calls → exponential complexity.
     */
    return fib(n - 1) + fib(n - 2);
}

int main()
{
    int n;

    printf("============================================\n");
    printf("  Experiment 2b: Fibonacci (Recursive)     \n");
    printf("  Student ID   : 11249A174                 \n");
    printf("============================================\n\n");

    printf("Enter the value of n (position, 0-indexed): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Error: Please enter a valid non-negative integer.\n");
        return 1;
    }

    /* Print the Fibonacci series up to nth term */
    printf("\nFibonacci Series: ");
    for (int i = 0; i <= n; i++)
        printf("%d ", fib(i));

    printf("\n\nFibonacci term F(%d) = %d\n", n, fib(n));

    return 0;
}
