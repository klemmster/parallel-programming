
__kernel void scan(__global int *buffer, const int size) {

    // Get the index of the current element to be processed
    const int i = get_global_id(0);

    if( i == 0){
        // Do the operation
        for(unsigned int i=1; i<size; ++i){
            buffer[i] = buffer[i-1] + buffer[i];
        }
    }
}

