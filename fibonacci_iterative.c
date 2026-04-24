/*
 * ============================================================
 * Experiment 2a: Fibonacci Term Using Iterative Method
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: Sri Chandrasekharendra Saraswathi Viswa Mahavidyalaya
 * ============================================================
 *
 * Objective:
 *   Compute the nth Fibonacci term and print the Fibonacci series
 *   using an iterative approach (no recursion).
 *
 * Mathematical Definition:
 *   F(0) = 0,  F(1) = 1
 *   F(n) = F(n-1) + F(n-2),  for n >= 2
 *
 * Algorithm:
 *   1. Read n and validate (n >= 0).
 *   2. Handle base cases: n=0 → print 0; n>=1 → print 0, 1.
 *   3. Initialize a = 0, b = 1.
 *   4. For i = 2 to n: compute next = a + b, print it, shift a = b, b = next.
 *   5. Report the nth term.
 *
 * Time Complexity  : O(n)  — Single loop
 * Space Complexity : O(1)  — Only 3 variables used
 * ============================================================
 */

#include <stdio.h>

int main()
{
    int n;
    long long a = 0, b = 1, next;

    printf("============================================\n");
    printf("  Experiment 2a: Fibonacci (Iterative)     \n");
    printf("  Student ID   : 11249A174                 \n");
    printf("============================================\n\n");

    printf("Enter the value of n (position, 0-indexed): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Error: Please enter a valid non-negative integer.\n");
        return 1;
    }

    printf("\nFibonacci Series: ");

    /* Handle first term */
    if (n >= 0)
        printf("%lld ", a);

    /* Handle second term */
    if (n >= 1)
        printf("%lld ", b);

    /* Iterative computation from 3rd term onwards */
    for (int i = 2; i <= n; i++) {
        next = a + b;
        printf("%lld ", next);
        a = b;
        b = next;
    }

    printf("\n\n");

    /* Report the nth Fibonacci term */
    if (n == 0)
        printf("Fibonacci term F(%d) = %lld\n", n, a);
    else
        printf("Fibonacci term F(%d) = %lld\n", n, b);

    return 0;
}
