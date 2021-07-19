#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int main(){
    ifstream test;
    ofstream test_out;
    test.open("Cover.jpg",ios::binary);
    test_out.open("out.jpg",ios::binary);
    while(!test.eof()){
        char temp;
        test >> noskipws >> temp;
        test_out << temp;
    }    
    test.close();
    test_out.close();
}