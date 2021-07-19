// Author:陳柏翰
// Date:Oct 23,2020
// Purpose:Calculate addition and multiplication of polynominal
#include<iostream>
#include"poly.cpp"
using namespace std;

int main(){
    int P,Q,i=1;
    while(1){
        Poly A,B,C,D;           // set Poly A,B,C (result of A+B),D (result of A*B)
        cin >> P;
        for(int i=0;i<P;i++){   // set A
            int c1,e1;
            cin >> c1 >> e1;
            A.add(c1,e1);
        }
        cin >> Q;
        for(int i=0;i<Q;i++){   // set B
            int c2,e2;
            cin >> c2 >> e2;
            B.add(c2,e2);
        }
        C=A+B;                  // addition
        D=A*B;                  // multiplication
        cout << "Case " << i << ":" << endl;    // print the result
        cout << "ADD:\n";
        C.print();
        cout << "MULTIPLY:\n";
        D.print();
        i++;
    }
}