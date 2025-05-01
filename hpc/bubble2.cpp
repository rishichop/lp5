// use -fopenmp as flag when compiling
#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void sequentialBubbleSort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void parallelBubbleSort(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int phase = i % 2;
#pragma omp parallel for default(none) shared(a, n, phase)
        for (int j = phase; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void printArray(const string &label, int *a, int n) {
    cout << label;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter number of elements to sort: ";
    cin >> n;

    int *arr_seq = new int[n];
    int *arr_par = new int[n];

    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr_seq[i] = rand() % 100000;
        arr_par[i] = arr_seq[i]; // Copy to parallel version
    }

    double start = omp_get_wtime();
    parallelBubbleSort(arr_par, n);
    double end = omp_get_wtime();
    // printArray("Sorted array (Parallel):   ", arr_par, n);
    cout << "Time taken by Parallel Bubble Sort: " << end - start << " seconds\n";

    start = omp_get_wtime();
    sequentialBubbleSort(arr_seq, n);
    end = omp_get_wtime();
    // printArray("Sorted array (Sequential): ", arr_seq, n);
    cout << "\nTime taken by Sequential Bubble Sort: " << end - start << " seconds\n";

    // Uncomment to verify correctness
    // printArray(arr_seq, n);
    // printArray(arr_par, n);

    delete[] arr_seq;
    delete[] arr_par;

    return 0;
}
