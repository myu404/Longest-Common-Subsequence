// ------------------------------------------------ PROG 02 -------------------------------------------------------

// Michael Yu, CSS 501

// Created on: 11/4/2021

// Date of Last Modification: 11/4/2021

// ---------------------------------------------------------------------------------------------------------------

// Longest Common Subsequence (LCS)
// Purpose - Implement LCS using iterative, recursive, and recursive w/ memoization algorithms
// LCS algorithms should return the length of LCS. For iterative algorithm, backtrack() function returns LCS as string

#ifndef LCS_H
#define LCS_H

#include <string>

// Iterative LCS function that returns the length of LCS
// Pre-condition: C is (m+1) x (n+1) 2D array, where the 0th row and 0th column represent empty string.
// X is length m, Y is length n
// Post-condition: Length of LCS
int lcs_it(int** C, std::string X, std::string Y, int m, int n);

// Recursive function that returns one LCS string variant. Does not return all possible combinations
// Pre-condition: This function must be executed after lcs_it function, where the 2D array, C, has been populated
// with LCS data. String X is length m and String Y is length n. Both X and Y are from lcs_it
// Post-condition: LCS string
std::string backtrack(int **C, std::string X, std::string Y, int m, int n);

// Recursive LCS function without memoization that returns the length of LCS
// Pre-condition: X is length m, Y is length n
// Post-condition: Length of LCS
int lcs_re(std::string X, std::string Y, int m, int n);

// Recursive LCS function with memoization that returns the length of LCS. Helper function is provided to perform recursion
// Pre-condition: memo is 2D aux array that stores already visited characters, thus reducing computing time
// X is length m, Y is length n
// Post-condition: Length of LCS
int lcs_re_memo(std::string X, std::string Y, int m, int n);

// Iterative LCS test wrapper function that creates 2D array and returns the length of LCS
// Pre-condition: X is length m, Y is length n
// Post-condition: Length of LCS
int lcs_it_test(std::string X, std::string Y, int m, int n);

#endif //LCS_H
