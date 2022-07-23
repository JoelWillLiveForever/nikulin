#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CL_TARGET_OPENCL_VERSION 120

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
 
#define MAX_SOURCE_SIZE (0x100000)

#define POINTS_SIZE 10000000UL // размер массива для вычислений
#define POINTS_VALUE 10000UL // количество точек, которое будет обсчитывать каждое kernel

int main()
{   
    srand((unsigned int) time(NULL));

    uint i, *points, *randoms, *good_points;
    ulong global_counter = 0;

    points = (uint*) malloc(sizeof(uint) * POINTS_SIZE);
    randoms = (uint*) malloc(sizeof(uint) * POINTS_SIZE);

    good_points = (uint*) malloc(sizeof(uint) * POINTS_SIZE);
 
    for (i = 0; i < POINTS_SIZE; i++)
    {
        points[i] = POINTS_VALUE;
        randoms[i] = rand();

        //printf("points[%d] = %d;\ngood_points[%d] = %f;\n\n", i, points[i], i, good_points[i]);
    }

    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;
 
    fp = fopen("kernel_boost.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }

    source_str = (char*) malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
   
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory buffers on the device for each vector 
    cl_mem points_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            POINTS_SIZE * sizeof(uint), NULL, &ret);

    cl_mem randoms_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            POINTS_SIZE * sizeof(uint), NULL, &ret);

    cl_mem good_points_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            POINTS_SIZE * sizeof(uint), NULL, &ret);

    // Copy the lists @points and @randoms to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, points_mem_obj, CL_TRUE, 0,
            POINTS_SIZE * sizeof(uint), points, 0, NULL, NULL);
 
    ret = clEnqueueWriteBuffer(command_queue, randoms_mem_obj, CL_TRUE, 0,
            POINTS_SIZE * sizeof(uint), randoms, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);
 
    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "compute", &ret);
 
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&points_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&randoms_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&good_points_mem_obj);
 
    // Execute the OpenCL kernel on the list
    size_t global_item_size = POINTS_SIZE; // Process the entire lists
    size_t local_item_size = 64; // Divide work items into groups of 64
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);
 
    // Read the memory buffer @good_points on the device to the local variable @good_points
    ret = clEnqueueReadBuffer(command_queue, good_points_mem_obj, CL_TRUE, 0, 
            POINTS_SIZE * sizeof(uint), good_points, 0, NULL, NULL);
    
    for (i = 0; i < POINTS_SIZE; i++)
    {
        //printf("good_points[%d] = %u;\n", i, good_points[i]);
        global_counter += good_points[i];
    }
    
    printf("POINTS_SIZE = %lu; POINTS_VALUE = %lu;\n", POINTS_SIZE, POINTS_VALUE);

    ulong all_points = POINTS_SIZE * POINTS_VALUE;
    printf("good_points = %lu; all_points = %lu;\n", global_counter, all_points);

    long double pi = (((long double) 4.0) * ((long double) global_counter)) / ((long double) all_points);
    printf("PI = %Lf\n", pi);
    
    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);

    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);

    ret = clReleaseMemObject(points_mem_obj);
    ret = clReleaseMemObject(good_points_mem_obj);

    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    free(points);
    free(good_points);

    return 0;
}
