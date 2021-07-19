#include<bits/stdc++.h>
#include<iostream>
using namespace std;
#include"Compress_function.cpp"
#include"Uncompress_function.cpp"

int main(int argc,char *argv[]){
    string func1;
    func1.assign(argv[1],2);
    if(func1=="-c"){
        Compress C1(argv[3],argv[5]);
        C1.Process();
    }
    else if(func1=="-u"){
        Uncompress U1(argv[3],argv[5]);
        U1.Process();
    }
}