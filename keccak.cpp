#include<iostream>
#include<vector>
#include<string>
#include<math.h>
#include"bitString.cpp"
#include"stateArray.cpp"
#include"mapping.cpp"

using namespace std;

vector<int> keccak_p(vector<int> vec, int n, int block_size){
    vector<vector<vector<int>>> state_array = stateArray(vec,block_size);
    int a = log2(state_array[0][0].size());

    for (int i = 12 + 12*a - n; i < 12 + 12*a - 1; i++)
        state_array = Rnd(state_array, i);
    
    return bitString(state_array);
}

vector<int> keccak(string& str, int d = 512){
    vector<int> N = bitString(str);
    N.push_back(0);
    N.push_back(1);

    sponge(keccak_p(N,24,1600),1600 - d*2);
}