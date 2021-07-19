// Author:陳柏翰
// Date:Nov 5,2020
// Purpose:進行Binary Tree排序

#ifndef BST_CPP
#define BST_CPP
#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

class Tree_Node{
    friend class Binary_Search_Tree;
    private:
        int data;                   // int in Tree_Node
        Tree_Node *left;            // pointer to left(smaller)
        Tree_Node *right;           // pointer to right(larger)
    public:
        Tree_Node(int);
};

Tree_Node::Tree_Node(int num){      // constructor of Tree_Node
    data=num;
    left=right=NULL;
}

class Binary_Search_Tree{
    private:
        Tree_Node *root;            // root of BST
        vector<int> d,r,l;          // vector of Nodes' info
        vector<Tree_Node *> del_tree;   // vector of every Nodes' address
    public:
        Binary_Search_Tree();
        Tree_Node *Search(int);
        Tree_Node *Search(int,Tree_Node *);
        void Add_Node(Tree_Node *,int);
        void Delete_Node(Tree_Node *);
        void Process(int);
        void Preprint(Tree_Node *);
        void Print();
        void Delete_tree();
};

Binary_Search_Tree::Binary_Search_Tree(){       // constructor of BST
    root=NULL;
};

Tree_Node* Binary_Search_Tree::Search(int num){ // search node of num
    return Search(num,root);
}

Tree_Node * Binary_Search_Tree::Search(int num,Tree_Node *current){             // search recursively
    if(!current) return NULL;                                                   // if BST if NULL,return NULL
    if(current->data>num && current->left) return Search(num,current->left);    // if left has node and num is smaller,Search left
    else if (current->data<num && current->right) return Search(num,current->right);    // if right has node and num is larger,Search right
    else return current;                                                                // return 1.exactly the node of num,2.the previous node of num
}

void Binary_Search_Tree::Add_Node(Tree_Node *up,int num){           // add new node to BST
    if(up->data>num) up->left=new Tree_Node(num);
    else if(up->data<num) up->right=new Tree_Node(num);
}

void Binary_Search_Tree::Delete_Node(Tree_Node *del){
    Tree_Node *del_up=root;
    while(del_up){                                                  // find the previous node of num(del_up)
        if(del==root) break;
        else if(del_up->left==del || del_up->right==del) break;
        else if(del_up->data < del->data) del_up=del_up->right;
        else if(del_up->data > del->data) del_up=del_up->left;
    } 
    if(!(del->left) && !(del->right)){                              // if del is leaf node,delete it
        if(del_up->right==del) del_up->right=NULL;
        else del_up->left=NULL;
        if(del==root) root=NULL;
    }
    else if((del->left) && (del->right)){                           // if del is nonleaf node with two son
        Tree_Node *q=del->right;                                    // q is the root of right tree of del
        while(q->left){
            //q_up=q;
            q=q->left;                                              // find the most left node in tree of root q
        }
        int temp=q->data;                                           // give its data to del and delete it
        Delete_Node(q);
        del->data=temp;
    }
    else if(del->left){                                             // delete del with one son on left
        if(del_up->left==del) del_up->left=del->left;
        else if(del_up->right==del) del_up->right=del->left;
        if(del==root) root=del->left;
    }
    else if(del->right){                                            // delete del with one son on right
        if(del_up->left==del) del_up->left=del->right;
        else if(del_up->right==del) del_up->right=del->right;
        if(del==root) root=del->right;
    }
}

void Binary_Search_Tree::Process(int num){                          // read the number user input and process
    Tree_Node* current=Search(num);                                 // get the node we need(node of num,pre node of num,NULL)
    if(!current) root=new Tree_Node(num);
    else{
        if(current->data==num){
            Delete_Node(current);                                   // if BST has node of num,delete it
        }
        else{
            Add_Node(current,num);                                  // add it otherwise
        }
    }
}

void Binary_Search_Tree::Preprint(Tree_Node *p){                    // put info of node into vector recursively
    if(p){
        Preprint(p->left);                                          // find left tree first
        d.push_back(p->data);                                       // then put info of itself into vector
        if(p->right) r.push_back(p->right->data);
        else r.push_back(0);
        if(p->left) l.push_back(p->left->data); 
        else l.push_back(0);
        del_tree.push_back(p);
        Preprint(p->right);                                         // finally find right tree
    }
}

void Binary_Search_Tree::Print(){                                   // print vector
    Preprint(root);
    cout << "node:  ";
    for(int i=0;i<d.size();i++) cout << setw(2) << d[i] << " ";
    cout << "\nleft:  ";
    for(int i=0;i<l.size();i++) cout << setw(2) << l[i] << " ";
    cout << "\nright: ";
    for(int i=0;i<r.size();i++) cout << setw(2) << r[i] << " ";
}

void Binary_Search_Tree::Delete_tree(){                             // delete the nodes
    for(int i=0;i<del_tree.size();i++) delete (del_tree[i]);
    d.clear();
    r.clear();
    l.clear();
}

#endif