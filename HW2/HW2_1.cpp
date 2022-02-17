#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <array>
using namespace std;

const int n = 10;

class ArrayFuctions {
    public:
        array<int, n> myArray;

    void fillArray() {
            for (int i = 0; i <= n; ++i) {
                //myArray[i] = (rand() % 1998 + (-999));
                myArray[i] = (rand() % 10 + (-5));
            }
    }

    void readArray() {
        cout << "Reading someArray elements.\n";

        // prefer using size_t for lengths and sizes, instead of int
        for (int i = 0; i <= n; ++i) {
            cout << myArray[i] << " , ";
            if(i != 0 && i % 10 == 0) {
                cout << endl;
            }
        }
    }

    int iterativeMaxWeight() {
        if (myArray.empty()) {
            return 0;
        }

        int bestSum = 0, currentSum = 0;
        int bestStart = 0, currentStart = 0;
        int bestEnd = 0, currentEnd = 0;
        
        for(int i = 0; i < n; ++i) {
            if(currentSum <= 0) {
                currentStart = currentEnd;
                currentSum = myArray[i];
            }
            else {
                currentSum += myArray[i];
            }

            if(currentSum > bestSum) {
                bestSum = currentSum;
                bestStart = currentStart;
                bestEnd = currentEnd + 1; 
            }
        }

        cout << bestSum << " , " << bestStart << " , " << bestEnd << endl;
        return(bestSum);
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