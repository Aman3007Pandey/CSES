#include<bits/stdc++.h>
using namespace std;

int solve(long long a,long long b)
{
    long long ans=0,mn=min(a,b),mx=max(a,b);

    while(mn<mx)
    {
         if(mn==mx)
         break;

         ans++;
         mn<<=1;
    }

    if(mn==mx)
    return ans;

    return -1;
}
int main()
{
   int a,b;
   cin>>a>>b;

   cout<<solve(a,b);
}