#include<bits/stdc++.h>
#include<iostream>
using namespace std;

class Uncompress{
    private:
        string input_file_name,output_file_name;
        map<unsigned char,string> encode_list;
        vector<unsigned char>ch_ptr;
        string decoded_data;
        int bit_num,original_byte;
    public:
        Uncompress(string i_name,string o_name):input_file_name(i_name),output_file_name(o_name){
            decoded_data="";
            bit_num=original_byte=0;
        };
        void Read_File();
        void Huffman_Decode();
        void Write_File();
        void Process();
};

void Uncompress::Read_File(){
    ifstream read_f;
    int flag=0;
    string trash;
    read_f.open(input_file_name,ios::binary);
    for(int i=0;i<3;i++){
        getline(read_f,trash);
        if(i==0){
            int pos=trash.find_first_of(':');
            original_byte=atoi(trash.substr(pos+1,trash.size()).c_str());
        }
    }
    // unsigned char ch;
    // while(read_f.eof()){
    //     read_f  >> std::noskipws >> ch;
    //     ch_ptr.push_back(ch);
    // }
    // cout << bit_num << endl;
    for(string line;getline(read_f,line);){
        unsigned char ch;
        string code;
        // cout << "line:" << line.size() << endl;
        if(line.find("=")!=string::npos && line.find("=")<4 && line.size()<15 && flag<256){
            flag++;
            // cout << "In!!" << endl;
            int ch_pos=line.find_first_of("=",0);
            string ch_str=line.substr(0,ch_pos);
            int ch_int=atoi(ch_str.c_str());
            ch=(unsigned char)(ch_int);
            code=line.substr(ch_pos+1,line.size()-1);
            // cout << ch << "   " << code << endl;
            encode_list[ch]=code;
            // cout << "encode_list:" << encode_list[ch] << endl;
        }
        else{
            // cout << "In\n";
            for(int i=0;i<line.size();i++) ch_ptr.push_back(line[i]);
            // ch_ptr.push_back('\r');
            ch_ptr.push_back('\n');
        }
    }     
    // cout << "In Uncompress read file\n";
    // for(auto ptr=encode_list.begin();ptr!=encode_list.end();ptr++){
    //     cout << (*ptr).first << "=" << (*ptr).second << endl;
    // }
}

void Uncompress::Huffman_Decode(){
    string data_bit="";
    for(int i=0;i<ch_ptr.size();i++){
        bitset<8> ch_byte(ch_ptr[i]);
        data_bit+=ch_byte.to_string();
    }
    // cout << "data_bit:" << data_bit << endl;
    string temp_data="";
    for(int i=0,k=0;i<data_bit.size(),k<original_byte;i++){
        temp_data+=data_bit[i];
        for(auto ptr=encode_list.begin();ptr!=encode_list.end();ptr++){
            if(temp_data==(*ptr).second){
                // if((*ptr).first!=13){
                //     decoded_data+=(*ptr).first;
                //     cout << ((*ptr).first);
                // }
                decoded_data+=(*ptr).first;
                k++;
                // cout << ((*ptr).first);
                temp_data="";
            }
        }
    }
    // cout << "In Huffman_Decode\n";
    // for(int i=0;i<decoded_data.size();i++){
    //     cout << decoded_data[i];
    //     if((i+1)%10==0) cout <<endl;
    // }
}

void Uncompress::Write_File(){
    ofstream write_f;
    write_f.open(output_file_name);
    for(int i=0;i<decoded_data.size();i++){
        // if(i==5) continue;
        // if(decoded_data[i]==13 && decoded_data[i+1]==10){
        //     cout << "In!!!\n";
        //     write_f << endl;
        //     i++;
        // }
        if(decoded_data[i]==13){
            bitset<8> temp("00001101");
            write_f << static_cast<unsigned char>(temp.to_ulong());
        }
        else if(decoded_data[i]==10){
            bitset<8> temp("00001010");
            write_f << static_cast<unsigned char>(temp.to_ulong());
        }
        else write_f << decoded_data[i];
        // cout << decoded_data[i];
    }
    write_f.close();
}

void Uncompress::Process(){
    Read_File();
    Huffman_Decode();
    Write_File();
}