#include<iostream>
#include<cuda_runtime.h>
using namespace std;

__global__ void matrix_mul(int *a, int *b, int *c, int size){
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < size && col < size){
        int sum = 0;
        for(int i=0; i<size; i++){
            sum += a[row*size + i] * b[i*size + col];
        }
        c[row*size + col] = sum;
    }
}

void init_matrix(int *matrix, int size){
    for(int i=0; i<size*size; i++){
        matrix[i] = rand() % 10;
    }
}

void print_matrix(int *matrix, int size){
    for(int row=0; row<size; row++){
        for(int col=0; col<size; col++){
            cout << matrix[row*size + col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    int n = 4;
    int *a, *b, *c;
    int matrixSize = n * n;

    size_t matrixBytes = matrixSize * sizeof(int);

    a = new int[matrixSize];
    b = new int[matrixSize];
    c = new int[matrixSize];

    init_matrix(a, n);
    cout << "Matrix A:\n";
    print_matrix(a, n);

    init_matrix(b, n);
    cout << "Matrix B:\n";
    print_matrix(b, n);

    int *da, *db, *dc;
    cudaMalloc(&da, matrixBytes);
    cudaMalloc(&db, matrixBytes);
    cudaMalloc(&dc, matrixBytes);

    cudaMemcpy(da, a, matrixBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(db, b, matrixBytes, cudaMemcpyHostToDevice);

    int THREADS = 16;
    int BLOCKS = (n + THREADS - 1) / THREADS;

    dim3 threads(THREADS, THREADS);
    dim3 blocks(BLOCKS, BLOCKS);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    matrix_mul<<<blocks, threads>>>(da, db, dc, n);
    cudaError_t error = cudaGetLastError();
    if(error != cudaSuccess){
        cout << "CUDA Error: " << cudaGetErrorString(error) << endl;
    }
    cudaEventRecord(stop);

    cudaEventSynchronize(stop);
    cudaDeviceSynchronize();

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    cudaMemcpy(c, dc, matrixBytes, cudaMemcpyDeviceToHost);

    cout << "Resultant Matrix C:\n";
    print_matrix(c, n);

    cout << "\nKernel execution time: " << milliseconds << " ms" << endl;


    delete[] a;
    delete[] b;
    delete[] c;

    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);

    return 0;
}