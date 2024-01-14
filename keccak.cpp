#include<iostream>
#include<vector>
#include<string>
#include<math.h>
#include"stateArray.cpp"
#include"mapping.cpp"

using namespace std;

vector<int> keccak_p(string str, int n, int block_size = 1600){
    vector<vector<vector<int>>> state_array = stateArray(str,block_size);
    int a = log2(state_array[0][0].size());

    for (int i = 12 + 12*a - n; i < 12 + 12*a - 1; i++)
        state_array = Rnd(state_array, i);
    
    return bitString(state_array);
}