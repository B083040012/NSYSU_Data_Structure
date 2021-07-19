#include<bits/stdc++.h>
#include"Huffman_Tree.cpp"
using namespace std;

class Compress{
    private:
        string input_file_name,output_file_name;
        int bit_num;
        double origin_byte,compress_byte,compress_rate;
        vector<unsigned char> data;
        deque<Node *> tree;
        map<unsigned char,string> encode_list;
    public:
        Compress(string,string);
        void Read_File();
        void Huffman_Encode();
        void Recursive_Encode(Node *,string);
        void Write_File();
        void Process();
        friend class Huffman_Tree;
};

Compress::Compress(string in_name,string out_name):input_file_name(in_name),output_file_name(out_name){
    bit_num=origin_byte=compress_byte=0;
};

void Compress::Read_File(){
    ifstream read(input_file_name,ios::binary);
    while(!read.eof()){
        char ch;
        read.get(ch);
        // if(ch=='\r') continue;
        // read >> ch;
        // read >> std::noskipws >> ch;
        data.push_back(ch);
    }
    cout << "Read Complete\n";
    origin_byte=data.size()-1;
    read.close();
}

void Compress::Huffman_Encode(){
    Huffman_Tree t1(data);
    tree=t1.build_tree();
    Recursive_Encode(tree.front(),"");
    // cout << "In Huffman_encode:\n";
    // for(auto ptr=encode_list.begin();ptr!=encode_list.end();ptr++){
    //     cout << (*ptr).first << " " << (*ptr).second << endl;
    // }
}

void Compress::Recursive_Encode(Node *ptr,string code){
    if(!ptr->lchild && !ptr->rchild){
        // cout << "Node: " << ptr->data << " " << ptr->freq << endl;
        encode_list[ptr->data]=code;
        return;
    }
    if(ptr->lchild) Recursive_Encode(ptr->lchild,code+"0");
    if(ptr->rchild) Recursive_Encode(ptr->rchild,code+"1");
}

void Compress::Write_File(){
    ofstream write_f;
    ifstream get_byte;
    string data_stream="";
    for(int i=0;i<data.size();i++){
        data_stream+=encode_list[data[i]];
    }
    // bit_num=data_stream.size();
    while(data_stream.size()%8){
        data_stream+="0";
    }
    write_f.open(output_file_name,ios::binary);
    // write_f << bit_num << endl;
    for(auto ptr=encode_list.begin();ptr!=encode_list.end();ptr++){
        write_f << static_cast<int>((*ptr).first) << "=" << (*ptr).second << endl;
    }
    for(int i=0;i<data_stream.size();i+=8){
        string temp="";
        for(int j=i;j<i+8;j++){
            temp+=data_stream[j];
        }
        bitset<8> bit_code(temp);
        write_f << static_cast<unsigned char>(bit_code.to_ulong());
    }
    write_f.close();
    get_byte.open(output_file_name,ios::in);
    get_byte.seekg(0,ios::end);
    compress_byte=get_byte.tellg();
    get_byte.close();
    // compress_byte+=63;
    compress_rate=compress_byte/origin_byte;
    write_f.open(output_file_name);
    write_f << "Original file:" << origin_byte << endl;
    write_f << "Compress file:" << compress_byte << endl;
    write_f << "Compression rate:" << compress_rate*100 << "%" << endl;
    for(auto ptr=encode_list.begin();ptr!=encode_list.end();ptr++){
        write_f << static_cast<int>((*ptr).first) << "=" << (*ptr).second << endl;
    }
    for(int i=0;i<data_stream.size();i+=8){
        string temp="";
        for(int j=i;j<i+8;j++){
            temp+=data_stream[j];
        }
        bitset<8> bit_code(temp);
        write_f << static_cast<unsigned char>(bit_code.to_ulong());
    }
    // write_f.seekp(0L,ios::beg);
    write_f << "Original file:" << origin_byte << endl;
    write_f << "Compress file:" << compress_byte << endl;
    write_f << "Compression rate:" << compress_rate*100 << "%" << endl;
    write_f.close();
}

void Compress::Process(){
    Read_File();
    Huffman_Encode();
    Write_File();
}