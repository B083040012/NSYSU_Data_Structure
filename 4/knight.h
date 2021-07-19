// Author:陳柏翰
// Date:Oct 5,2020
// Purpose:輸出西洋棋騎士走完棋盤的順序(By recursive)
#ifndef KNIGHT_H
#define KNIGHT_H
#include<iostream>

namespace walk{
    using namespace std;
    class Knight{
        private:
            int size,**map,step,ini_x,ini_y;    //宣告棋盤邊長size、棋盤map、步數step、起始座標ini_x,ini_y
        public:
            Knight(int,int,int);
            int get_ini_x();
            int get_ini_y();
            int** get_board();
            int detect(int,int,int);
            int walk(int**,int,int);
            void show_result();
            ~Knight();
    };
} 
#endif