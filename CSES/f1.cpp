
#include<bits/stdc++.h>
using namespace std;

#define pll pair<long long, long long>
#define pii pair<ll,ll>
#define pb push_back
#define ll long long
#define all(arr) arr.begin(), arr.end()
#define _test     \
    ll _TEST;     \
    cin >> _TEST; \
    while (_TEST--)

const int mod = 998244353;

void print2D(vector<vector<ll>> & v)
{
    for(auto x:v)
    {
        for(auto y:x)
        cout<<y<<" ";

        cout<<endl;
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

        cout<<endl;
}

void prll(vector<vector<char>>&mat)
{
    for(auto x:mat)
    {
        for(auto y:x)
        {
            cout<<y<<" ";
        }
        cout<<endl;
    }
}

class segTree
{

public:
    vector<ll> seg;
    segTree(ll n)
    {
        seg.resize(4 * n + 1);
    }

    void build(ll idx, ll low, ll high, vector<ll> &arr)
    {
        if (low == high)
        {
            seg[idx] = arr[low];
            return;
        }

        ll mid = low + (high - low) / 2;

        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);

        seg[idx] = seg[2 * idx + 1]+ seg[2 * idx + 2];
    }

    ll query(ll idx, ll low, ll high, ll l, ll r)
    {
        // l r low high or low high l r

        if (r < low || high < l)
            return 0;

        // complete overlap- l low high r

        if (low >= l and high <= r)
        {
            return seg[idx];
        }

        // partial overlap
        ll mid = low + (high - low) / 2;

        ll left = query(2 * idx + 1, low, mid, l, r);
        ll right = query(2 * idx + 2, mid + 1, high, l, r);

        return left+right;
    }

    void update(ll idx, ll low, ll high, ll i, ll val)
    {
        if (low == high)
        {
            seg[idx] = val;
            return;
        }

        ll mid = low + (high - low) / 2;

        if (i <= mid)
            update(2 * idx + 1, low, mid, i, val);
        else
            update(2 * idx + 2, mid + 1, high, i, val);

        seg[idx] = seg[idx * 2 + 1]+ seg[idx * 2 + 2];
    }
};

bool static cmp(string&a,string&b)
{
    return a.size()<b.size();
}

class TrieNode
{
    public:
    TrieNode*one,*zero;
    TrieNode()
    {
        one=zero=NULL;
    }
};

class Trie
{  
   public:
       TrieNode *root;
       Trie()
       {
           root = new TrieNode();
   }

   void insert(ll x)
   {
       TrieNode*curr=root;
       for(ll i=31;i>=0;i--)
       {
           if((x>>i) & 1)
           {
               if(!curr->one)
               curr->one=new TrieNode();

               curr=curr->one;
           }
           else
           {
               if (!curr->zero)
                   curr->zero = new TrieNode();

               curr = curr->zero;
           }
       }
   }

   ll getMaxXorUtil(ll x)
   {
       TrieNode*curr=root;
       ll temp=0;
       for(ll i=31;i>=0;i--)
       {
          if((x>>i)&1)
          {
              if(curr->zero)
              {
                curr=curr->zero;
                temp+=pow(2,i);
              }
              else
              curr=curr->one;
          }
          else
          {
              if (curr->one)
              {
                  curr = curr->one;
                  temp += pow(2, i);
              }
              else
                  curr = curr->zero;
          }
       }
       return temp;
   }

   ll getMaxXor(vector<ll>&arr)
   {
       ll ans=0;
       for(auto x:arr)
       ans=max(ans,getMaxXorUtil(x));
       return ans;
   }
};

long long log(long long x)
{
    return 64 - __builtin_clzll(x) - 1;
}

long long GCD(long long x, long long y)
{
    if (y == 0)
        return x;
    return GCD(y, x % y);
}

ll isSubstring(string s1, string s2)
{
    // using find method to check if s1 is
    // a substring of s2
    if (s2.find(s1) != string::npos)
        return s2.find(s1);
    return -1;
}

ll isPrime(ll n)
{
    // Corner case
    if (n <= 1)
        return 1;

    // Check from 2 to square root of n
    for (ll i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return i;

    return 1;
}

class DSU
{
public:
    vector<ll> parent;
    vector<ll> sz,rank;

    DSU(ll n,vector<ll>&cost)
    {
        parent.resize(n);
        sz.resize(n);
        rank.resize(n);

        for (ll i = 0; i < n; i++)
        {
            parent[i] = i;
            sz[i] = 2*cost[i];
            rank[i]=cost[i];
        }
    }

    ll findParent(ll x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = findParent(parent[x]);
    }

    void Union(ll u, ll v)
    {
        u = findParent(u);
        v = findParent(v);

        if (u == v)
            return;

        if(rank[u]<=rank[v])
        {
            parent[v]=u;
            sz[u]+=sz[v];
        }
        else
        {
            parent[u]=v;
            sz[v]+=sz[u];
        }
    }
};

// for (int i = 1; i <= n; i++)
//     if (!vis[i])
//     {
//         int j = i;
//         while (!vis[j])
//             vis[j] = i, j = p[j];
//         int len = 0;
//         while (vis[j] == i)
//             vis[j] = -1, len++, j = p[j];
//         if (len != 0 && len != k)
//             tag = 0;
//     }

void work()
{
    ll n;
    cin>>n;
    
    vector<ll>arr(n);
    ll sum=0;
    for(auto &e:arr)
    {
        cin>>e;
        sum+=e;
    }

    if(n==1)
    {
        cout<<arr[0]<<endl;
        return;
    }

    
   
    ll ans=0,turn=0;
    for(ll i=0;i<n;i++)
    {   
        sum-=arr[i];

        if(arr[i]<0)
        {
            if(sum>0 and sum>=abs(arr[i]))
            {   
                turn++;
                ans+=turn*arr[i];
            }
            else
            {   
                if(turn==0)
                turn++;

                ans+=turn*arr[i];
            }
        }
        else
        {
            turn++;
            ans+=turn*arr[i];
        }
        
    }

    cout<<ans<<endl;
    
}  
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
       _test{
          work();
          //cout<<(work()?"YES":"NO")<<endl;
        //   cout<<work()<<"ans"<<endl;
          
        }
    
}
