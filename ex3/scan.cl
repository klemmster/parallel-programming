
__kernel void scan(__global int *buffer, const int size) {

    // Get the index of the current element to be processed
    const int i = get_global_id(0);

    for(unsigned offset=1; offset<size; offset *=2){
        int threadLocalVal;
        if(i>=offset){
            threadLocalVal = buffer[i-offset];
        }
        barrier(CLK_GLOBAL_MEM_FENCE);
        if(i>=offset){
            buffer[i] = threadLocalVal + buffer[i];
        }
        barrier(CLK_GLOBAL_MEM_FENCE);
    }
}


//Reduce -- DownSweep Version http://http.developer.nvidia.com/GPUGems3/gpugems3_ch39.html
__kernel void reduce(__global int *buffer, const int size) {

    const int i = get_global_id(0);

    for(unsigned d=1; d<size-1; d*=2){
        if(((i+1) % (2*d)) == 0){
        buffer[i] = buffer[i] + buffer[i-d];
        }
        barrier(CLK_GLOBAL_MEM_FENCE);
    }

    barrier(CLK_GLOBAL_MEM_FENCE);

    buffer[size-1] = 0;
    for(unsigned d=size>>1; d>0; d>>=1){
        int threadLocalVal;
        if((i+1) % (d) == 0){
            threadLocalVal = buffer[i];
        }
        barrier(CLK_LOCAL_MEM_FENCE);
        if((i+1) % (2*d) == 0){
            buffer[i] = threadLocalVal;
            int index = i-1;
            if(index >= 0){
                buffer[index] = d;
            }else{
                buffer[index] = 255;
            }
            //buffer[i-d] = threadLocalVal;
        }
        /*
        else if((i+1) % (d) == 0){
            buffer[i+d] += threadLocalVal;
        }
        */
        barrier(CLK_GLOBAL_MEM_FENCE);
    }

    buffer[i] = i;
}

__kernel void sweepdown(__global int *buffer, const int size){
    int last = buffer[size-1];
    const int i = get_global_id(0);

    for(unsigned d=size>>1; d>0; d>>=1){
        int threadLocalVal;
        if((i+1) % (d) == 0){
            threadLocalVal = buffer[i];
        }
        barrier(CLK_GLOBAL_MEM_FENCE);
        if((i+1) % (2*d) == 0){
            buffer[i-d] = threadLocalVal;
        }else if((i+1) % (d) == 0){
            buffer[i+d] += threadLocalVal;
        }
        barrier(CLK_GLOBAL_MEM_FENCE);
    }
    buffer[i] = i;
}
