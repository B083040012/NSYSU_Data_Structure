// Author:陳柏翰(B083040012)
// Date:Sep,9,2020
// Purpose:製作N階魔方陣(magic square)

#include<iostream>
#include<iomanip>
using namespace std;

void set_numbers(int **sq,int n){
	int x=n/2,y=0;					      //宣告x,y表示即將瑱入數字的座標
	sq[x][y]=1;					      //於指定位置填入數字1
	for(int i=2;i<=n*n;i++){			      
		if (sq[(x-1+n)%n][(y-1+n)%n]!=0) y=(y+1+n)%n; //判斷(x-1,y-1)的位置是否已填入數字(是否為0),若已有數字(非0)則將座標訂為(x,y+1)
		else{
			x=(x-1+n)%n;			      //否則將座標訂為(x-1,y-1)
			y=(y-1+n)%n;
		}
		sq[x][y]=i;				      //最後將數字i填入指定座標
	}
}

int main(){
	for(int i=1;i<=9;i+=2){				      //利用for來建立1,3,5,7,9階之魔方陣
		int **square=new int*[i];		      //建立i*i的二維陣列
		for(int j=0;j<i;j++){
			square[j]=new int[i];
			for(int p=0;p<i;p++){
				square[j][p]=0;		      //將陣列內的數字預設為0,用於後續判斷該格是否已填入數字
			}
		}
		set_numbers(square,i);			      //將數字填入陣列
		for(int row=0;row<i;row++){		      //輸出陣列
			for(int col=0;col<i;col++){
				cout << setw(2) << square[col][row] << " ";
			}
			cout << endl;
		}
		cout << endl;
		for(int k=0;k<i;k++){			      //輸出結束,釋放記憶體
			delete [] square[k];
		}
		delete [] square;
	}
	return 0;
}
