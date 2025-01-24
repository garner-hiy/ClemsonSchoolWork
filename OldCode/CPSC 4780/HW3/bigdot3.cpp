#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.hpp>
#include <iostream>
#include <vector>
#include <fstream>

#define N 40 // Matrix size

int main() {
    // Initialize matrices
    std::vector<float> inputMatrix1(N * N, 1.0f);
    std::vector<float> inputMatrix2(N * N, 1.0f);
    std::vector<float> results(N * N, 0.0f);

    try {
        // OpenCL setup
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        if (platforms.empty()) {
            std::cerr << "No OpenCL platforms found!" << std::endl;
            return 1;
        }

        cl::Platform platform = platforms[0];
        cl::Context context(CL_DEVICE_TYPE_GPU);
        std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
        if (devices.empty()) {
            std::cerr << "No OpenCL devices found!" << std::endl;
            return 1;
        }

        cl::Device device = devices[0];

        // Load kernel source
        std::ifstream file("matrix_mult.cl");
        if (!file) {
            std::cerr << "Kernel file not found!" << std::endl;
            return 1;
        }
        std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        cl::Program::Sources sources(1, std::make_pair(source.c_str(), source.length()));
        cl::Program program(context, sources);

        // Build the program
        try {
            program.build(devices);
        } catch (...) {
            std::cerr << "Build log:\n"
                      << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
            throw;
        }

        // Create command queue
        cl::CommandQueue queue(context, device, CL_QUEUE_PROFILING_ENABLE);

        // Buffers
        cl::Buffer bufferA(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * N * N, inputMatrix1.data());
        cl::Buffer bufferB(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * N * N, inputMatrix2.data());
        cl::Buffer bufferC(context, CL_MEM_WRITE_ONLY, sizeof(float) * N * N);

        // Kernel
        cl::Kernel kernel(program, "matrixMultiply");
        kernel.setArg(0, bufferA);
        kernel.setArg(1, bufferB);
        kernel.setArg(2, bufferC);
        kernel.setArg(3, N);

        // Execute kernel for BLOCK_SIZE = 20
        int BLOCK_SIZE = 20;
        cl::NDRange global(N, N);
        cl::NDRange local(BLOCK_SIZE, BLOCK_SIZE);

        cl::Event event;
        queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local, nullptr, &event);
        queue.finish();

        // Profiling information
        cl_ulong start = event.getProfilingInfo<CL_PROFILING_COMMAND_START>();
        cl_ulong end = event.getProfilingInfo<CL_PROFILING_COMMAND_END>();
        double executionTime = (end - start) / 1e6; // Convert nanoseconds to milliseconds

        // Output execution time
        std::cout << "BLOCK_SIZE = " << BLOCK_SIZE << ", Execution Time: " << executionTime << " ms" << std::endl;

        // Retrieve results
        queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, sizeof(float) * N * N, results.data());

        // Output part of the result matrix for verification
        std::cout << "Top-left 5x5 submatrix of the result:" << std::endl;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                std::cout << results[i * N + j] << " ";
            }
            std::cout << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}