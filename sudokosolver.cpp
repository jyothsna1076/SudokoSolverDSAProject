#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
int check(int,int ,vector<vector<int>>);
void solve(vector<vector<int>>&vect)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(vect[i][j]==0)
            {
                vect[i][j] = check(i,j,vect);
            }
        }
    }
}
int check(int i,int j,vector<vector<int>>vect)
{ 
   for(int k=1;k<=9;k++)
   {
     bool same= false; 
        for(int col=0;col<9;col++)
        {   bool same= false;
         if(vect[i][col]==k)
          same= true;
          continue;
        }
         for(int row=0;row<9;row++)
        {  bool same= false;
         if(vect[row][j]==k)
          same= true;
          continue;
        }
        for(int m= k/3; m< (k/3 +3);m++)
        {
            for(int n= j/3; n< (j/3 +3); j++)
            {  bool same= false;
                if(vect[m][n]==k)
                {
                    same= true;
                    continue;
                }
            }
        }
        if(same== false)
        {
            vect[i][j]= k;
            break;
        }
       
    
   }
}

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
        sudoko[row][column]=element;
        cout<<"another element?(1 if yes,-1 if no)"<<endl;
        cin>>a;
    }
    solve(sudoko);
    
}