//
//  main.cpp
//  Program4LCS
//
//  Created by Mark Stewart on 11/4/21.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;



int lcs_it(int** C, string X, string Y, int m, int n ) {
    // initialize first arrays to zero
    for (int i = 0; i <= m; i++) {
        C[0][i] = 0;
    }
    for (int i = 0; i <= n; i++) {
        C[i][0] = 0;
    }
    
    int lcsLength = 0;
    //Row
    for (int y = 0; y < n; y++) {
        char yChar = Y[y];
        //Column
        for (int x = 0; x < m; x++) {
            char xChar = X[x];
            // matrix indecies + 1 to leave first arrays of zero buffer
            int cX = x + 1;
            int cY = y + 1;
            if (xChar == yChar) {
                int upperLeftVal = C[cY - 1][cX - 1];
                C[cY][cX] = upperLeftVal + 1;
            } else {
                int upperVal = C[cY - 1][cX];
                int leftVal = C[cY][cX - 1];
                C[cY][cX] = max(upperVal, leftVal);
            }
            lcsLength = max(lcsLength, C[cY][cX]);
        }
    }
    return lcsLength;
}

string backtrack(int **C, string X, string Y, int m, int n) {
    string lcs;
    
    return "";
}

int main(int argc, const char * argv[]) {
    ifstream myReadFile("/Users/markstewart/Desktop/input.txt");
    string X;
    string Y;
    while(myReadFile >> X >> Y);
//    X = "abcdefg";
//    Y = "defghij";
    
    int m = static_cast<int>(X.size());
    int n = static_cast<int>(Y.size());
    int** C = new int* [m+1];
    for (int i = 0; i < m + 1; ++i) C[i]=new int [n + 1];
    int len = lcs_it(C, X, Y, m, n);
    cout << len;
    cout<<" LCS is "<<backtrack(C, X, Y, m, n)<<endl;

    return 0;
}
//    a b z d e f a
//    0 0 0 0 0 0 0
//b 0 0 1 0 0 0 0 0
//z 0 0 1 2 2 2 2 2
//f 0 0 1 2 2 2 3 3
//d 0 0 1 2 3 3 3 3
//e 0 0 1 2 3 4 4 4
//a 0 1 1 2 3 4 4 4 <--- this is not incremented to 5?
//z 0 1 1 2 3 4 4 4
//
//bzfa (length of 4)
