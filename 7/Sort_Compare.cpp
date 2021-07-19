// Author:陳柏翰
// Date:Nov 25,2020
// Purpose:Compare the time complexity of different sorting method

#ifndef SORT_CPP
#define SORT_CPP

//#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;

template<class T>
class Sort_Compare{
    private:
        vector<T> data;             // Get the input data
        clock_t start,end;          // start、end timing,use to get executing time
        double exe_time;            // Get the executing time
        int data_size;              // Size of input data
    public:
        void Write_Input_Data(int);
        void Read_Data();
        void Run_Selection_Sort();
        void Recur_Merge_Sort(T *,const int,const int);
        void List_Merge(T *,const int,const int,const int);
        void Run_Merge_Sort();
        void Radix_Sort();
        void Run_Radix_Sort();
        void Run_qsort();
        void Run_sort();
        void Write_Output_Data(string,string);
        double show_exe_time();
        void Process();
};

template<class T>
void Sort_Compare<T>::Write_Input_Data(int size){
    // Write input data from txt file(custom data size)
    ofstream write;
    write.open("input.txt");
    srand(time(NULL));
    if(write.fail()){
        cout << "Write input ERROR\n";
        exit(1);
    }
    else{
        write << size << endl;
        for(int i=0;i<size;i++) write << rand()%size*10 << endl;
    }
    write.close();
}

template<class T>
void Sort_Compare<T>::Read_Data(){
    // Read input data to data vector
    ifstream read;
    read.open("input.txt");
    if(read.fail()){
        cout << "Read file ERROR\n";
        exit(1);
    }
    else{
        T temp;
        read >> data_size;
        while(read >> temp) data.push_back(temp);
    }
    read.close();
}

template<class T>
void Sort_Compare<T>::Run_Selection_Sort(){
    // Run Selection Sort,and get executing time
    Read_Data();
    start=clock();
    for(int i=0;i<data_size-1;i++){
        int min_index=i;
        for(int j=i+1;j<data_size;j++){
            if(data[j]<data[min_index]) min_index=j;
        }
        swap(data[min_index],data[i]);
    }
    end=clock();
    exe_time=double(end-start)/CLOCKS_PER_SEC;
    cout << "Total executing time:" << exe_time << "sec\n";
    Write_Output_Data("outputA","Selection Sort");
    data.clear();
}

template<class T>
void Sort_Compare<T>::Recur_Merge_Sort(T *array,const int left,const int right){
    // Merge Sort by recursion
    if(left>=right) return;
    int mid=(left+right)/2;
    Recur_Merge_Sort(array,left,mid);       // Sort left sublist
    Recur_Merge_Sort(array,mid+1,right);    // Sort right sublist
    List_Merge(array,left,mid,right);       // Merge the sublists
}

template<class T>
void Sort_Compare<T>::List_Merge(T *array,const int left,const int mid,const int right){
    // Merging the lists
    int n1=mid-left+1;
    int n2=right-mid;
    int l_array[n1],r_array[n2];
    for (int i=0;i<n1;i++) l_array[i] = array[left+i];
    for (int j=0;j<n2;j++) r_array[j] = array[mid+1+j];
    int i =0;
    int j =0;
    int k =left;
    while (i<n1 && j<n2) {
        if (l_array[i]<=r_array[j]) {
            array[k]=l_array[i];
            i++;
        }
        else {
            array[k]=r_array[j];
            j++;
        }
        k++;
    }
    while (i<n1) {
        array[k] = l_array[i];
        i++;
        k++;
    }
    while (j<n2) {
        array[k] = r_array[j];
        j++;
        k++;
    }
}


// template<class T>
// int Sort_Compare<T>::Recur_Merge_Sort(vector<T> array,int *link,const int left,const int right){
//     if(left>=right) return left;
//     int mid=(left+right)/2;
//     return List_Merge(array,link,Recur_Merge_Sort(array,link,left,mid),Recur_Merge_Sort(array,link,mid+1,right));
// }

// template<class T>
// int Sort_Compare<T>::List_Merge(vector<T> array,int *link,const int start1,const int start2){
//     int iResult=0,i1,i2;
//     for(i1=start1,i2=start2;i1 && i2;){
//         if(array[i1]<=array[i2]){
//             link[iResult]=i1;
//             iResult=i1;
//             i1=link[i1];
//         }
//         else{
//             link[iResult]=i2;
//             iResult=i2;
//             i2=link[i2];
//         }
//     }
//     if(i1==0) link[iResult]=i2;
//     else link[iResult]=i1;
//     for(int i=0;i<data_size;i++) cout << link[i] << " ";
//     cout << endl;
//     return link[0];
// }

template<class T>
void Sort_Compare<T>::Run_Merge_Sort(){
    // Run Merge Sort and get executing time
    Read_Data();
    T temp[data_size];
    for(int i=0;i<data_size;i++) temp[i]=data[i];
    start=clock();
    Recur_Merge_Sort(temp,0,data_size-1);
    end=clock();
    for(int i=0;i<data_size;i++) data[i]=temp[i];
    exe_time=double(end-start)/CLOCKS_PER_SEC;
    cout << "Total executing time:" << exe_time << "sec\n";
    Write_Output_Data("outputB","Merge Sort");
    data.clear();
}

