#include<iostream>
#include<vector>
#include<string>
#include"keccak.cpp"

using namespace std;

vector<int> pad(int x, int m){
    int j = mod((-1*m) - 2,x);
    vector<int> str(j,0);
    str.insert(str.begin(), 1);
    str.insert(str.end(), 1);
    return str;
}

vector<int> sponge(vector<int> N, int r){
    
    vector<int> k = pad(r,N.size());
    vector<int> P;

    for (int i = 0; i < N.size(); i++)
        P.push_back(N[i]);
    
    for (int i = 0; i < k.size(); i++)
        P.push_back(k[i]);

    
    int n = P.size()/r;
    int c = N.size() - r;

    
}