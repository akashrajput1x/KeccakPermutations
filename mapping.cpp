#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

int mod(int data, int modulus){    return data%modulus;    }

int C(vector<vector<vector<int>>>& state_array, int x, int z){
    int result = state_array[x][0][z];
    for (int i = 1; i < state_array[0].size(); i++){
        result = result ^ state_array[x][i][z];
    }
    return result;
}

int D(vector<vector<vector<int>>>& state_array, int x, int z){
    int a = C(state_array,mod(x-1, 5), z);
    int b = C(state_array, mod(x + 1, 5), mod( z - 1, state_array[0][0].size()));
    return a^b;
}

vector<vector<vector<int>>> theta(vector<vector<vector<int>>>& state_array){

    int x = state_array.size();
    int y = state_array[0].size();
    int z = state_array[0][0].size();

    vector<vector<vector<int>>> new_state(x, vector<vector<int>>(y, vector<int>(z)));

    for (int i = 0; i < x; i++){
        for (int k = 0; k < z; k++){

            int d = D(state_array, i, k);

            for (int j = 0; j < y; j++)
                new_state[i][j][k] = state_array[i][j][k] ^ d;
        }
    }
    return new_state;   
}

vector<vector<vector<int>>> roh(vector<vector<vector<int>>>& state_array){
    
    int x = state_array.size();
    int y = state_array[0].size();
    int z = state_array[0][0].size();

    vector<vector<vector<int>>> new_state(x, vector<vector<int>>(y, vector<int>(z)));

    for(int k=0; k < z; k++)
        new_state[0][0][k] = state_array[0][0][k];

    int i = 1;
    int j = 0;

    for(int t = 0; t < 24 ; t++){
        for(int k = 0; k < z; k++)
            new_state[i][j][k] = state_array[i][j][mod(k - (t+1)*(t+2)/2, z)];

        int m = i;
        i = j;
        j = mod(2*m + 3*j, 5);
    }

    return new_state;
}

vector<vector<vector<int>>> pie(vector<vector<vector<int>>>& state_array){

    int x = state_array.size();
    int y = state_array[0].size();
    int z = state_array[0][0].size();

    vector<vector<vector<int>>> new_state(x, vector<vector<int>>(y, vector<int>(z)));

    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            for (int k = 0; k < z; k++)
                new_state[i][j][k] = state_array[mod(i+3*j, 5)][i][k];
        }
    }
    return new_state;   
}

vector<vector<vector<int>>> chi(vector<vector<vector<int>>>& state_array){

    int x = state_array.size();
    int y = state_array[0].size();
    int z = state_array[0][0].size();

    vector<vector<vector<int>>> new_state(x, vector<vector<int>>(y, vector<int>(z)));

    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            for (int k = 0; k < z; k++)
                new_state[i][j][k] = state_array[i][j][k] ^ ((state_array[mod(i+1, 5)][y][z] ^ 1) && state_array[mod(x+2, 5)][y][z]);
        }
    }
    return new_state;   
}

int rc(int t){
    
    if(t%255 == 0){    return 1;    }

    vector<int> R(8);
    R[0] = 1;

    for (int i = 1; i < 8; i++)
        R[i] = 0;
    
    for(int i = 1;i < (t % 255); i++){
        R.insert(R.begin(),0);
        R[0] = R[0] ^ R[8];
        R[4] = R[4] ^ R[8];
        R[5] = R[5] ^ R[8];
        R[6] = R[6] ^ R[8];
        R.pop_back();
    }
    return R[0];
}

vector<vector<vector<int>>> iota(vector<vector<vector<int>>>& state_array, int ir){

    int x = state_array.size();
    int y = state_array[0].size();
    int z = state_array[0][0].size();

    vector<vector<vector<int>>> new_state(x, vector<vector<int>>(y, vector<int>(z)));

    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            for (int k = 0; k < z; k++)
                new_state[i][j][k] = state_array[i][j][k];
        }
    }

    vector<int> RC(z, 0);
    int l = log2(z);

    for(int i = 0; i < l;i++)
        RC[pow(2,i) - 1] = rc(i + 7*ir);
    
    for(int i = 0; i < z; i++)
        new_state[0][0][i] = new_state[0][0][i] ^ RC[i];

    return new_state;   
}

vector<vector<vector<int>>> Rnd(vector<vector<vector<int>>>& state_array, int ir){

    int x = state_array.size();
    int y = state_array[0].size();
    int z = state_array[0][0].size();

    vector<vector<vector<int>>> new_state(x, vector<vector<int>>(y, vector<int>(z)));

    new_state = theta(state_array);
    new_state = roh(state_array);
    new_state = pie(state_array);
    new_state = chi(state_array);
    new_state = iota(state_array, ir);

    return new_state;
}

