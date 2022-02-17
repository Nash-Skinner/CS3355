#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <array>
#include <cmath>
#include <algorithm>
using namespace std;

void fillArray(int* a, int l) {
    for (int i = 0; i < l; ++i) {
        a[i] = (rand() % 1998 + (-999));
    }
}

// Print out an Array.
void readArray(int A[], int l) {
    cout << "Reading elements.\n";
    for (int i = 0; i < l; ++i) {
        cout << A[i] << " , ";
        if(i != 0 && i % 9 == 0) 
            cout << endl;
    }
    cout << endl;
}

// Linear Max Weight anaylysis of subsets of an Array.
int iterativeMaxWeight(int A[], int l) {
    // If the array is empty there is no weight
    if (l == 0) {
        return 0;
    }

    int maxSum = 0;
    for(int i = 0; i < l; ++i) {
        for(int j = i; j <= l; ++j) {  
            int sum = 0;
            for(int k = i; k <= j; ++k)
                sum = sum + A[k];
            if(sum > maxSum)
                maxSum = sum;
        }
    } 
    return(maxSum);
}

// Compute the Crossing Sum for the function recursive Max Weight
int maxCrossingSum(int currentArray[], int low, int mid, int r) {
    int sum = 0;
    int lsum = INT_MIN;
    for(int i = mid; i > low; --i) {
        sum = sum + currentArray[i];
        if (sum > lsum)
            lsum = sum;
    }
    sum = 0;
    int rsum = INT_MIN;
    for(int i = mid+1; i < r; ++i) {
        sum = sum + currentArray[i];
        if (sum > rsum)
            rsum = sum;
    }
    return (lsum + rsum);
}

// Recursive Max Weight anaylysis of subsets of an Array.
int recursiveMaxWeight(int A[], int low, int high) {
    if (low == high)
        return A[low];
    else {
        int mid = low + floor ((high - low)/2);
        int left_sum = recursiveMaxWeight (A, low, mid);
        int right_sum = recursiveMaxWeight (A, mid+1, high);
        int crossing_Sum = maxCrossingSum(A, low, mid, high);

        cout << left_sum << " , " << crossing_Sum << " , " << right_sum << endl;

        if(left_sum > right_sum && left_sum > crossing_Sum) {
            return left_sum;
        } 
        if (right_sum > crossing_Sum){
            return right_sum;
        }
        else{
            return(crossing_Sum);   
        }
    }
}

// Optimal Max Weight anaylysis of subsets of an Array.
int optimalMaxWeight(int A[], int n) {
    int max_so_far = 0;
    int max_ending_here = 0;
    for (int i = 0; i < n-1; ++i) {
        max_ending_here += A[i];
        
        if( max_ending_here < 0 )
            max_ending_here = 0;
        
        max_so_far = max(max_so_far, max_ending_here);
    }
   return max_so_far;
}


int main() {
    srand (time(NULL));

    int length = 0;
    cout << "Give the max length (> 500): ";
    cin >> length;

    if(length <= 0 or length > 500) {
        cout << "Rerun program with value less than or equal to 500."  << endl;
    } else {
        int currentArray[length];
        fillArray(currentArray, length);

        readArray(currentArray, length);
        cout << iterativeMaxWeight(currentArray, length) << endl;
        cout << recursiveMaxWeight(currentArray, 0, length - 1) << endl;
        cout << optimalMaxWeight(currentArray, length) << endl;
    }
    return 0;
}