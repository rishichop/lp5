// use -fopenmp as flag when compiling
#include <iostream>
#include <omp.h>

using namespace std;

void sequentialBubbleSort(int *, int);
void parallelBubbleSort(int *, int);
void swap(int &, int &);

void sequentialBubbleSort(int *a, int n)
{
    int swapped;
    for (int i = 0; i < n; i++)
    {
        swapped = 0;
        for (int j = 0; j < n - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

void parallelBubbleSort(int *a, int n)
{
    int swapped;
    for (int i = 0; i < n; i++)
    {
        swapped = 0;
        // Odd and even indexed pass optimization
        #pragma omp parallel for shared(a) reduction(|:swapped)
        for (int j = (i % 2); j < n - 1; j += 2) // Handle odd and even index separately
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

void swap(int &a, int &b)
{
    int test = a;
    a = b;
    b = test;
}

int main()
{
    int *a, *b, n;
    cout << "\nEnter total number of elements: ";
    cin >> n;
    a = new int[n];
    b = new int[n]; // Create a second array for parallel sorting

    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        b[i] = a[i]; // Duplicate input data into second array
    }

    // Sequential Bubble Sort
    double start_time = omp_get_wtime(); // Start timer for sequential algorithm
    sequentialBubbleSort(a, n);
    double end_time = omp_get_wtime(); // End timer for sequential algorithm

    cout << "\nSorted array using sequential algorithm: ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "Time taken by sequential algorithm: " << end_time - start_time << " seconds" << endl;

    // Parallel Bubble Sort
    start_time = omp_get_wtime(); // Start timer for parallel algorithm
    parallelBubbleSort(b, n);
    end_time = omp_get_wtime(); // End timer for parallel algorithm

    cout << "\nSorted array using parallel algorithm: ";
    for (int i = 0; i < n; i++)
    {
        cout << b[i] << " ";
    }
    cout << endl;

    cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds" << endl;

    delete[] a; // Free the allocated memory for the first array
    delete[] b; // Free the allocated memory for the second array

    return 0;
}
