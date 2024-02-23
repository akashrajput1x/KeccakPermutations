#include<iostream>
#include<string>
#include<vector>
using namespace std;


//binary representation of message
vector<int> bitString(string& str){

    vector<int> bits_vector(str.length()*8);
    int a = 0;
    for(char c: str){                                   //character iteration

        for(int i = 0; i<8; i++){                       //character to binary
        
            bits_vector[a + 7 - i] = c%2;
            c /= 2;
        }

        a+=8;
    }

    return bits_vector;
}

//message representation of binary 
string charString(vector<int>& bits_vector){
    
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