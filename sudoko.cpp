#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
bool check(int,int ,vector<vector<int>>&, int);
bool solve(vector<vector<int>>&vect)
{  int lastr=0;
int lastc= 0;
    for(int i=0;i<9;i++)
    { 
        for(int j=0;j<9;j++)
        {   
            if(vect[i][j]==0)
            {
              for(int k=1;k<=9;k++)
              {
                 if(check(i,j,vect,k))
                 {
                    vect[i][j]=k;
                  if(solve(vect))
                  return true;
                  vect[i][j]=0;
                  } 
 
              }
              
            return false;
            }
        }
    }
    return true;
}
bool check(int i,int j,vector<vector<int>>&vect, int num)
{  
        for(int x=0;x<9;x++)
        {   
         if(vect[i][x]==num || vect[x][j]==num)
           return false;
        
        }
       
        for(int m= (i/3 )* 3; m< ((i/3)*3 +3);m++)
        {
            for(int n= (j/3)*3; n< ((j/3)*3 +3); n++)
            { 
                if(vect[m][n]==num)
                {
                     return false;
                  
                }
            }
        }
       
    return true;
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
        cout<<"enter row and col"<<endl;
        cin>>row>>column;
        int element;
        cout<<"enter element"<<endl;
        cin>>element;
        sudoko[row][column]=element;
        cout<<"another element?(1 if yes,-1 if no)"<<endl;
        cin>>a;
    }
    if(solve(sudoko))
    {
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cout<<sudoko[i][j]<<" ";
        }
        cout<<endl;
    }
    }
    else{
        cout<<"Can't Solve"<<endl;
    }
    return 0;
}