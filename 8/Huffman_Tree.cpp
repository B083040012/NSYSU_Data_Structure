#include<bits/stdc++.h>
#include<iostream>
using namespace std;

class Node{
    public:
        unsigned char data;
        int freq;
        Node *lchild,*rchild;
        Node(unsigned char _data,int _freq,Node *_lchild,Node *_rchild):data(_data),freq(_freq),lchild(_lchild),rchild(_rchild){};
};

bool compare(Node *a,Node *b){
    if(a->freq==b->freq) return a->data<b->data;
    else return a->freq<b->freq;
}

class Huffman_Tree{
    private:
        unordered_map<unsigned char,int> count_fre;
        deque<Node*> tree;
    public:
        Huffman_Tree(vector<unsigned char>);
        deque<Node *> build_tree();

};

Huffman_Tree::Huffman_Tree(vector<unsigned char> data){
    for(int i=0;i<data.size();i++){
        if(count_fre.count(data[i])) count_fre[data[i]]++;
        else count_fre[data[i]]=1;
    }
    // cout << "In Huffman_tree:\n";
    // for(auto &ptr_c:count_fre) cout << ptr_c.first << " " << ptr_c.second << endl;
    for(auto ptr=count_fre.begin();ptr!=count_fre.end();ptr++){
        tree.push_back(new Node((*ptr).first,(*ptr).second,nullptr,nullptr));
    }

}

deque<Node *> Huffman_Tree::build_tree(){
    // cout << "In build_tree:\n";
    // sort(tree.begin(),tree.end(),compare);
    // for(auto ptr_t=tree.begin();ptr_t!=tree.end();ptr_t++){
    //     cout << (int)((*ptr_t)->data) << " " << (*ptr_t)->freq << endl;
    // }
    // cout << "out_tree\n";
    for(int i=0;i<count_fre.size()-1;i++){
        sort(tree.begin(),tree.end(),compare);
        unsigned char min_char;
        Node *n1=tree.front();
        tree.pop_front();
        Node *n2=tree.front();
        tree.pop_front();
        if(n1->data<n2->data) tree.push_back(new Node(n1->data,n1->freq+n2->freq,n1,n2));
        else tree.push_back(new Node(n2->data,n1->freq+n2->freq,n2,n1));
    }
    return tree;
}