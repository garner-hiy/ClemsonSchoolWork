/*
 * Author: AJ Garner
 * Class: CPSC 4780
 * Date: 09/15/2024
 *
 * Description:
 * This program computes the dot product of two large vectors both on the CPU and GPU. It compares the performance
 * of CPU and GPU implementations, including memory allocation, data transfer, and kernel execution on the GPU.
 * The results are printed along with the time taken for each step to analyze the speedup achieved using GPU parallel processing.
 *
 * Compilation Instructions:
 * First Make sure to run the module:
 *   module load cuda gcc
 *
 * To compile this program, use the NVIDIA CUDA compiler (nvcc):
 *   nvcc dotProduct.cu -o dotProduct
 *
 * Run the program:
 * After compiling, you can run the program using:
 *   ./dotProduct
 *
 * Note: If there is an error when trying to compile, such as the compiler may be unsupported, please compile using
 * this command instead: nvcc -allow-unsupported-compiler dotProduct.cu -o dotProduct
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <cuda.h>

// Timer functions to measure different sections of the code
long long start_timer() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return current_time.tv_sec * 1000000 + current_time.tv_usec;
}

// Stops the timer and prints the elapsed time for a specific label
long long stop_timer(long long start_time, char *label) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long long end_time = current_time.tv_sec * 1000000 + current_time.tv_usec;
    printf("%s: %.5f sec\n", label, ((float)(end_time - start_time)) / (1000 * 1000));
    return end_time - start_time;
}

// Computes the dot product on the CPU
float CPU_big_dot(float *vec_A, float *vec_B, int vector_size) {
    float dot_product_result = 0.0;
    for (int i = 0; i < vector_size; i++) {
        // Simple element-wise multiplication and accumulation
        dot_product_result += vec_A[i] * vec_B[i];
    }
    return dot_product_result;
}

// GPU kernel to compute dot product in parallel
__global__ void GPU_dot_product_kernel(float *vec_A, float *vec_B, float *partial_result, int vector_size) {
    __shared__ float shared_memory[512];  // Using shared memory to speed up reduction
    int thread_id = threadIdx.x + blockIdx.x * blockDim.x;
    int cache_index = threadIdx.x;
    float temp_sum = 0.0;

    // Each thread computes part of the dot product
    while (thread_id < vector_size) {
        temp_sum += vec_A[thread_id] * vec_B[thread_id];
        thread_id += blockDim.x * gridDim.x;
    }

    shared_memory[cache_index] = temp_sum;
    __syncthreads();

    // Perform reduction within the block
    int offset = blockDim.x / 2;
    while (offset != 0) {
        if (cache_index < offset) {
            shared_memory[cache_index] += shared_memory[cache_index + offset];
        }
        __syncthreads();
        offset /= 2;
    }

    // Use atomicAdd to accumulate the results across all blocks
    if (cache_index == 0) {
        atomicAdd(partial_result, shared_memory[0]);
    }
}

// Function to handle the GPU computation, including memory allocation and transfers
float GPU_big_dot(float *vec_A, float *vec_B, int vector_size) {
    float *device_vec_A, *device_vec_B, *device_partial_result;
    float host_result = 0.0;
    cudaError_t cuda_status;

    // Allocate memory on the GPU
    long long timer_start = start_timer();
    cuda_status = cudaMalloc((void **)&device_vec_A, vector_size * sizeof(float));
    if (cuda_status != cudaSuccess) {
        printf("CUDA error in cudaMalloc (device_vec_A): %s\n", cudaGetErrorString(cuda_status));
        return -1;
    }
    cuda_status = cudaMalloc((void **)&device_vec_B, vector_size * sizeof(float));
    if (cuda_status != cudaSuccess) {
        printf("CUDA error in cudaMalloc (device_vec_B): %s\n", cudaGetErrorString(cuda_status));
        return -1;
    }
    cuda_status = cudaMalloc((void **)&device_partial_result, sizeof(float));
    if (cuda_status != cudaSuccess) {
        printf("CUDA error in cudaMalloc (device_partial_result): %s\n", cudaGetErrorString(cuda_status));
        return -1;
    }
    stop_timer(timer_start, "Memory allocation on GPU");

    // Transfer data from host to device (CPU to GPU)
    timer_start = start_timer();
    cudaMemcpy(device_vec_A, vec_A, vector_size * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(device_vec_B, vec_B, vector_size * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(device_partial_result, &host_result, sizeof(float), cudaMemcpyHostToDevice);
    stop_timer(timer_start, "Memory transfer to GPU");

    // Launch the kernel with an appropriate number of blocks and threads
    int threads_per_block = 512;
    int num_blocks = (vector_size + threads_per_block - 1) / threads_per_block;
    timer_start = start_timer();
    GPU_dot_product_kernel<<<num_blocks, threads_per_block>>>(device_vec_A, device_vec_B, device_partial_result, vector_size);
    
    // Ensure the kernel has completed
    cuda_status = cudaDeviceSynchronize();
    if (cuda_status != cudaSuccess) {
        printf("CUDA error in kernel execution: %s\n", cudaGetErrorString(cuda_status));
        return -1;
    }
    stop_timer(timer_start, "Kernel execution");

    // Copy the result from device to host (GPU to CPU)
    timer_start = start_timer();
    cudaMemcpy(&host_result, device_partial_result, sizeof(float), cudaMemcpyDeviceToHost);
    stop_timer(timer_start, "Memory transfer to CPU");

    // Free up GPU memory
    cudaFree(device_vec_A);
    cudaFree(device_vec_B);
    cudaFree(device_partial_result);

    return host_result;
}

int main() {
    int vector_size = 1024 * 1024;
    float *host_vec_A = (float *)malloc(vector_size * sizeof(float));
    float *host_vec_B = (float *)malloc(vector_size * sizeof(float));

    // Initialize vectors with random values
    for (int i = 0; i < vector_size; i++) {
        host_vec_A[i] = (float)rand() / RAND_MAX;
        host_vec_B[i] = (float)rand() / RAND_MAX;
    }

    // Perform dot product on the CPU
    long long timer_start = start_timer();
    float cpu_result = CPU_big_dot(host_vec_A, host_vec_B, vector_size);
    long long cpu_time = stop_timer(timer_start, "CPU computation");

    // Perform dot product on the GPU
    timer_start = start_timer();
    float gpu_result = GPU_big_dot(host_vec_A, host_vec_B, vector_size);
    long long gpu_time = stop_timer(timer_start, "Total GPU computation");

    // Output results and speedup
    printf("CPU result: %f\n", cpu_result);
    printf("GPU result: %f\n", gpu_result);
    printf("Difference: %f\n", abs(cpu_result - gpu_result));
    printf("Speedup (CPU time / GPU time): %.5f\n", (float)cpu_time / gpu_time);

    // Clean up memory
    free(host_vec_A);
    free(host_vec_B);

    return 0;
}