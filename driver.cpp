// ------------------------------------------------ PROG 02 -------------------------------------------------------

// Michael Yu, CSS 501

// Created on: 11/4/2021

// Date of Last Modification: 11/4/2021

// ---------------------------------------------------------------------------------------------------------------

// Longest Common Subsequence (LCS)
// Purpose - Implement LCS using iterative, recursive, and recursive w/ memoization algorithms
// LCS algorithms should return the length of LCS. For iterative algorithm, backtrack() function returns LCS as string

#include "lcs.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

// Driver Code
int main()
{
    std::string X;
    std::string Y;

    std::cout << "Input first string: ";
    std::cin >> X;
    std::cout << "X is " << X << std::endl;

    std::cout << "Input second string: ";
    std::cin >> Y;
    std::cout << "Y is " << Y << std::endl;

    // ========================================================================
    // Part 1 - Determine LCS and LCS length from string inputs using iterative algorithm
    int m = X.size();
    int n = Y.size();

    // Initialize 2D array to track LCS prefixes
    int** C = new int*[m + 1];
    for (int i=0; i < m + 1; ++i) C[i] = new int [n + 1];

    // Initialize 2D array, C, to 0s
    for (int i = 0; i < m + 1; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            C[i][j] = 0;
        }
    }

    int len = lcs_it(C, X, Y, m, n);

    std::cout << "Length of LCS (iterative): " << len << std::endl;
    std::cout << "LCS is " << backtrack(C, X, Y, m, n) << std::endl;

    // Deallocate memory for 2D array, C
    for (int i = 0; i < m + 1; i++) {
        delete[] C[i];
    }
    delete[] C;
    // ========================================================================

    // ========================================================================
    // Part 2 - Compare LCS algorithm complexity between iterative, recursive w/o memoization, and recursive w/ memoization
    // NOTE: Trial time for all recursive algorithms are the same
    std::cout << "Enter trial time for iterative version (less than min(|X|, |Y|)): ";
    size_t trialIt;
    std::cin >> trialIt;
    trialIt = std::min(trialIt, std::min(X.size(), Y.size()));

    std::cout << "Enter trial time for recursive version (less than 20): ";
    unsigned int trialRe;
    std::cin >> trialRe;
    trialRe = std::min(trialRe, 20u);

    // Iterative trials
    std::clog << "Iterative time trials (ms)" << std::endl;
    std::clog << std::setw(5) << "N" << std::setw(10) << "Time" << std::setw(10) << "LCS Length" << std::endl;
    for (int trial = 1; trial <= trialIt; ++trial)
    {
        std::string input1 = X.substr(0, trial);
        std::string input2 = Y.substr(0, trial);
        int start_s, stop_s;
        int length = 0;

        start_s=clock();
        length = lcs_it_test(input1, input2, trial, trial);
        stop_s=clock();

        std::clog << std::setw(5) << trial << std::setw(10) << std::setiosflags(std::ios::fixed) << std::setprecision(3) <<
                  (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::setw(10) << length << std::endl;
    }

    // Recursive w/o memoization trials
    std::clog << "Recursive without memoization time trials (ms)" << std::endl;
    std::clog << std::setw(5) << "N" << std::setw(10) << "Time" << std::setw(10) << "LCS Length" << std::endl;
    for (int trial = 1; trial <= trialRe; ++trial)
    {
        std::string input1 = X.substr(0, trial);
        std::string input2 = Y.substr(0, trial);
        int start_s, stop_s;
        int length = 0;

        start_s=clock();
        length = lcs_re(input1, input2, trial, trial);
        stop_s=clock();

        std::clog << std::setw(5) << trial << std::setw(10) << std::setiosflags(std::ios::fixed) << std::setprecision(3) <<
                  (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::setw(10) << length << std::endl;
    }

    // Recursive w/ memoization trials
    std::clog << "Recursive with memoization time trials (ms)" << std::endl;
    std::clog << std::setw(5) << "N" << std::setw(10) << "Time" << std::setw(10) << "LCS Length" << std::endl;
    for (int trial = 1; trial <= trialIt; ++trial)
    {
        std::string input1 = X.substr(0, trial);
        std::string input2 = Y.substr(0, trial);
        int start_s, stop_s;
        int length = 0;

        start_s=clock();
        length = lcs_re_memo(input1, input2, trial, trial);
        stop_s=clock();

        std::clog << std::setw(5) << trial << std::setw(10) << std::setiosflags(std::ios::fixed) << std::setprecision(3) <<
                  (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::setw(10) << length << std::endl;
    }
    // ========================================================================

    // ========================================================================
    // Unit test where string 1 = AACCTTGG and string 2 = ACACTGTGA
    // EXPECTED LCS = 6
    // LCS = AACTTG

    std::string input1 = "AACCTTGG";
    std::string input2 = "ACACTGTGA";

    int length1 = input1.size();
    int length2 = input2.size();

    std::cout << "Unit test to verify correct outputs" << std::endl;
    std::cout << "First input string: " << input1 << std::endl;
    std::cout << "Second input string: " << input2 << std::endl;

    std::cout << "LCS Iterative Algorithm" << std::endl;
    int** D = new int*[length1 + 1];
    for (int i=0; i < length1 + 1; ++i) D[i] = new int [length2 + 1];

    // Initialize 2D array, D, to 0s
    for (int i = 0; i < length1 + 1; ++i)
    {
        for (int j = 0; j < length2 + 1; ++j)
        {
            D[i][j] = 0;
        }
    }

    int lcs_length_it = lcs_it(D, input1, input2, length1, length2);
    std::string lcs = backtrack(D, input1, input2, length1, length2);

    std::cout << "Expected LCS length = 6" << " Actual LCS length = " << lcs_length_it <<
              " Test passed: " << std::boolalpha << (lcs_length_it == 6) << std::endl;

    std::cout << "Expected LCS = AACTTG" << " Actual LCS length = " << lcs <<
              " Test passed: " << std::boolalpha << (lcs == "AACTTG") << std::endl;

    std::cout << "LCS Recursive without Memoization Algorithm" << std::endl;
    int lcs_length_re_no_memo = lcs_re(input1, input2, length1, length2);
    std::cout << "Expected LCS length = 6" << " Actual LCS length = " << lcs_length_re_no_memo <<
              " Test passed: " << std::boolalpha << (lcs_length_re_no_memo == 6) << std::endl;

    std::cout << "LCS Recursive with Memoization Algorithm" << std::endl;
    int lcs_length_re_memo = lcs_re_memo(input1, input2, length1, length2);
    std::cout << "Expected LCS length = 6" << " Actual LCS length = " << lcs_length_re_memo <<
              " Test passed: " << std::boolalpha << (lcs_length_re_memo == 6) << std::endl;
    // ========================================================================

    // Deallocate memory for 2D array, D
    for (int i = 0; i < length1 + 1; i++) {
        delete[] D[i];
    }
    delete[] D;

    return 0;
}
