// ------------------------------------------------ PROG 02 -------------------------------------------------------

// Michael Yu, CSS 501

// Created on: 11/4/2021

// Date of Last Modification: 11/4/2021

// ---------------------------------------------------------------------------------------------------------------

// Longest Common Subsequence (LCS)
// Purpose - Implement LCS using iterative, recursive, and recursive w/ memoization algorithms
// LCS algorithms should return the length of LCS. For iterative algorithm, backtrack() function returns LCS as string

#include "lcs.h"
#include <vector>

// Iterative LCS function that returns the length of LCS
// Pre-condition: C is (m+1) x (n+1) 2D array, where the 0th row and 0th column represent empty string.
// X is length m, Y is length n
// Post-condition: Length of LCS
int lcs_it(int** C, std::string X, std::string Y, int m, int n)
{
    // O(N^2) time complexity due to nested for loop
    for (int row = 1; row <= m; ++row)
    {
        for (int col = 1; col <= n; ++col)
        {
            // If the character in string X matches character in string Y, then
            // set C[row][col] to the value at C[row - 1][col - 1] and add 1
            // to indicate that the character is appended to LCS
            // Otherwise, set C[row][col] to the max value above or to left
            if (X[row - 1] == Y[col - 1])
            {
                C[row][col] = C[row - 1][col - 1] + 1;
            }
            else
            {
                C[row][col] = std::max(C[row][col - 1], C[row - 1][col]);
            }
        }
    }
    return C[m][n];
}

// Recursive function that returns one LCS string variant. Does not return all possible combinations
// Pre-condition: This function must be executed after lcs_it function, where the 2D array, C, has been populated
// with LCS data. String X is length m and String Y is length n. Both X and Y are from lcs_it
// Post-condition: LCS string
std::string backtrack(int** C, std::string X, std::string Y, int m, int n)
{
    if (m == 0 || n == 0) return "";

    if (X[m - 1] == Y[n - 1]) return backtrack(C, X, Y, m - 1, n - 1) + X[m - 1];

    if (C[m][n - 1] > C[m - 1][n]) return backtrack(C, X, Y, m, n - 1);

    return backtrack(C, X, Y, m - 1, n);
}

// Recursive LCS function without memoization that returns the length of LCS
// Pre-condition: X is length m, Y is length n
// Post-condition: Length of LCS
int lcs_re(std::string X, std::string Y, int m, int n)
{
    // O(N^2) due to 2 recursive calls per activation record
    // Starts at highest array indices and reduce problem towards 0 indices
    // Base case
    if (m == 0 || n == 0) return 0;

    // If there is a character match, then add 1 to the recursive output
    if (X[m - 1] == Y[n - 1]) return 1 + lcs_re(X, Y, m - 1, n - 1);

    // Otherwise, if not match, then take the max of recursive output from adjacent previous column and row
    return std::max(lcs_re(X, Y, m, n - 1), lcs_re(X, Y, m - 1, n));
}

// Recursive LCS function with memoization that returns the length of LCS. Helper function is provided to perform recursion
// Pre-condition: memo is 2D aux array that stores already visited characters, thus reducing computing time
// X is length m, Y is length n
// Post-condition: Length of LCS

// HELPER FUNCTION
int lcs_re_memo(std::vector<std::vector<int>>& memo, std::string X, std::string Y, int m, int n)
{
    // O(mn) due to 2 recursive calls per activation record if memoization array indicates element have not been visited yet
    // Base case
    if (m == 0 || n == 0) return 0;

    // If the character combination from X and Y is not computed, then execute code
    if (memo[m - 1][n - 1] == -1)
    {
        // If there is a character match, then add 1 to the recursive output
        // and cache it to the memo array
        if (X[m - 1] == Y[n - 1])
        {
            memo[m - 1][n - 1] = 1 + lcs_re_memo(memo, X, Y, m - 1, n - 1);
        }
        else
        {
            // Otherwise, if not match, then take the max of recursive output from adjacent previous column and row
            // and cache it to the memo array
            memo[m - 1][n - 1] = std::max(lcs_re_memo(memo, X, Y, m, n - 1), lcs_re_memo(memo, X, Y, m - 1, n));
        }
    }
    return memo[m - 1][n - 1];
}

// CALLING FUNCTION
int lcs_re_memo(std::string X, std::string Y, int m, int n)
{
    // Memoization array to indicate visited elements
    std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));

    return lcs_re_memo(memo, X, Y, m, n);
}

// Iterative LCS test wrapper function that creates 2D array and returns the length of LCS
// Pre-condition: X is length m, Y is length n
// Post-condition: Length of LCS
int lcs_it_test(std::string X, std::string Y, int m, int n)
{
    // Initialize 2D array as vector
    std::vector<std::vector<int>> C(m + 1, std::vector<int>(n + 1, 0));
    for (int row = 1; row <= m; ++row)
    {
        for (int col = 1; col <= n; ++col)
        {
            if (row == 0 || col == 0)
            {
                C[row][col] = 0;
            }
            else if (X[row - 1] == Y[col - 1])
            {
                C[row][col] = C[row - 1][col - 1] + 1;
            }
            else
            {
                C[row][col] = std::max(C[row][col - 1], C[row - 1][col]);
            }
        }
    }
    int length = C[m][n];
    return length;
}
