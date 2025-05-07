#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

// The OpenMP library is included with the <omp.h> header file.

// (1) Print "Hello World!" using OpenMP
// This is a simple example of using OpenMP to parallelize a task.
void simplePrint()
{
#pragma omp parallel // Specify parallel region
    {
        printf("Hello World!\n");
    }
}

// (2) Print "Hello World!" using OpenMP with specified number of threads
// This example demonstrates how to set the number of threads for parallel execution
void specifiedThreadsPrint()
{
    omp_set_num_threads(4); // Specify number of thread (default = 8)
    int threadId;
#pragma omp parallel
    {
        threadId = omp_get_thread_num(); // Obtain thread ID
        printf("Thread %d: Hello World!\n", threadId);
    }
}

// (3) Calculate the sum of numbers from 1 to N using OpenMP
// This example demonstrates how to use OpenMP to parallelize a loop for summation
// The sum is calculated by dividing the work among multiple threads
// Each thread computes a partial sum, and the final result is obtained by combining these partial sums
void parallelSumTillN(int N)
{
    int i, sum = 0;
    int thread_sum[4];

    omp_set_num_threads(4);
#pragma omp parallel
    {
        int ID = omp_get_thread_num();
        thread_sum[ID] = 0;

#pragma omp for
        for (i = 1; i < N; i++)
        {
            thread_sum[ID] += i;
        }
    }
    for (i = 0; i < 4; i++)
    {
        sum += thread_sum[i];
    }

    printf("Sum till %d= %d\n", N, sum);
}

// (4) Shared vs Private Variables in OpenMP
/*
    Shared Vars -> Shared among all threads
    Private Vars -> Each thread in a team of threads has its own local copy of the variable.

    Implicit Rules:
    +---------------------------------------------------------------+
    |   Var. Declaration                |   Default Access Control  |
    |---------------------------------------------------------------|
    |   1) Outside Parallel region      |   Shared                  |
    |   2) Loop iteration var           |   Private                 |
    |   3) Local inside parallel region |   Private                 |
    +---------------------------------------------------------------+
*/

// (5) Counter using critical section
// This example demonstrates the use of a critical section to ensure that only one thread at a time can access a shared resource
// In this case, the shared resource is the counter variable
void counterUsingCriticalSection()
{
    int limit = 10;
    int counter = 0;

    // without critical section -> counter is out of order, may not reach 10
    // This is because multiple threads are trying to update the counter variable simultaneously
    printf("Counter without critical section:\n");
#pragma omp parallel num_threads(4)
    {
        int ID = omp_get_thread_num();
#pragma omp for
        for (int i = 0; i < limit; i++)
        {
            printf("Thread %d: %d\n", ID, counter++);
        }
    }
    printf("Final counter= %d\n\n", counter);

    limit = 10;
    counter = 0;

    // with critical section -> counter stays in order, will reach 10
    // This is because the critical section ensures that only one thread can access the counter variable at a time
    printf("Counter using critical section:\n");
#pragma omp parallel num_threads(4)
    {
        int ID = omp_get_thread_num();
#pragma omp for
        for (int i = 0; i < limit; i++)
        {
#pragma omp critical
            printf("Thread %d: %d\n", ID, counter++);
        }
    }
    printf("Final counter= %d\n\n", counter);
}

// (6) Atomics
void atomicUpdate()
{
    // count no. of threads without Atomic
    int counter = 0;
    int MAX = 10;

#pragma omp parallel num_threads(MAX)
    {
        counter++;
    }

    printf("Max without atomic= %d\n", counter);

    // count no. of threads using Atomic
    counter = 0;

#pragma omp parallel num_threads(MAX)
    {
#pragma omp atomic update
        counter++;
    }

    printf("Max using atomic= %d\n", counter);
}

void atomicRead()
{
    // without atomic read
    int n = 100;
    int arr[n];
    int max = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
        cout << arr[i] << endl;
    }

#pragma omp parallel for num_threads(2)
    for (int i = 0; i < n; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }

    cout << "Max= " << max << endl;

    // with atomic read
    max = INT_MIN;

#pragma omp parallel for num_threads(2)
    for (int i = 0; i < n; i++)
    {
        if (max < arr[i])
        {
#pragma omp atomic read
            max = arr[i];
        }
    }

    cout << "Max= " << max << endl;
}

// (7) Conditional
void chcekConditional(int val)
{
#pragma omp parallel if (val > 5)
    if (omp_in_parallel())
    {
#pragma omp single
        printf("Val = %d <= 5, Parallelized by %d threads.\n", val, omp_get_num_threads());
    }
    else
    {
        printf("Val = %d > 5, Serialized\n", val);
    }
}

// (8) Reduction
void sumByReduction(int N)
{
    int sum = 0;

#pragma omp parallel for num_threads(4) reduction(+ : sum)
    for (int i = 0; i < N; i++)
    {
        sum += i;
    }

    printf("Sum by Reduction= %d\n", sum);
}

void minByReduction(int N)
{
    int minimum = INT_MAX;
    int *arr = new int[N];

    for (int i = 0; i < N; i++){
        arr[i] = rand();
        // printf("%d\n", arr[i]);
    }

#pragma omp parallel for num_threads(4) reduction(min : minimum)
    for (int i = 0; i < N; i++)
    {
        if (minimum > arr[i])
        {
            minimum = arr[i];
        }
    }

    printf("Min by Reduction= %d\n", minimum);
}

int main()
{
    // simplePrint();                   // (1) Print "Hello World!" using OpenMP
    // specifiedThreadsPrint();         // (2) Print "Hello World!" using OpenMP with specified number of threads
    // parallelSumTillN(1000);          // (3) Calculate the sum of numbers from 1 to N using OpenMP
    // counterUsingCriticalSection();   // (5) Counter using critical section

    // atomicUpdate();                  // (6) Atomic: Update
    // atomicRead();                    //     Atomic: Read

    // chcekConditional(3);             // (7) Conditional
    // chcekConditional(7);

    sumByReduction(100);                // (8) Reduction
    minByReduction(10);
    return 0;
}