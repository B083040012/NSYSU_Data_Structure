// Author:陳柏翰
// Date:Sep,20,2020
// Purpose:建造C++的集合類別
#include<iostream>
#include"Tset.cpp"											//引用Tset
using namespace std;
using namespace Set;

int main(){
    int n=0;												//宣告表示測試資料總數的n
	cin >> n;												//輸入測資總數
	for(int i=0;i<n;i++){
		TSet A("A"),B("B");									//宣告Tset A,B進行運算
		char x;												//宣告字元x進行'屬於'運算
		cin.ignore();
		cin >> A;											//輸入A
		cin >> B;											//輸入B
		cin >> x;											//輸入x
		TSet C("\0"),D(("\0"));								//宣告Tset C,D承接運算結果
		C=A+B;												//C為'A和B之交集'結果
		D=A*B;												//D為'A和B之聯集'結果
		cout << "Test Case " << i+1 << ":" << endl;			//印出測試結果
		cout << A;
		cout << B;
		cout << C;											//印出C
		cout << D;											//印出D
		cout << (A-B);										//印出A和B之差集
		cout << (B-A);										//印出B和A之交集
        cout << (A>=B) << endl;								//印出'A包含B'之結果
        cout << (B>=A) << endl;								//印出'B包含A'之結果
        cout << "'" << x << "'" << A.in(x) << endl;			//印出'x屬於A'之結果
        cout << "'" << x << "'" << B.in(x) << endl;			//印出'x屬於B'之結果
		cout << endl;
	}	
}