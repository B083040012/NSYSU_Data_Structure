// Author:陳柏翰
// Date:Oct 5,2020
// Purpose:輸出西洋棋騎士走完棋盤的順序(stack)
#ifndef KNIGHT_CPP
#define KNIGHT_CPP
#include"knight.h"
#include<iomanip>

namespace walk{
    Knight::Knight(int s,int x,int y):size(s),ini_x(x),ini_y(y){//傳入size、ini_x、ini_y
        curr_x=ini_x;                                           //將當前座標設為起始座標
        curr_y=ini_y;
        curr_dir=0;                                             //當前方向預設為0
        top=0;                                                  //將top預設為0
        row_lo=new int[s*s];                                    //建立row_lo,col_lo,dir動態一維陣列
        col_lo=new int[s*s];
        dir=new int[s*s];
        map=new int*[s];                                        //建立動態二維陣列map
        for(int i=0;i<s;i++){
            row_lo[i]=col_lo[i]=dir[i]=-1;                      //將stack中的值預設為0
            map[i]=new int[s];
            for(int k=0;k<s;k++){
                map[i][k]=0;                                    //預設棋盤內各格為0(未走過)
            }
        }
    }
    void Knight::push(int i,int j,int d){
        top++;                                                  //stack增加一層
        row_lo[top]=i;                                          //將當前的座標和方向放入stack中
        col_lo[top]=j;
        dir[top]=d;
        map[i][j]=top;                                          //將當前步數(其值=top)填入map
    }
    int Knight::pop(){
        int error_dir=dir[top];                                 //將錯誤的方向dir[top]存入error_dir
        curr_y=row_lo[top];                                     //將最上層的座標存入當前座標，表示到退一步
        curr_x=col_lo[top];
        map[row_lo[top]][col_lo[top]]=0;                        //將map上該座標歸零
        row_lo[top]=-1;                                         //將stack中的值回復預設值
        col_lo[top]=-1;
        dir[top]=-1;
        top--;                                                  //stack減少一層
        return error_dir;                                       //回傳error_dir，以便判斷下一個方向
    }
    int Knight::detect(int pre){
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
    int Knight::walk(){
        while(1){
            curr_dir=detect(curr_dir);                          //偵測下一個可走的方向
            if(curr_dir==-1){                                   //若沒有方向可走:
                if(top==size*size-1){                           //且top==size*size-1，表示以ini_x,ini_y為原點有解
                    map[curr_y][curr_x]=++top;                  //在map上標示最後一步，return 0;
                    return 1;
                }
                if(curr_x==ini_x && curr_y==ini_y){             //且當前座標為原點，表示以ini_x,ini_y為原點無解，return 0
                    return 0;
                }
                else{
                    curr_dir=pop();                             //其他情況-->表示必須到退一步，並將前一個錯誤方向存入curr_dir，以此為基準偵測下一個方向
                    continue;
                }
            }
            else{
                push(curr_y,curr_x,curr_dir);                   //若有方向可走-->將curr_x,curr_y和curr_dir push進stack中
                int k_i[8]={-2,-1,1,2,2,1,-1,-2};               //宣告k_i,k_j表示kn向量
                int k_j[8]={1,2,2,1,-1,-2,-2,-1};
                curr_y+=k_i[curr_dir-1];                        //將當前座標加上k(curr_dir-1)向量得到新的當前向量
                curr_x+=k_j[curr_dir-1];
                curr_dir=0;                                     //將curr_dir歸零(新座標適用)
            }
        }
    }
    void Knight::show_result(){                                 //印出map
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
        delete[] map;
        delete[] row_lo;
        delete[] col_lo;
        delete[] dir;
    }
}
#endif