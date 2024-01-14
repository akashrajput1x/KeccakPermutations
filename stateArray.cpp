#include<iostream>
#include<vector>
#include<string>

using namespace std;

//length of binary message rounded off to blocksize
int lenInBlockSize(string& str, int block_size){
    
    int len = str.length();
    
    return (( len * 8) /block_size + 1) * block_size;
}

//binary representation of message
vector<int> bitString(string& str,int block_size){

    vector<int> bits_vector(lenInBlockSize(str, block_size));
    int a = 0;

    for(char c: str){                                   //character iteration

        for(int i = 0; i<8; i++){                       //character to binary
        
            bits_vector[a + 7 - i] = c%2;
            c /= 2;
        }

        a+=8;
    }
    
    bits_vector[a++] = 1;                               //ending vector with 1
    
    while(a < bits_vector.size())                       //filling of left out vector with zeros
        bits_vector[a++] = 0;

    return bits_vector;
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

//message representation of binary 
string message(vector<int>& bits_vector){
    
    int len = bits_vector.size()/8;
    string str;
    
    for (int i = 0; i < len; i++){
    
        int result = 0;
        
        for (int j = 0; j < 8; j++)
            result = result*2 +  bits_vector[i*8 + j];
        
        str += result;
    }
    
    return str;
}
//state array to message
string message(vector<vector<vector<int>>>& state_array){
    vector<int>bit_string  = bitString(state_array);
    return message(bit_string);
}

//bit string to state array
vector<vector<vector<int>>> stateArray(vector<int> bits_vector,int block_size){

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

//message to state array
vector<vector<vector<int>>> stateArray(string str,int block_size){

    int x = 5;
    int y = 5;
    int z = block_size/(x*y);
    vector<int> bits_vector = bitString(str, block_size);
    return stateArray(bits_vector, block_size);
}