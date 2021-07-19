// Author:陳柏翰
// Date:Oct 5,2020
// Purpose:輸出西洋棋騎士走完棋盤的順序(By recursive)
#ifndef KNIGHT_CPP
#define KNIGHT_CPP
#include"knight.h"
#include<iomanip>

namespace walk{
    Knight::Knight(int s,int x,int y):size(s),ini_x(x),ini_y(y){//傳入size、ini_x、ini_y
        step=1;                                                 //預設步數為1(即起始點)
        map=new int*[s];                                        //建立動態二微陣列map
        for(int i=0;i<s;i++){
            map[i]=new int[s];
            for(int k=0;k<s;k++){
                map[i][k]=0;                                    //預設棋盤內各格為0(未走過)
            }
        }
        map[ini_y][ini_x]=step;                                 //將起始點標上步數1
    }
    inline int Knight::get_ini_x(){return ini_x;}
    inline int Knight::get_ini_y(){return ini_y;}
    inline int** Knight::get_board(){return map;}

    int Knight::detect(int pre,int curr_x,int curr_y){
        int new_dir=pre+1;                                      //宣告new_dir表示新的方向，預設為舊方向+1
        while(1){
            int temp_x,temp_y;                                  //宣告temp_x、temp_y表示欲前進的座標
            int k_i[8]={-2,-1,1,2,2,1,-1,-2};                   //宣告k_i,k_j表示kn向量
            int k_j[8]={1,2,2,1,-1,-2,-2,-1};
            if(new_dir>8) return -1;                            //若已經沒有方向可走(new_dir>8)，return -1
            else{
                temp_y=curr_y+k_i[new_dir-1];                   //將curr_x,curr_y加上k(new_dir)向量,表示為temp_x,temp_y
                temp_x=curr_x+k_j[new_dir-1];
            }
            if(temp_x>=size || temp_x<0 || temp_y>=size || temp_y<0 || map[temp_y][temp_x]!=0){
                new_dir++;                                      //若temp_x,temp_y碰到邊界或該座標已經走過(!=0)，嘗試下一個方向
                continue;
            }
            else return new_dir;                                //若此new_dir可走，回傳該方向
        }
    }
    int Knight::walk(int **board,int c_x,int c_y){
        if(step==size*size) return 1;                           //若step==size*size，即表示走完全部(以ini_x,ini_y為原點有解)，回傳1
        for(int i=0;i<8;i++){                                   //以座標(c_x,c_y)為基準嘗試全部(8個)方向看看是否有解
            int next_dir=detect(i,c_x,c_y);                     //篩選掉不合適的方向
            if(next_dir!=-1){
                int k_i[8]={-2,-1,1,2,2,1,-1,-2};               //宣告k_i,k_j表示kn向量
                int k_j[8]={1,2,2,1,-1,-2,-2,-1};
                int next_x=c_x,next_y=c_y;                      //宣告next_x,next_y表示目前座標(c_x,c_y)加上k(next_dir)向量後的座標
                next_x+=k_j[next_dir-1];
                next_y+=k_i[next_dir-1];
                board[next_y][next_x]=++step;                   //將(next_x,next_y)視為新的一步，標上step
                if(walk(map,next_x,next_y)) return 1;           //若以新基準(next_x,next_y)有解，表示以(c_x,c_y)為基準有解，return 1
                else{                                           //若以(next_x,next_y)為基準無解，
                    map[next_y][next_x]=0;                      //須將該座標歸零
                    step--;                                     //步數-1
                    i=next_dir-1;                               //以(c_x,c_y)為準嘗試下一個方向
                }
            }
            else break;                                         //若已沒有方向可走，表示以(c_x,c_y)為基準無解，return 0
        }
        return 0;
    }
    void Knight::show_result(){                                 //印出棋盤
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                cout << setw(2) << map[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    Knight::~Knight(){
        for(int i=0;i<size;i++) delete[] map[i];
        delete []map;
    }
}
#endif