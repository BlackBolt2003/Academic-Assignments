/*
Implement Min, Max, Sum and Average operations using Parallel Reduction.
Measure the performance of sequential and parallel algorithms.
*/

#include <iostream>
#include <iomanip>
#include <omp.h>
#include <climits>
using namespace std;

int min_seq(int n, int *arr)
{
    int min = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        min = (min < arr[i]) ? min : arr[i];
    }
    return min;
}

int min_pll(int n, int *arr)
{
    int minimum = INT_MAX;
#pragma omp parallel for reduction(min : minimum)
    for (int i = 0; i < n; i++)
    {
        minimum = (minimum < arr[i]) ? minimum : arr[i];
    }
    return minimum;
}

int max_seq(int n, int *arr)
{
    int maximum = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        maximum = (maximum > arr[i]) ? maximum : arr[i];
    }
    return maximum;
}

int max_pll(int n, int *arr)
{
    int maximum = INT_MIN;
#pragma omp parallel for reduction(max : maximum)
    for (int i = 0; i < n; i++)
    {
        maximum = (maximum > arr[i]) ? maximum : arr[i];
    }
    return maximum;
}

int sum_seq(int n, int *arr)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int sum_pll(int n, int *arr)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

double avg_seq(int n, int *arr)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    return (sum / n);
}

double avg_pll(int n, int *arr)
{
    double sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return (sum / n);
}

void printArray(string msg, int n, int *arr)
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
    long int n = 10000000;
    int *arr = new int[n];
    double t1 = 0, t2 = 0;

    double ansSeq = 0, ansPll = 0;
    double tSeq = 0, tPll = 0;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % n;
    }

    cout << "\nN = " << n << endl;
    // printArray("\nNumbers:\t", n, arr);

    cout << endl
         << left
         << setw(20) << "Operation"
         << setw(20) << "Sequential"
         << setw(20) << "Time"
         << setw(20) << "Parallel"
         << setw(20) << "Time"
         << endl;

    cout << "--------------------------------------------------------------------------------------------" << endl;

    // Min ==================================
    // Sequencial
    t1 = omp_get_wtime();
    ansSeq = min_seq(n, arr);
    t2 = omp_get_wtime();
    tSeq = t2 - t1;

    // Parallel
    t1 = omp_get_wtime();
    ansPll = min_pll(n, arr);
    t2 = omp_get_wtime();
    tPll = t2 - t1;

    cout << left
         << setw(20) << "Min"
         << setw(20) << ansSeq
         << setw(20) << tSeq
         << setw(20) << ansPll
         << setw(20) << tPll
         << endl;

    // Max ==================================
    // Sequencial
    t1 = omp_get_wtime();
    ansSeq = max_seq(n, arr);
    t2 = omp_get_wtime();
    tSeq = t2 - t1;

    // Parallel
    t1 = omp_get_wtime();
    ansPll = max_pll(n, arr);
    t2 = omp_get_wtime();
    tPll = t2 - t1;

    cout << left
         << setw(20) << "Max"
         << setw(20) << ansSeq
         << setw(20) << tSeq
         << setw(20) << ansPll
         << setw(20) << tPll
         << endl;

    // Sum ==================================
    // Sequencial
    t1 = omp_get_wtime();
    ansSeq = sum_seq(n, arr);
    t2 = omp_get_wtime();
    tSeq = t2 - t1;

    // Parallel
    t1 = omp_get_wtime();
    ansPll = sum_pll(n, arr);
    t2 = omp_get_wtime();
    tPll = t2 - t1;

    cout << left
         << setw(20) << "Sum"
         << setw(20) << ansSeq
         << setw(20) << tSeq
         << setw(20) << ansPll
         << setw(20) << tPll
         << endl;

    // Average ==================================
    // Sequencial
    t1 = omp_get_wtime();
    ansSeq = avg_seq(n, arr);
    t2 = omp_get_wtime();
    tSeq = t2 - t1;

    // Parallel
    t1 = omp_get_wtime();
    ansPll = avg_pll(n, arr);
    t2 = omp_get_wtime();
    tPll = t2 - t1;

    cout << left
         << setw(20) << "Avg"
         << setw(20) << ansSeq
         << setw(20) << tSeq
         << setw(20) << ansPll
         << setw(20) << tPll
         << endl;

    cout << endl;

    return 0;
}