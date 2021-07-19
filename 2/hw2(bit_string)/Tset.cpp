// Author:陳柏翰
// Date:Sep,20,2020
// Purpose:建造C++的集合類別
#ifndef HW2_CPP                                                 //利用ifndef避免重複引用
#define HW2_CPP
#include"Tset.h"

namespace Set{
    TSet::TSet(string n):name(n){                               //宣告constructor
        for(int i=0;i<256;i++){
            word_array[i]='\0';							        //利用for迴圈將word_array初始化(變為'\0')
        }
    }
    istream& operator >> (istream& in,TSet& t1){                //宣告輸入operator
        string input;                                           //宣告input承接輸入的字串
        int i=0;                                                //宣告i表示要放入word_array的字元順序
        getline(in,input);                                      //輸入字串至input
        while(input[i]){
            t1.word_array[int(input[i])]=input[i];              //將input中的字元依照其ascii放入相對應(int(input[i]))的word_array
            i++;
        }
        return in;
    }
    ostream& operator << (ostream& out,TSet t1){				//宣告輸出operator
        out << t1.name << ": {";
        for(int i=0;i<256;i++){
            if(t1.word_array[i]!='\0') out << t1.word_array[i]; //若word_array[i]非'\0'，代表Tset中有ascii code為i的字元，輸出word_array[i]
        }
        out << "}" << endl;
        return out;
    }
    TSet operator * (const TSet& t1,const TSet& t2){			//宣告交集operator
        TSet t3(t1.name+"*"+t2.name);							//宣告表示運算結果的t3
        for(int i=0;i<256;i++){
            if(t1.word_array[i]!='\0' && t2.word_array[i]!='\0'){   //若t1與t2皆有ascii code為i的字元(!=0)，
                t3.word_array[i]=t1.word_array[i];                  //則將ascii code為i的字元放入t3的word_array[i]
            }
        }
        return t3;												//回傳結果t3
    }
    TSet operator - (const TSet& t1,const TSet& t2){			//宣告差集operator
        TSet t3(t1.name+"-"+t2.name);							//宣告表示運算結果的t3
        for(int i=0;i<256;i++){
            if(t1.word_array[i]!='\0' && t2.word_array[i]=='\0'){   //若t1有ascii code為i的字元(!='\0')但t2沒有(=='\0')，
                t3.word_array[i]=t1.word_array[i];                  //則將ascii code為i的字元放入t3的word_array[i]
            }
        }
        return t3;												//回傳結果t3
    }
    TSet operator + (const TSet& t1,const TSet& t2){			//宣告聯集operator
        TSet t3(t1.name+"+"+t2.name);							//宣告表示運算結果的t3
        for(int i=0;i<256;i++){
            if(t1.word_array[i]!='\0') t3.word_array[i]=t1.word_array[i];       //若t1或t2有ascii code為i的字元，將其放入t3
            else if(t2.word_array[i]!='\0') t3.word_array[i]=t2.word_array[i];
        }
        return t3;												//回傳t3
    }
    string operator >= (const TSet& t1,const TSet& t2){         //宣告包含operator
        for(int i=0;i<256;i++){
            if(t2.word_array[i]!='\0' && t1.word_array[i]=='\0'){
                return (t1.name+" does not contain "+t2.name);      //若t1不具有t2所擁有的字元，t1便不包含t2
            }
        }
        return (t1.name+" contains "+t2.name);					//若t1具有t2全部的字元，t1包含t2
    }
    TSet& TSet:: operator = (const TSet& t1){					//宣告賦值operator
        this->name=t1.name;                                     //賦予t1名稱給此Tset(name)
        for(int i=0;i<256;i++){
            this->word_array[i]=t1.word_array[i];				//將t1之值賦予此TSet
        }
        return *this;
    }
    string TSet::in(char input){								//宣告'屬於'函式
        for(int i=0;i<256;i++){
            if((input)==word_array[i]) return (" is in "+this->name);	//一旦input存在於此TSet的word_array中，input屬於此Tset，回傳相應訊息
        }
        return (" is not in "+this->name);						//如果不存在，即input不屬於此TSet，回傳相應訊息
    }
}

#endif