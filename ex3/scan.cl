__kernel void seqscan(__global int *buffer, const int size) {

    // Get the index of the current element to be processed
    const int i = get_global_id(0);

    if( i == 0){
        // Do the operation
        for(unsigned int i=1; i<size; ++i){
            buffer[i] = buffer[i-1] + buffer[i];
        }
    }
}

__kernel void naivParallelscan(__global int *source, const int size) {

    // Get the index of the current element to be processed
    const int i = get_global_id(0);

    for(unsigned int offset=1; offset<size; offset *=2)
    {
        int threadLocalVal;
        if(i>=offset){
            threadLocalVal = source[i-offset];
        }
        barrier(CLK_LOCAL_MEM_FENCE);
        if(i>=offset){
            source[i] = threadLocalVal + source[i];
            //buffer[i] = threadLocalVal;// + buffer[i];
        }
        barrier(CLK_GLOBAL_MEM_FENCE);
    }
}


//Reduce -- DownSweep Version http://http.developer.nvidia.com/GPUGems3/gpugems3_ch39.html
__kernel void reduce(__global int *buffer) {

    const int globalIndex = get_global_id(0);
    if(globalIndex < get_global_size(0)){
    const int i = get_local_id(0);
    int size = get_local_size(0);
    __local int tmp[1024];
    int offset = 1;

    tmp[2*i] = buffer[2*globalIndex];
    tmp[2*i+1] = buffer[2*globalIndex+1];

    for(int d=size>>1; d>0; d >>=1)
    {
        barrier(CLK_LOCAL_MEM_FENCE);
        if( i < d){
            int ai = offset*(2*i+1)-1;
            int bi = offset*(2*i+2)-1;

            tmp[bi] += tmp[ai];
        }
        barrier(CLK_LOCAL_MEM_FENCE);
        offset *= 2;
    }

    barrier(CLK_LOCAL_MEM_FENCE);
    if( i == 0) {
        tmp[size-1] = 0;
    }

    for(int d = 1; d < size; d *= 2){
        offset >>= 1;
        barrier(CLK_LOCAL_MEM_FENCE);

        if (i < d)
        {
            int ai = offset*(2*i+1)-1;
            int bi = offset*(2*i+2)-1;

            __local int t = tmp[ai];
            tmp[ai] = tmp[bi];
            tmp[bi] += t;
        }
    }
    barrier(CLK_LOCAL_MEM_FENCE);
    buffer[2*globalIndex] = tmp[2*i];
    buffer[2*globalIndex+1] = tmp[2*i+1];
    }
}
