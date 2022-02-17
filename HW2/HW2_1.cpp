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

// A utility function to find maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }
 
// A utility function to find maximum of three integers
int max(int a, int b, int c) { return max(max(a, b), c); }
 
// Find the maximum possible sum in arr[] auch that arr[m]
// is part of it
int maxCrossingSum(int arr[], int l, int m, int h)
{
    // Include elements on left of mid.
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; i--) {
        sum = sum + arr[i];
        if (sum > left_sum)
            left_sum = sum;
    }
 
    // Include elements on right of mid
    sum = 0;
    int right_sum = INT_MIN;
    for (int i = m + 1; i <= h; i++) {
        sum = sum + arr[i];
        if (sum > right_sum)
            right_sum = sum;
    }
 
    // Return sum of elements on left and right of mid
    // returning only left_sum + right_sum will fail for
    // [-2, 1]
    return max(left_sum + right_sum, left_sum, right_sum);
}
 
// Returns sum of maximum sum subarray in aa[l..h]
int recursiveMaxWeight(int arr[], int l, int h)
{
    // Base Case: Only one element
    if (l == h)
        return arr[l];
 
    // Find middle point
    int m = (l + h) / 2;
 
    /* Return maximum of following three possible cases
            a) Maximum subarray sum in left half
            b) Maximum subarray sum in right half
            c) Maximum subarray sum such that the subarray
       crosses the midpoint */
    return max(recursiveMaxWeight(arr, l, m),
               recursiveMaxWeight(arr, m + 1, h),
               maxCrossingSum(arr, l, m, h));
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

        // readArray(currentArray, length);

        clock_t start;
        start = clock();
        cout << "Iterative Max Weight: " << iterativeMaxWeight(currentArray, length) << endl;
        cout << "Time for iterativeMaxWeight: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " in milliseconds\n";

        start = clock();
        cout << "Recursive Max Weight: " << recursiveMaxWeight(currentArray, 0, length - 1) << endl;
        cout << "Time for recursiveMaxWeight: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " in milliseconds\n";

        start = clock();
        cout << "Optimal Max Weight: " << optimalMaxWeight(currentArray, length) << endl;
        cout << "Time for optimalMaxWeight: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " in milliseconds\n";
    }
    return 0;
}