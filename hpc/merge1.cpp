// use -fopenmp as flag when compiling
#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void mergesort(int a[], int i, int j);
void merge(int a[], int i1, int j1, int i2, int j2);

void mergesort(int a[], int i, int j)
{
    int mid;
    if(i < j)
    {
        mid = (i + j) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergesort(a, i, mid);
            }

            #pragma omp section
            {
                mergesort(a, mid + 1, j);
            }
        }

        merge(a, i, mid, mid + 1, j);
    }
}

void merge(int a[], int i1, int j1, int i2, int j2)
{
    int temp[1000];
    int i = i1, j = i2, k = 0;

    while(i <= j1 && j <= j2)
    {
        if(a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while(i <= j1)
        temp[k++] = a[i++];

    while(j <= j2)
        temp[k++] = a[j++];

    for(i = i1, j = 0; i <= j2; i++, j++)
        a[i] = temp[j];
}

int main()
{
    int *a, *a_seq, *a_par, n, i;
    double start_time, end_time, seq_time, par_time;

    cout << "\nEnter total number of elements: ";
    cin >> n;

    a = new int[n];
    a_seq = new int[n];
    a_par = new int[n];

    cout << "\nEnter elements: ";
    for(i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // Copy input to two separate arrays
    for(i = 0; i < n; i++)
    {
        a_seq[i] = a[i];
        a_par[i] = a[i];
    }

    // Sequential mergesort
    start_time = omp_get_wtime();
    mergesort(a_seq, 0, n - 1);
    end_time = omp_get_wtime();
    seq_time = end_time - start_time;
    cout << "\nSequential Time: " << seq_time << " seconds";

    // Parallel mergesort
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergesort(a_par, 0, n - 1);
        }
    }
    end_time = omp_get_wtime();
    par_time = end_time - start_time;
    cout << "\nParallel Time: " << par_time << " seconds";

    // Output sorted array from parallel run
    cout << "\n\nSorted array (Parallel):";
    for(i = 0; i < n; i++)
    {
        cout << " " << a_par[i];
    }

    // Clean up memory
    delete[] a;
    delete[] a_seq;
    delete[] a_par;

    return 0;
}
