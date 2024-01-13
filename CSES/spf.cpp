#include <bits/stdc++.h>
using namespace std;

#define pll pair<long, long>
#define pii pair<ll, ll>
#define pb push_back
#define ll long long
#define all(arr) arr.begin(), arr.end()
#define _test     \
    ll _TEST;     \
    cin >> _TEST; \
    while (_TEST--)

void print2D(vector<vector<ll>> &v)
{
    for (auto x : v)
    {
        for (auto y : x)
            cout << y << " ";

        cout << endl;
    }
}
void prllString(vector<string> &v)
{
    for (auto x : v)
        cout << x << endl;
}
void prllArray(vector<ll> &v)
{
    for (auto x : v)
        cout << x << " ";

    cout << endl;
}

const int N=1000003;
map<int, int> powers; // key is a prime number, value is its highest power
int spf[N];
ll divisorCount=1;
void solve()
{
     for(ll i=1;i<N;i++)
         spf[i]=i;
     for(ll i=2;i*i<N;i++)
     {
        if(spf[i]==i)
        {
            for(ll j=i*i;j<N;j+=i)
             spf[j]=i;
        }
     }    
}

// helps to calculate divisor count in log (X)
void factorize(int x)
{  
    int p=0,currentDivisor=1;
    while(x>1)
    { 
           if(currentDivisor!=spf[x])
           {
                if(p>0)
                {
                    divisorCount/=powers[currentDivisor]+1;
                    powers[currentDivisor]+=p;
                    divisorCount*=powers[currentDivisor]+1;
                }

                p=1;
                currentDivisor=spf[x];
           }
           else
           p++;

           x/=spf[x];
    }

    if(p>0)
    {
        divisorCount /= powers[currentDivisor] + 1;
        powers[currentDivisor] += p;
        divisorCount *= powers[currentDivisor] + 1;
    }
}

void work()
{
    ll n,q;
    cin>>n>>q;
    
    powers.clear();
    divisorCount=1;
    
    factorize(n);
    map<int,int> org=powers;
    ll orgDivisorCount=divisorCount;
    
    vector<ll>que;
    while(q--)
    {
        int type;
        cin>>type;

        if(type==1)
        {
            int x;
            cin>>x;

            factorize(x);
            que.pb(x);
            
            ll num=n;
            for(auto &q:que)
            {
                num*=q;
                num%=divisorCount;
            }

            cout<<(num==0?"YES\n":"NO\n");

        }
        else
        {
             powers.clear();
             powers=org;
             divisorCount=orgDivisorCount;
             que.clear();
        }
    }

}
int main()
{    
     solve();
    _test
    {
        work();
    }
}