template<class T>
void Sort_Compare<T>::Radix_Sort(){
    int max_data=data[0];
    for(int i=1;i<data_size;i++) if(data[i]>max_data) max_data=data[i]; // Find number with max digits
    for(int i=1;max_data/i>0;i*=10){
        int count[10]={0};
        T temp[data_size];
        for(int j=0;j<data_size;j++) count[(data[j]/i)%10]++;   // Cal the number of each buckets
        for(int j=1;j<10;j++) count[j]+=count[j-1];         // Prefix sum(position of each data in sorted array)
        for(int j=data_size-1;j>=0;j--){
            temp[count[(data[j]/i)%10]-1]=data[j];          // Put data to sorted array
            count[(data[j]/i)%10]--;
        }
        for(int j=0;j<data_size;j++) data[j]=temp[j];
    }   
}

template<class T>
void Sort_Compare<T>::Run_Radix_Sort(){
    // Run Radix Sort and get executing time
    Read_Data();
    start=clock();
    Radix_Sort();
    end=clock();
    exe_time=double(end-start)/CLOCKS_PER_SEC;
    cout << "Total executing time:" << exe_time << "sec\n";
    Write_Output_Data("outputC","Radix Sort");
    data.clear();
}

template<class T>
int compare( const void *num1,const void *num2){
    // comparing function for qsort()
    return ((*(T *)num1) > (*(T *)num2)) - ((*(T *)num1) < (*(T *)num2));
}

template<class T>
void Sort_Compare<T>::Run_qsort(){
    // Run qsort() and get executing time
    Read_Data();
    T temp[data_size];
    for(int i=0;i<data_size;i++) temp[i]=data[i];
    start=clock();
    qsort(temp,data_size,sizeof(T),compare<T>);
    end=clock();
    for(int i=0;i<data_size;i++) data[i]=temp[i];
    exe_time=double(end-start)/CLOCKS_PER_SEC;
    cout << "Total executing time:" << exe_time << "sec\n";
    Write_Output_Data("outputD","C qsort()");
    data.clear();
}

template<class T>
void Sort_Compare<T>::Run_sort(){
    // Run sort() and get executing time
    Read_Data();
    start=clock();
    sort(data.begin(),data.end());
    end=clock();
    exe_time=double(end-start)/CLOCKS_PER_SEC;
    cout << "Total executing time:" << exe_time << "sec\n";
    Write_Output_Data("outputE","C++ sort()");
    data.clear();
}

template<class T>
void Sort_Compare<T>::Write_Output_Data(string file_name,string sort_type){
    // Write sorted data into output file
    ofstream write;
    write.open(file_name+".txt");
    if(write.fail()){
        cout << "Write output file ERROR\n";
        exit(1);
    }
    else{
        write << sort_type << endl;
        for(int i=0;i<data_size;i++){
            write << data[i] << endl;
        }
    }
    write.close();
    data_size=0;
}

template<class T>
double Sort_Compare<T>::show_exe_time(){
    return exe_time;
}

template<class T>
void Sort_Compare<T>::Process(){
    int function,size;
    vector<double> exe_time(5,0);
    // Select function
    cout << "===Sorting Comparision(Run 10 times)===\n";
    cout << "Select Function:\n1.Read input file in folder\n2.Custom data size and generate new input file\n";
    cin >> function;
    if(function==2){
        cout << "Input the size of data:";
        cin >> size;
    }

    // Generate 10 different test data file
    for(int i=0;i<10;i++){
        if(function==2) Write_Input_Data(size);
        cout << "test " << i+1 << ":\n";
        cout << "Runnimg Selection Sort...";
        Run_Selection_Sort();
        exe_time[0]+=show_exe_time();
        cout << "Runnimg Merge Sort...";
        Run_Merge_Sort();
        exe_time[1]+=show_exe_time();
        cout << "Runnimg Radix Sort...";
        Run_Radix_Sort();
        exe_time[2]+=show_exe_time();
        cout << "Running C_qsort()...";
        Run_qsort();
        exe_time[3]+=show_exe_time();
        cout << "Running C++_sort()...";
        Run_sort();
        exe_time[4]+=show_exe_time();
        cout << "\n";
    }

    // Output average executing time
    cout << "\n\n\nAvg. exe time:\n";
    cout << "Selection Sort:" << exe_time[0]/10 << "sec\n";
    cout << "Merge Sort:" << exe_time[1]/10 << "sec\n";
    cout << "Radix Sort:" << exe_time[2]/10 << "sec\n";
    cout << "C qsort():" << exe_time[3]/10 << "sec\n";
    cout << "C++ sort():" << exe_time[4]/10 << "sec\n";
}

#endif