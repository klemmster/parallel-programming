
__kernel void scan(__global int *buffer, const int size) {

    // Get the index of the current element to be processed
    const int i = get_global_id(0);
    const int n = get_global_size(0);

    for(unsigned offset=1; offset<n; offset *=2){
        int threadLocalVal;
        if(i>=offset){
            threadLocalVal = buffer[i-offset];
        }
        barrier(CLK_LOCAL_MEM_FENCE);
        if(i>=offset){
            buffer[i] = threadLocalVal + buffer[i];
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }
}

