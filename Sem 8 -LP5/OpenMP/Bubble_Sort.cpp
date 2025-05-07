// Sequencial and Parallel Bubble sort

#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void bubble_sort(int n, int *&arr)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void parallel_bubble_sort(int n, int *&arr)
{
    for (int i = 0; i < n; i++)
    {
        int start = i%2;    // check if term is even or odd
        #pragma omp parallel for num_threads(4)
        for(int j = start; j < n - 1; j += 2){
            if (arr[j] > arr[j+1]) swap(arr[j], arr[j+1]);
        }
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
    double t1=0, t2=0;

    // set array
    for (int i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }

    // Sequencial Bubble Sort
    printf("\nSequencial Bubble Sort:\n");
    print_array("Before Sorting:\t", n, arr);

    t1 = omp_get_wtime();
    bubble_sort(n, arr);
    t2 = omp_get_wtime();

    print_array("After Sorting:\t", n, arr);

    printf("\nTime:\t%lf\n", t2 - t1);

    // reset array
    for (int i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }

    // Parallel Bubble sort
    printf("\nParallel Bubble Sort:\n");
    print_array("Before Sorting:\t", n, arr);

    t1 = omp_get_wtime();
    parallel_bubble_sort(n, arr);
    t2 = omp_get_wtime();

    print_array("After Sorting:\t", n, arr);

    printf("\nTime:\t%lf\n", t2 - t1);

    return 0;
}