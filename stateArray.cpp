#include<iostream>
#include<vector>
#include<string>

using namespace std;

int padLength(vector<int> vec, int block_size){

    return(    vec.size()/block_size + 1   )* block_size - vec.size();
}

int removalLength(vector<int> vec){
    int count = 0;
    int i = vec.size() - 1;
    
    while (vec[i--] == 0)
        count++;

    count++;

    return count;
}

//binary representation of state array
vector<int> bitString(vector<vector<vector<int>>>& state_array){       

    int x = state_array.size();
    int y = state_array[0].size();
    int z = state_array[0][0].size();
    vector<int> bits_vector(x*y*z);
    
    for (int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            for(int k = 0; k < z; k++)
                bits_vector[ z * (y * j + i) + k ]  = state_array[i][j][k];
        }
    }

    return bits_vector;
}

//bit string to state array
vector<vector<vector<int>>> stateArray(vector<int> bits_vector,int block_size){

    int plen = padLength(bits_vector, block_size);
    
    bits_vector.push_back(1);
    for (int i = 1; i < plen; i++)
        bits_vector.push_back(0);
    

    int x = 5;
    int y = 5;
    int z = block_size/(x*y);
    vector<vector<vector<int>>> state_array(x,vector<vector<int>>(y,vector<int>(z)));
    
    for (int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            for(int k = 0; k < z; k++)
                state_array[i][j][k] = bits_vector[ z * (y * j + i) + k ];
        }
    }
    return state_array;
}