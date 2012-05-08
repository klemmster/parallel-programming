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

    vector<vector< unsigned int >> L;
    L.assign(N, vector< unsigned int > (M));

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (a[i] == b[j]) {
                if (i == 0 || j == 0){
                    L[i][j] = 1;
                }else{
                    L[i][j] = L[i-1][j-1] + 1;
                }
            } else {
                L[i][j] = 0;
            }
        }
    }

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j){
            if (L[i][j] >= K) {
                if (i+1<N && j+1<M && L[i+1][j+1] > L[i][j])
                    continue;
                printf("%d %d %d\n", i, j, L[i][j]);
            }
        }
    cout << "######################################################" << "\n";
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < M; ++j){
            cout << " " << L[i][j];
        }
        cout << "\n";
    }

    return 0;
}
