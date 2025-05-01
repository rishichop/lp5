// use -fopenmp as flag when compiling
#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void merge(int a[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void sequentialMergeSort(int a[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        sequentialMergeSort(a, left, mid);
        sequentialMergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

void parallelMergeSort(int a[], int left, int right, int depth = 0) {
    const int threshold = 1000; // Only parallelize if large enough

    if (left < right) {
        int mid = (left + right) / 2;

        if ((right - left) > threshold && depth < 4) { // Prevent too much nesting
#pragma omp parallel sections
            {
#pragma omp section
                parallelMergeSort(a, left, mid, depth + 1);
#pragma omp section
                parallelMergeSort(a, mid + 1, right, depth + 1);
            }
        } else {
            sequentialMergeSort(a, left, mid);
            sequentialMergeSort(a, mid + 1, right);
        }

        merge(a, left, mid, right);
    }
}

void printSample(const string &label, int a[], int n) {
    cout << label << " [";
    for (int i = 0; i < min(n, 10); i++)
        cout << a[i] << (i < min(n, 10) - 1 ? ", " : "");
    if (n > 10)
        cout << "...";
    cout << "]\n";
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int *original = new int[n];
    int *a_seq = new int[n];
    int *a_par = new int[n];

    srand(time(0));
    for (int i = 0; i < n; i++) {
        original[i] = rand();
        a_seq[i] = original[i];
        a_par[i] = original[i];
    }

    printSample("Original sample:", original, n);

    // Parallel sort
    double start = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        parallelMergeSort(a_par, 0, n - 1);
    }
    double end = omp_get_wtime();
    cout << "Time taken by Parallel Merge Sort: " << (end - start) << " seconds\n";

    printSample("Sorted (Parallel) sample:", a_par, n);

    // Sequential sort
    start = omp_get_wtime();
    sequentialMergeSort(a_seq, 0, n - 1);
    end = omp_get_wtime();
    cout << "Time taken by Sequential Merge Sort: " << (end - start) << " seconds\n";

    printSample("Sorted (Sequential) sample:", a_seq, n);

    delete[] original;
    delete[] a_seq;
    delete[] a_par;

    return 0;
}
