#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;
int main(int argc, char const *argv[])
{
    /* code */
    if(argc < 4){
        printf("Not enough arguments\n");
        return 0;
    }
    string a(argv[1]);
    string b(argv[2]);
    size_t K = atoi(argv[3]);
    size_t N = a.size();
    size_t M = b.size();

    vector< unsigned int > L(a.size()*b.size());
    L.reserve(a.size()*b.size());

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            size_t index = i*M + j;
            if (a[i] == b[j]) {
                if (i == 0 || j == 0){
                    L.at(index) = 1;
                }else{
                    size_t lowerIndex = (i-1)*M + j-1;
                    L.at(index) = L.at(lowerIndex)+1;
                }
            } else {
                L.at(index) = 0;
            }
        }
    }

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j){
            size_t index = i*M + j;
            if (L.at(index) >= K) {
                size_t upperIndex = (i+1)*M + j+1;
                if (i+1<N && j+1<M && L.at(upperIndex) > L.at(index))
                    continue;
                printf("%d %d %d\n", i, j, L.at(index));
            }
        }
    cout << "######################################################" << "\n";
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < M; ++j){
            size_t index = i*M + j;
            cout << " " << L.at(index);
        }
        cout << "\n";
    }

    return 0;
}
