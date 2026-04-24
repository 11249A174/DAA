/*
 * ============================================================
 * Experiment 1: Tower of Hanoi Using Recursion
 * ============================================================
 * Student ID : 11249A174
 * Course     : Design and Analysis of Algorithms
 * Course Code: BCSF244T40 / BCSF244P80
 * Institution: Sri Chandrasekharendra Saraswathi Viswa Mahavidyalaya
 * ============================================================
 *
 * Objective:
 *   Implement the Tower of Hanoi problem using the Divide and
 *   Conquer (Recursion) paradigm.
 *
 * Algorithm:
 *   1. Base Case: If n == 1, move disk directly from Source to Destination.
 *   2. Move (n-1) disks from Source to Auxiliary using Destination as temp.
 *   3. Move the nth disk from Source to Destination.
 *   4. Move (n-1) disks from Auxiliary to Destination using Source as temp.
 *
 * Time Complexity  : O(2^n) — Exponential
 * Space Complexity : O(n)   — Recursive stack depth
 * Recurrence       : T(n) = 2T(n-1) + 1
 * Total Moves      : 2^n - 1
 * ============================================================
 */

#include <stdio.h>

/**
 * towerOfHanoi - Recursively solves the Tower of Hanoi problem.
 * @diskNumber : Number of disks to move
 * @source     : Starting rod
 * @destination: Target rod
 * @auxiliary  : Intermediate (helper) rod
 */
void towerOfHanoi(int diskNumber, char source, char destination, char auxiliary)
{
    /* Base Condition: Only one disk — move it directly */
    if (diskNumber == 1) {
        printf("  Move disk 1 from %c to %c\n", source, destination);
        return;
    }

    /* Step 1: Move top (n-1) disks from Source to Auxiliary */
    towerOfHanoi(diskNumber - 1, source, auxiliary, destination);

    /* Step 2: Move the nth (largest remaining) disk to Destination */
    printf("  Move disk %d from %c to %c\n", diskNumber, source, destination);

    /* Step 3: Move (n-1) disks from Auxiliary to Destination */
    towerOfHanoi(diskNumber - 1, auxiliary, destination, source);
}

int main()
{
    int n;

    printf("============================================\n");
    printf("  Experiment 1: Tower of Hanoi (Recursion) \n");
    printf("  Student ID  : 11249A174                  \n");
    printf("============================================\n\n");

    printf("Enter the number of disks: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Please enter a valid positive integer.\n");
        return 1;
    }

    printf("\nTotal moves required: %d\n\n", (1 << n) - 1);  /* 2^n - 1 */
    printf("Step-by-step moves:\n");
    printf("-------------------\n");
    towerOfHanoi(n, 'S', 'D', 'A');

    printf("\n-------------------\n");
    printf("Rods: S = Source | A = Auxiliary | D = Destination\n");

    return 0;
}
