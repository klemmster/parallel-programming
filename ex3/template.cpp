#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
using namespace cl;

int main() {
    // Create the two input vectors
    const int LIST_SIZE = 17;
    int *A = new int[LIST_SIZE];
    for(int i = 0; i < LIST_SIZE; i++) {
        A[i] = i;
    }

   try {
        // Get available platforms
        vector<Platform> platforms;
        Platform::get(&platforms);

        // Select the default platform and create a context using this platform and the GPU
        cl_context_properties cps[3] = {
            CL_CONTEXT_PLATFORM,
            (cl_context_properties)(platforms[0])(),
            0
        };
        Context context( CL_DEVICE_TYPE_CPU, cps);

        // Get a list of devices on this platform
        vector<Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

        // Create a command queue and use the first device
        CommandQueue queue = CommandQueue(context, devices[0]);

        // Read source file
        std::ifstream sourceFile("scan.cl");
        std::string sourceCode(
            std::istreambuf_iterator<char>(sourceFile),
            (std::istreambuf_iterator<char>()));
        Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length()+1));

        // Make program of the source code in the context
        Program program = Program(context, source);

        // Build program for these specific devices
        program.build(devices);

        // Make kernel
        Kernel reduceKernel(program, "naivParallelscan");

        // Create memory buffers
        Buffer buffer = Buffer(context, CL_MEM_READ_WRITE, LIST_SIZE * sizeof(int));
        Buffer outputBuffer = Buffer(context, CL_MEM_WRITE_ONLY, LIST_SIZE * sizeof(int));
        //Buffer localBuffer = Buffer(context, CL_MEM_READ_WRITE, LIST_SIZE * sizeof(int));

        // Copy lists A and B to the memory buffers
        queue.enqueueWriteBuffer(buffer, CL_TRUE, 0, LIST_SIZE * sizeof(int), A);
        //queue.enqueueWriteBuffer(localBuffer, CL_TRUE, 0, LIST_SIZE * sizeof(int), A);

        // Set arguments to kernel
        reduceKernel.setArg(0, buffer);
        //reduceKernel.setArg(1, outputBuffer);
        //reduceKernel.setArg(2,  sizeof(int)*LIST_SIZE, NULL);
        reduceKernel.setArg(1, LIST_SIZE);

        // Run the kernel on specific ND range
        NDRange global(LIST_SIZE);
        NDRange local(LIST_SIZE);
        queue.enqueueNDRangeKernel(reduceKernel, NullRange, global, local);

        // Read buffer C into a local list
        int *C = new int[LIST_SIZE];
        queue.enqueueReadBuffer(buffer, CL_TRUE, 0, LIST_SIZE * sizeof(int), C);

        for(int i = 0; i < LIST_SIZE; i ++)
             std::cout << C[i] << std::endl;
    } catch(Error error) {
       std::cout << error.what() << "(" << error.err() << ")" << std::endl;
    }

    return 0;
}
