#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <array>
using namespace std;

const int n = 500;

class ArrayFuctions {
    public:
        array<int, n> myArray;

    // Fill in an Array of length n with values -999 to 999.
    void fillArray() {
            for (int i = 0; i <= n; ++i) {
                myArray[i] = (rand() % 1998 + (-999));
                //myArray[i] = (rand() % 10 + (-5));
            }
    }

    // Print out an Array.
    void readArray() {
        cout << "Reading elements.\n";
        for (int i = 0; i <= n; ++i) {
            cout << myArray[i] << " , ";
            if(i != 0 && i % 10 == 0) {
                cout << endl;
            }
        }
    }

    // Linear Max Weight anaylysis of subsets of an Array.
    int iterativeMaxWeight() {
        // If the array is empty there is no weight
        if (myArray.empty()) {
            return 0;
        }

        int maxSum = 0;
        for(int i = 0; i <= n; ++i) {
            for(int j = i; j <= n; ++j) {  
                int sum = 0;
                for(int k = i; k <= j; ++k)
                    sum = sum + myArray[k];
                if(sum > maxSum)
                    maxSum = sum;
            }
        } 

        return(maxSum);
    }

    int recursiveMaxWeight() {
        return 0;
    }

    int optimalMaxWeight() {
        return 0;
    }
};


int main() {
    srand (time(NULL));

    ArrayFuctions startArray;

    startArray.fillArray();
    startArray.readArray();
    cout << startArray.iterativeMaxWeight() << endl;

    return 0;
}