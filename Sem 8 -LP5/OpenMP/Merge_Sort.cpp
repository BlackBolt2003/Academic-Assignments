// Sequencial and Parallel Merge sort

#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void merge(int *&arr, int st, int mid, int en)
{
    // create left and right arrays
    int nl = mid + 1 - st;
    int nr = en - mid;

    int *left = new int[nl];
    int *right = new int[nr];

    // copy arrays
    for (int i = 0; i < nl; i++)
        left[i] = arr[st + i];

    for (int j = 0; j < nr; j++)
        right[j] = arr[mid + 1 + j];

    // compare two arrays and place elements in original array
    int i = 0, j = 0, k = st;

    while (i < nl && j < nr)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // If any array is non-empty
    while (i < nl)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < nr)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(int st, int en, int *&arr)
{
    if (st < en)
    {
        int mid = (st + en) / 2;
        merge_sort(st, mid, arr);
        merge_sort(mid + 1, en, arr);
        merge(arr, st, mid, en);
    }
}

void parallel_merge_sort(int st, int en, int *&arr)
{
    if (st < en)
    {
        int mid = (st + en) / 2;

#pragma omp parallel sections num_threads(2)
        {
#pragma omp section
            merge_sort(st, mid, arr);

#pragma omp section
            merge_sort(mid + 1, en, arr);
        }
        merge(arr, st, mid, en);
    }
}

void print_array(string msg, int n, int *&arr)
{
    cout << msg;
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n = 10;
    int *arr = new int[n];
    double t1 = 0, t2 = 0;

    // set array
    for (int i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }

    // Sequencial Merge Sort
    printf("\nSequencial Merge Sort:\n");
    print_array("Before Sorting:\t", n, arr);

    t1 = omp_get_wtime();
    merge_sort(0, n - 1, arr);
    t2 = omp_get_wtime();

    print_array("After Sorting:\t", n, arr);

    printf("\nTime:\t%lf\n", t2 - t1);

    // reset array
    for (int i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }

    // Parallel Merge sort
    printf("\nParallel Merge Sort:\n");
    print_array("Before Sorting:\t", n, arr);

    t1 = omp_get_wtime();
    parallel_merge_sort(0, n - 1, arr);
    t2 = omp_get_wtime();

    print_array("After Sorting:\t", n, arr);

    printf("\nTime:\t%lf\n", t2 - t1);

    return 0;
}