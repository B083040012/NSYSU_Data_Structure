// Author:陳柏翰
// Date:Sep,20,2020
// Purpose:建造C++的集合類別
#ifndef HW2_H                                                   //利用ifndef避免重複引用
#define HW2_H
#include<iostream>

namespace Set{
    using namespace std;
    class TSet{
        private:
            string name;                                        //宣告name表示Tset的名稱
            char word_array[256];								//宣告private變數word_array表示Tset中的字元
        public:
            TSet(string);
            friend istream& operator >> (istream&,TSet&);
            friend ostream& operator << (ostream&,TSet);
            friend TSet operator + (const TSet&,const TSet&);
            friend TSet operator - (const TSet&,const TSet&);
            friend TSet operator * (const TSet&,const TSet&);
            friend string operator >= (const TSet&,const TSet&);
            TSet& operator = (const TSet&);
            string in (char input);
    };
}

#endif