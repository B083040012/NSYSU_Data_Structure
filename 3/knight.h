// Author:陳柏翰
// Date:Oct 5,2020
// Purpose:輸出西洋棋騎士走完棋盤的順序(stack)
#ifndef KNIGHT_H
#define KNIGHT_H
#include<iostream>

namespace walk{
    using namespace std;
    class Knight{
        private:
            //宣告座標stack row_lo,col_lo、方向stack dir_lo、棋盤邊長size、棋盤map、當前座標curr_x,curr_y、當前方向curr_dir、stack數量or最上層index top、原點座標ini_x,ini_y
            int *row_lo,*col_lo,*dir,size,**map,curr_x,curr_y,curr_dir,top,ini_x,ini_y;
        public:
            Knight(int,int,int);
            void push(int,int,int);
            int pop();
            int detect(int);
            int walk();
            void show_result();
            ~Knight();
    };
} 
#endif