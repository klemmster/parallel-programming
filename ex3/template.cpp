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
    const int LIST_SIZE_NAIVE = 1024;
    int *inputNaive = new int[LIST_SIZE_NAIVE];
    for(int i = 0; i < LIST_SIZE_NAIVE; i++) {
        inputNaive[i] = i;
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
        vector<int> max_Sizes;
        devices[0].getInfo(CL_DEVICE_MAX_WORK_ITEM_SIZES, &max_Sizes);
        for(int i=0; i<max_Sizes.size(); ++i)
            std::cout << "MAX_WORKGROUP_SIZE: " << max_Sizes[i] << "\n";
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

        /*
        // Make kernel
        Kernel naiveKernel(program, "naivParallelscan");

        // Create memory buffers
        Buffer naiveSrcBuffer = Buffer(context, CL_MEM_READ_WRITE, LIST_SIZE_NAIVE * sizeof(int));

        // Copy list inputNaive to the memory buffers
        queue.enqueueWriteBuffer(naiveSrcBuffer, CL_TRUE, 0, LIST_SIZE_NAIVE * sizeof(int), inputNaive);

        // Set arguments to kernel
        naiveKernel.setArg(0, naiveSrcBuffer);
        naiveKernel.setArg(1, LIST_SIZE_NAIVE);

        //Global: Overall Num of Elements
        //Local: Elements per Block
        NDRange global(LIST_SIZE_NAIVE);
        NDRange local(LIST_SIZE_NAIVE);
        queue.enqueueNDRangeKernel(naiveKernel, NullRange, global, local);

        // Read buffer C into a local list
        int *resultNaive = new int[LIST_SIZE_NAIVE];
        queue.enqueueReadBuffer(naiveSrcBuffer, CL_TRUE, 0, LIST_SIZE_NAIVE * sizeof(int), resultNaive);

        std::cout << "Sum Naive Approach: " << resultNaive[LIST_SIZE_NAIVE-1] << std::endl;
        std::cout << "ListSize: " << LIST_SIZE_NAIVE << std::endl;
        std::cout << "Difference last two elements: " <<
                resultNaive[LIST_SIZE_NAIVE-1]-resultNaive[LIST_SIZE_NAIVE-2] << "\n";


        */
        const int LIST_SIZE_REDUCE = 4096;
        int *inputReduce = new int[LIST_SIZE_REDUCE];
        for(int i = 0; i < LIST_SIZE_REDUCE; i++) {
            inputReduce[i] = i;
        }

        Kernel reduceSweepKernel(program, "reduce");
        Buffer reduceSrcBuffer = Buffer(context, CL_MEM_READ_WRITE, LIST_SIZE_REDUCE * sizeof(int));
        queue.enqueueWriteBuffer(reduceSrcBuffer, CL_TRUE, 0, LIST_SIZE_REDUCE * sizeof(int), inputReduce);
        reduceSweepKernel.setArg(0, reduceSrcBuffer);
        //reduceSweepKernel.setArg(1, LIST_SIZE_REDUCE);
        NDRange global(LIST_SIZE_REDUCE);
        NDRange local(1024);
        queue.enqueueNDRangeKernel(reduceSweepKernel, NullRange, global, local);
        int *resultReduce = new int[LIST_SIZE_REDUCE];
        queue.enqueueReadBuffer(reduceSrcBuffer, CL_TRUE, 0, LIST_SIZE_REDUCE * sizeof(int), resultReduce);

        for(int i=0; i < LIST_SIZE_REDUCE; ++i){
            std::cout << resultReduce[i] << "\n";
        }
        std::cout << "Sum Reduce Approach: " << resultReduce[LIST_SIZE_REDUCE-1] << std::endl;
        std::cout << "ListSize: " << LIST_SIZE_REDUCE << std::endl;
        std::cout << "Difference last two elements: " <<
                resultReduce[LIST_SIZE_REDUCE-1]-resultReduce[LIST_SIZE_REDUCE-2] << "\n";


    } catch(Error error) {
       std::cout << error.what() << "(" << error.err() << ")" << std::endl;
    }

    return 0;
}
