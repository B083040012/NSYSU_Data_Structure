// Author:陳柏翰
// Date:Sep,20,2020
// Purpose:建造C++的集合類別
#include<iostream>
using namespace std;

class TSet{
	private:
		char word_array[256];								//宣告private變數word_array
	public:
		TSet();
		friend istream& operator >> (istream&,TSet&);
		friend ostream& operator << (ostream&,TSet&);
		friend int sort_and_set(TSet&);
		friend TSet operator + (const TSet&,const TSet&);
		friend TSet operator - (const TSet&,const TSet&);
		friend TSet operator * (const TSet&,const TSet&);
		friend bool operator >= (const TSet&,const TSet&);
		TSet& operator = (const TSet&);
		bool in (char input);
};

TSet::TSet(){												//宣告constructor
	for(int i=0;i<256;i++){
		word_array[i]='\0';									//利用for迴圈將word_array中的字元初始化(變為'\0')
	}
}

istream& operator >> (istream& in,TSet& t1){				//宣告輸入operator
	in.getline(t1.word_array,256);							//利用getline使得空白字元可以被讀入
	return in;
}

ostream& operator << (ostream& out,TSet& t1){				//宣告輸出operator
	int size=sort_and_set(t1);								//利用sort_and_set將要輸出的TSet刪除重複字元、排列並取得有效長度
	out << "{";
	for(int i=0;i<size;i++) out << t1.word_array[i];		//輸出word_array至有效長度
	out << "}" << endl;
	return out;
}

int sort_and_set(TSet& t1){									//宣告sort_and_set函式
	int size=0;												//宣告size儲存字串長度
	for(int s=0;s<256;s++){									//利用for迴圈取得輸入字串的長度並存入size
		if(t1.word_array[s]=='\0'){
			size=s;
			break;
		} 
	}
	for(int j=0;j<size;j++){								//利用bubble sort由小到大排列字元陣列
		for(int n=0;n<size-1;n++){
			if(t1.word_array[n]>t1.word_array[n+1]) swap(t1.word_array[n],t1.word_array[n+1]);
		}
	}
	for(int i=0;i<size-1;i++){								//利用for迴圈剔除重複元素
		if((t1.word_array[i]==t1.word_array[i+1])){			//一旦偵測到重覆元素，便將後續的元素一個個向前推進
			for(int k=i+1;k<size-1;k++){
				t1.word_array[k]=t1.word_array[k+1];		
			}
			size--;											//並將字串長度縮減
			i--;
		}
	}
	return size;											//回傳字串長度size
}

TSet operator * (const TSet& t1,const TSet& t2){			//宣告交集operator
	TSet t3;												//宣告儲存結果的TSet t3
	int index=0;											//宣告代表將要存入t3陣列的序數index
	for(int i=0;i<256;i++){
		for(int k=0;k<256;k++){
			if(t1.word_array[i]==t2.word_array[k]){			//一旦發現t1和t2共有的元素，便存入t3[index]
				t3.word_array[index]=t1.word_array[i];
				index++;									//後將index加一，表示未來要存入的序數
				break;
			}
		}
	}
	return t3;												//回傳結果t3
}

TSet operator - (const TSet& t1,const TSet& t2){			//宣告差集operator
	TSet t3;												//宣告儲存結果的TSet t3
	int index=0,detect=0;									//宣告代表將要存入t3陣列的序數index，及表示字元比對結果的detect
	for(int i=0;i<256;i++){
		detect=0;											//先將detect設為0，表示比對結果為'不一致'
		for(int k=0;k<256;k++){
			if(t1.word_array[i]==t2.word_array[k]){			//一旦t1和t2字元比對結果相同，detect變為1
				detect=1;	
				break;
			}
		}
		if(detect==0){										//比對結束後如果detect仍為0，表示此t1字元不存在於t2
			t3.word_array[index]=t1.word_array[i];			//將此t1及t2之差集元素存入t3
			index++;
		} 
	}
	return t3;												//回傳結果t3
}

TSet operator + (const TSet& t1,const TSet& t2){			//宣告聯集operator
	TSet t3;												//宣告儲存結果的TSet t3
	int i=0,k=0;											//宣告代表提取t1和存入t3的序數i，和提取t2的序數k
	while(t1.word_array[i]){								//一旦t1[i]非'\0'，便存入t3[i]
		t3.word_array[i]=t1.word_array[i];
		i++;
	}
	while(t2.word_array[k]){								//一旦t2[k]非'\0'，便存入t3[i]
		t3.word_array[i]=t2.word_array[k];
		i++;
		k++;
	}
	return t3;												//回傳t3
}

bool operator >= (const TSet& t1,const TSet& t2){			//宣告包含operator
	int detect=0;											//宣告表示字元比對結果的detect
	for(int i=0;i<256;i++){
		detect=0;											//預設detect為0，代表t1不包含t2[i]
		for(int k=0;k<256;k++){
			if(t2.word_array[i]==t1.word_array[k]){			//一旦t1中有和t2[i]相同之元素，detect變為1
				detect=1;
				break;
			}
		}
		if(detect==0) return false;							//一旦t1不包含任一t2[i]，t1便不包含t2，回傳false
	}
	return true;											//t1包含全部的t2[i]，t1便包含t2，回傳true
}

TSet& TSet:: operator = (const TSet& t1){					//宣告賦值operator
	for(int i=0;i<256;i++){
		this->word_array[i]=t1.word_array[i];				//將t1之值賦予此TSet
	}
	return *this;
}

bool TSet::in(char input){									//宣告'屬於'函式
	for(int i=0;i<256;i++){
		if(input==word_array[i]) return true;				//一旦input存在於此TSet的word_array中，回傳true
	}
	return false;											//如果不存在，回傳false，即input不屬於此TSet
}

int main(){
	int n=0;												//宣告表示測試資料總數的n
	cin >> n;												//輸入測資總數
	for(int i=0;i<n;i++){
		TSet A,B;
		char x;
		cin.ignore();
		cin >> A;
		cin >> B;
		cin >> x;
		TSet C,D,E,F;
		C=A+B;
		D=A*B;
		E=A-B;
		F=B-A;
		cout << "Test Case " << i+1 << ":" << endl;
		cout << "A:" << A;
		cout << "B:" << B;
		cout << "A+B:" << C;
		cout << "A*B:" << D;
		cout << "A-B:" << E;
		cout << "B-A:" << F;
		if(A>=B) cout << "A contains B" << endl;
		else cout << "A does not contain B" << endl;
		if(B>=A) cout << "B contains A" << endl;
		else cout << "B does not contain A" << endl;
		if(A.in(x)) cout << "'" << x << "' is in A" << endl;
		else cout << "'" << x << "' is not in A" << endl;
		if(B.in(x)) cout << "'" << x << "' is in B" << endl;
		else cout << "'" << x << "' is not in B" << endl;
		cout << endl;
	}	
}