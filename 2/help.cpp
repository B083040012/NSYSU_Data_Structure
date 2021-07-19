#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
class CompareString { 
  
public: 

	char s1[256]; 
    char s2[256]; 
  
    // Declaring and initializing the class 
    // with above two strings 
    CompareString(){};
    CompareString(char AA,char BB){
        s1=AA;
        s2=BB;
            
    } 
     CompareString operator+(CompareString);
   
};


  
  
 char CompareString::operator+(char s3) {
 			
 			
 		 
        for(int i=0;i<256;i++){
        	if((*(s1+i)||*(s2+i))=='1'){
        		*(s3+i)='1';
			}else{
				continue;
			}	
		}
		
		return(s3);
    } 
    
    
// CompareString s1(str1); 
//    CompareString s2(str2); 
//    char s3[256]={0};
//    CompareString (char C[]){
//    	strcpy(this->s3,C);
//	}
//    
//    
//    char operator=(CompareString s3) 
//    { 
//        for(int i=0;i<256;i++){
//        	C[i]=s3[i];
//		}
//    } 
//  


int main()
{
// int N=0;
// cin>>N;
// 
// 	for(int i=0;i<N;i++){
  	char x;
    char AA[256],BB[256],C[256];
 
 	//A input and initialize become 0101 with ascii
string a;
 cin>>a;
 char A[a.length()];
strcpy(A,a.c_str());
 
 for(int i=0;i<256;i++){
 	
 	AA[i]='0';
 }

 for(int i=0;i<a.length();i++){
 	A[i]=int(A[i]);
 	AA[A[i]]='1';
 }
// cout<<endl;
// 
 /////////
 	//B input and initialize become 0101 with ascii
string b;

 cin>>b;
 char B[b.length()];
strcpy(B,b.c_str());

  
 for(int i=0;i<256;i++){
 	
 	BB[i]='0';
 }

 for(int i=0;i<b.length();i++){
 	B[i]=int(B[i]);
 	BB[B[i]]='1';
 }
// 
///////////// 	

CompareString(); 
    
		
 	
 C=AA+BB;
 	
 	
for(int i=0;i<256;i++){
 	cout<<AA[i];
 }
 	cout<<endl;
 for(int i=0;i<256;i++){
 	cout<<BB[i];
 }
 	
	// for(int i=0;i<256;i++){
 cout<<C<<endl;

 
 	

 	cout<<endl;
 
    return 0;
}
