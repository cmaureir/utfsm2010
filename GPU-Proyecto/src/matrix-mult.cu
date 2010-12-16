#include <iostream>
#include <iomanip>
#include <time.h>
#include <cuda_runtime_api.h>
#include <fstream>
using namespace std;
using std::ifstream;
#define BLOCK_SIZE  16

// max 40
// 32
// 25
// 20
// 16
// 10
// 8
// 4
// min 2

// Device multiplication function called by Mul()
// Compute C = A * B
//	wA is the width of A
//	wB is the width of B

float A[1600][1600],B[1600][1600];

__global__ void Muld(float* A, float* B, int wA, int wB, float* C)
{
	// Block index
	int bx = blockIdx.x;
	int by = blockIdx.y;

	// Thread index
	int tx = threadIdx.x;
	int ty = threadIdx.y;

	// Index of the first sub-matrix of A processed by the block
	int aBegin = wA * BLOCK_SIZE * by;

	// Index of the last sub-matrix of A processed by the block
	int aEnd = aBegin + wA - 1;

	// Step size used to iterate through the sub-matrices of A
	int aStep = BLOCK_SIZE;

	// Index of the first sub-matrix of B processed by the block
	int bBegin = BLOCK_SIZE * bx;

	// Step size used to iterate through the sub-matrices of B
	int bStep = BLOCK_SIZE * wB;

	// The element of the block sub-matrix that is computed by the thread
	float Csub = 0;

	// Loop	over all the sub-matrices of A and B required to compute the block
	for (int a = aBegin, b = bBegin; 
		a <= aEnd;
		a += aStep, b += bStep) {

		// Shared memory for the sub-matrix of A
		__shared__ float As[BLOCK_SIZE][BLOCK_SIZE];

		// Shared memory for the sub-matrix of B
		__shared__ float Bs[BLOCK_SIZE][BLOCK_SIZE];

		// Load the matrices from global memory to shared memory;
		// each thread loads one element of each matrix
		As[ty][tx] = A[a + wA * ty + tx];
		Bs[ty][tx] = B[b + wB * ty + tx];

		// Synchronize to make sure the matrices are loaded
		__syncthreads();

		// Multiply the two matrices together;
		// each thread computes one element
		// of the block sub-matrix
		for (int k = 0; k < BLOCK_SIZE; ++k)
			Csub += As[ty][k] * Bs[k][tx];

		// Synchronize to make sure that the preceding
		// computation is done before loading two new
		// sub-matrices of A and B in the next iteration
		__syncthreads();
	}

	// Write the block sub-matrix to global memory;
	// each thread writes one element

	int c = wB * BLOCK_SIZE * by + BLOCK_SIZE * bx;
	C[c + wB * ty + tx] = Csub;
}
// Host multiplication function
// Compute C = A * B
// 	hA is the height of A
// 	wA is the width of A
//	wB is the width of B

void Mul(const float* A, const float* B, int hA, int wA, int wB,float* C)
{
	int size;
	// Load A and B to the device
	float* Ad;
	size = hA * wA * sizeof(float);
	cudaMalloc((void**)&Ad, size);
	cudaMemcpy(Ad, A, size, cudaMemcpyHostToDevice);

	float* Bd;
	size = wA * wB * sizeof(float);
	cudaMalloc((void**)&Bd, size);
	cudaMemcpy(Bd, B, size, cudaMemcpyHostToDevice);

	// Allocate C on the device
	float* Cd;
	size = hA * wB * sizeof(float);
	cudaMalloc((void**)&Cd, size);

	// Compute the execution configuration assuming
	// the matrix dimensions are multiples of BLOCK_SIZE
	dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
	dim3 dimGrid(wB / dimBlock.x, hA / dimBlock.y);

	// Launch the device computation
	Muld<<<dimGrid, dimBlock>>>(Ad, Bd, wA, wB, Cd);

	//cout << cudaGetErrorString(cudaGetLastError()) << endl;

	// Read C from the device
	cudaMemcpy(C, Cd, size, cudaMemcpyDeviceToHost);


	// Free device memory
	cudaFree(Ad);
	cudaFree(Bd);
	cudaFree(Cd);
}

void readFile(){
    int i=0,j=0,tmp=0;
    ifstream f;
    int num;
    bool t = true;
    f.open("1");
    f >> num;
    tmp += 1;
    while(!f.eof())
     {
        if(j == 1600){
            j=0;
            i++;
            //cout << endl;
            //getchar();
        }
        if(i == 1600){
            t = false;
            i = 0;
            j = 0;
        }
        if(t){
            A[i][j] = num;
        }
        else{
            B[i][j] = num;
        }
        f >> num;
        j++;
     }
    f.close();
}

int main(int argc , char* argv[]){
    timespec ts, te;
 
    float *C;
    C = (float*)malloc(sizeof(float) * 1600 * 1600);
	
	readFile();
    clock_gettime(CLOCK_REALTIME, &ts);
    Mul(*A,*B,1600,1600,1600,C);
    clock_gettime(CLOCK_REALTIME, &te);
    cout  << BLOCK_SIZE << " " <<  (te.tv_sec-ts.tv_sec)<<"."<<abs(te.tv_nsec-ts.tv_nsec) << endl;

	free(C);
    return 0;
}

