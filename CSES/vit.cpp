#include <bits/stdc++.h>
using namespace std;


int solve(vector<int>&arr)
{
     int mx=0,idx=0,ans=1;
     int n=arr.size();

     queue<int>q;
     q.push(0);

     while(!q.empty())
     {
         int k=q.size(),sum=0;
         idx++;
         while(k--)
         {
            int node=q.front();
            q.pop();

            if(arr[node]%2)
            sum+=arr[node];

            if(2*node+1<n)
            q.push(2*node+1);
            if(2*node+2<n)
            q.push(2*node+2);
         }

         if(mx<sum)
         {
            mx=sum;
            ans=idx;
         }
     }

     return ans;
}

int main()
{ 
   vector<int>arr={1,2,3,4,5,6,7,8};
   cout<<solve(arr);
}


