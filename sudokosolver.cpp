#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

int main()
{
    cout<<"Give Input"<<endl;
    vector<vector<int>> sudoko(9,vector<int>(9,0));
    int a;
    a=1;
    cout<<"enter elements"<<endl;
    while(a!=-1)
    {
        int row,column;
        cin>>row>>column;
        int element;
        cin>>element;
        cout<<"another element?(1 if yes,-1 if no)"<<endl;
        cin>>a;
    }
    
}