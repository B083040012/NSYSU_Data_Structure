// Author:陳柏翰
// Date:Nov 5,2020
// Purpose:進行Binary Tree排序

#include<iostream>
#include"Binary_Search_Tree.cpp"
using namespace std;

int main(){
    int input;
    while(cin >> input){                    // input number
        Binary_Search_Tree BST1;
        while(input!=-1){
            if(input==-1) break;            // if input -1 ,end the BST process
            BST1.Process(input);
            cin >> input;
        }
        BST1.Print();                       // print the info of node on BST inorder
        if(cin.peek()!=EOF) cout << "\n\n"; // if having next input,print newline
    }
}