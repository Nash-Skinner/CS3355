#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <array>
#include <cmath>
#include <algorithm>
using namespace std;

/*
    Using the pointer of an array until length l
    pass the values from -999 to 999 back to the array
*/
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

/*
    Naive Algorithm:
        Linear Max Weight anaylysis of subsets of an Array.
        Time Complexity: O(n^3) 
            -For ever loop n * n * n
        Space Complexity: O(1)
            -No copies of the array
*/
int iterativeMaxWeight(int A[], int l) {
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

// Simplfy logic finding maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }
 
// Simplfy logic finding maximum of three integers
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
 
 /*
    Divide-and-Conquer Algorithm:
        Recursive Max Weight anaylysis of subsets of an Array.
        Time Complexity: O(n log n)
            -T(n) = 2T(n/2) + O(n) = O(nlogn)
        Space Complexity: O(logn)
            -The recursive stack requires us to copy the array

    Returns sum of maximum sum subarray in aa[l..h]
*/
int recursiveMaxWeight(int arr[], int l, int h)
{
    // Base Case: Only one element
    if (l == h)
        return arr[l];
 
    // Find middle point
    int m = (l + h) / 2;
 
    /*  Return maximum of following three possible cases
            a) Maximum subarray sum in left half
            b) Maximum subarray sum in right half
            c) Maximum subarray sum such that the subarray
            crosses the midpoint 
    */
    return max(recursiveMaxWeight(arr, l, m),
               recursiveMaxWeight(arr, m + 1, h),
               maxCrossingSum(arr, l, m, h));
}

/*
    Time-Optimal Algorithm:
        Optimal Max Weight anaylysis of subsets of an Array.
        Time Complexity: O(n)
            -Only one iteration of the for loop from the Naive algorithm
        Space Complexity: O(1)
            -No copy of the array is necessary. 
*/
int optimalMaxWeight(int A[], int n) {
    int currentMax = 0;
    int endingMax = 0;
    
    //
    for (int i = 0; i < n-1; ++i) {
        endingMax += A[i];
        
        if(endingMax < 0)
            endingMax = 0;
        
        currentMax = max(currentMax, endingMax);
    }
   return currentMax;
}


int main() {
    // Initalized random valueation 
    srand (time(NULL));

    // Get user input for length of the Array
    int length = 0;
    cout << "Give the max length (> 500): ";
    cin >> length;

    // Make sure the Array does not exceed the Max or Min expected.
    // Else carry on with the computation
    if(length <= 0 or length > 500) {
        cout << "Rerun program with value less than or equal to 500."  << endl;
    } else {
        char printKey;
        int currentArray[length];
        fillArray(currentArray, length);

        // Allow user to see the array in a 10 by (Length / 10) matrix
        cout << "Do you want to print the array? (Y/N)";
        cin >> printKey;
        if (toupper(printKey) == 'Y'){
            readArray(currentArray, length);
        }
        
        // Variable to be used messuring the physical time complexatiy 
        clock_t start;

        /*
            Starts the clock for Iterative Max Weight
            Returns the Iterative Max Weight 
            and the Time cost in milliseconds
        */
        start = clock();
        cout << "Iterative Max Weight: " << iterativeMaxWeight(currentArray, length) << endl;
        cout << "Time for iterativeMaxWeight: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " in milliseconds\n";

        /*
            Starts the clock for Recursive Max Weight
            Returns the Recursive Max Weight 
            and the Time cost in milliseconds
        */
        start = clock();
        cout << "Recursive Max Weight: " << recursiveMaxWeight(currentArray, 0, length - 1) << endl;
        cout << "Time for recursiveMaxWeight: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " in milliseconds\n";

        /*  
            Starts the clock for Optimal Max Weight
            Returns the Optimal Max Weight 
            and the Time cost in milliseconds
         */
        start = clock();
        cout << "Optimal Max Weight: " << optimalMaxWeight(currentArray, length) << endl;
        cout << "Time for optimalMaxWeight: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " in milliseconds\n";
    }
    return 0;
}