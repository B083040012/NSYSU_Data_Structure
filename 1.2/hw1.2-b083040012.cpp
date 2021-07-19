// Author:陳柏翰(B083040012)
// Date:Sep,9,2020
// Purpose:印出1~N(N<=50)之間所有整數之階層

#include<iostream>
#include<vector>
using namespace std;

void turn_to_one(int *array){
	for(int i=1;i<99;i++){				//將陣列中之各個元素(第一個除外)設為0
		array[i]=0;
	}
	array[0]=1;					//將第一個元素設為1
}

int main(){
	int fac[100];					//建立陣列fac儲存各個位數
	int input;					//宣告變數input儲存輸入的值
	int index=0;					//宣告變數index儲存最高位數
	int temp=0;					//宣告變數temp儲存各個位數欲進位的值
	vector<int> input_list;				//宣告vector input_list儲存各個input值
	do{					
		cin >> input;				//使用者輸入input
		input_list.push_back(input);		//並儲存至input_list
	}while(input>0);
	for(int i=0;i<input_list.size();i++){		//依據input_list內的值進行運算
		temp=0;					//將temp歸零
		turn_to_one(fac);			//將fac的值變為初始值1
		for(int k=1;k<=input_list[i];k++){
			for(int j=0;j<70;j++){
				fac[j]=fac[j]*k+temp;	//將fac中的第j位數乘上k並加上欲進位值temp
				temp=fac[j]/10;		//將當前位數除以10得商存入temp(下一個位數欲進位值)
				fac[j]%=10;		//當前位數除以十之餘為其最終值
				if(fac[j]!=0) index=j;	//index紀錄最後非零位數
			}
			cout << k << "!=";
			for(int h=index;h>=0;h--){	//以index為首輸出當前k階之值
				cout << fac[h];
			}
			cout << endl;
		}
		cout << endl;
	}
}