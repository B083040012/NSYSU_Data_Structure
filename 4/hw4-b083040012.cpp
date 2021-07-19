// Author:陳柏翰
// Date:Oct 5,2020
// Purpose:輸出西洋棋騎士走完棋盤的順序(By recursive)
#include<iostream>
using namespace std;
#include"knight.cpp"
using namespace walk;

int walk_test(int size){
    for(int i=0;i<=size/2;i++){                                          //嘗試以棋盤上一半的座標為原點看看是否有解
        for(int k=0;k<size;k++){
            Knight k1(size,i,k);                                        //宣告Knight物件k1，傳入邊長及原點座標
            if(k1.walk(k1.get_board(),k1.get_ini_y(),k1.get_ini_x())){
                k1.show_result();                                       //若以(i,k)為原點有解，輸出結果，return 1
                return 1;
            }
            //k1.~Knight();
        }
    }
    return 0;                                                           //若無解，return 0
}

int main(){
    for(int size=1;size<9;size++){                                      //宣告size表示棋盤邊長，測試1~8
        cout << "Size=" << size << endl;
        if(walk_test(size)) continue;
        else cout << "No solution\n\n";                                 //若無解，輸出No solution
    }
}