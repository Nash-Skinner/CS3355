#include <iostream>
#include <time.h>

 /*
    Utility Function - to fill an array with a spread of values
    Pre: An arbitrary array length n 
    Post: Returns an array with arbirary length carrying numbers 0 to 999
 */ 
void fillArray(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = (rand() % 999);
    }
}

/* 
    Utility Function - to print array by powers of 2
    Pre: An arbitrary array length n 
    Post: A heap display printed to console
*/
void displayArray(int* arr, int n) {
    int currPow2 = 0;

    for (int i=0; i<n; ++i){
        if(i >= currPow2) {
            std::cout << std::endl;
            currPow2 = currPow2 * 2 + 1;
        }
        std::cout << arr[i] << " ";
    }

   std::cout << "\n\n";
}

/*
    Function to heapify the tree
    Pre: An arbitrary array length n with known root
    Post: Returns heap_array length n
*/
void heapify(int* arr, int n, int root) {
    int largest = root; // root is the largest element
    int l = 2*root + 1; // left = 2*root + 1
    int r = 2*root + 2; // right = 2*root + 2
  
    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
    largest = l;
  
    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
    largest = r;
  
    // If largest is not root
    if (largest != root) {
        //swap root and largest
        std::swap(arr[root], arr[largest]);
  
        // Recursively heapify the sub-tree
        heapify(arr, n, largest);
    }
}
  
/*
    Implementing heap sort
    Pre: An arbitrary array length n 
    Post: Returns a built: numberically sorted heap_heap based on the lowest value
*/
void heapSort(int* arr, int n) {
    // build heap
    for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);
  
    // extracting elements from heap one by one
    for (int i=n-1; i>=0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);

        // again call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
  
/* main program */
int main() {
    // Initalized random valueation 
    srand(time(NULL));

    int length = 0;
    std::cout << "Give the max length: ";
    std::cin >> length;

    int heap_arr[length];
    fillArray(heap_arr, length);

    std::cout<<"Input array:"<<std::endl;
    displayArray(heap_arr,length);
  
    heapSort(heap_arr, length);
  
    std::cout << "Sorted array:"<<std::endl;
    displayArray(heap_arr, length);
}