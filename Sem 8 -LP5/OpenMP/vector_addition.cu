#include <stdio.h>
#include <cuda_runtime.h>

__global__ void vector_addition(float *A, float *B, float *C, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
    {
        C[i] = A[i] + B[i];
    }
}

void initialize(float *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % n;
    }
}

int main()
{
    int n = 1000;
    size_t size = n * sizeof(float);

    float *A = new float[n];
    float *B = new float[n];
    float *C = new float[n];

    initialize(A, n);
    initialize(B, n);

    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    vector_addition<<<1, n>>>(d_A, d_B, d_C, n);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    printf("Result Vector C:\t");
    for (int i = 0; i < n; i++)
    {
        printf("%f ", C[i]);
    }
    printf("\n");

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}