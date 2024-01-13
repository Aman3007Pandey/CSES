#include <bits/stdc++.h>
using namespace std;


#define pii pair<ll,ll>
#define pb push_back
#define ll long long
#define _test  ll _TEST; cin>>_TEST; while(_TEST--)


void printString(vector<string>&v)
{
    for(auto x:v)
    cout<<x<<endl;
}

void printArray(vector<ll> &v)
{
    for (auto x : v)
    cout << x << endl;
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

        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    ll query(ll idx, ll low, ll high, ll l, ll r)
    {
        // l r low high or low high l r

        if (r < low || high < l)
            return LONG_MAX;

        // complete overlap- l low high r

        if (low >= l and high <= r)
        {
            return seg[idx];
        }

        // partial overlap
        ll mid = low + (high - low) / 2;

        ll left = query(2 * idx + 1, low, mid, l, r);
        ll right = query(2 * idx + 2, mid + 1, high, l, r);

        return min(left, right);
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

        seg[idx] = min(seg[idx * 2 + 1], seg[idx * 2 + 2]);
    }
};

int main()
{   


    _test
    {
        ll n,q;
        cin>>n>>q;

        vector<vector<ll>>adj(n);
        for(ll i=0;i<n-1;i++)
        {
            ll u,v;
            cin>>u>>v;
            u--,v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        vector<ll>p(n);
        for(auto &e:p)
        cin>>e;

        vector<ll>st(n),en(n),order;

        ll t=0;

        function<void(ll,ll)>dfs=[&](ll u,ll p)
        {
            st[u]=en[u]=t++;
            order.pb(u);
            for(auto v:adj[u])
            {
                if(v!=p)
                {
                    dfs(v,u);
                    en[u]=max(en[u],en[v]);
                }
            }
        }; 
         
        dfs(0,-1);

        vector<vector<array<ll,3>>>que(n); 
        for(ll i=0;i<q;i++)
        {
             ll l,r,x;
            cin>>l>>r>>x;
            l--,r--,x--;
            que[x].pb({l,r,i});
        }

        vector<string>ans(q);
        vector<ll>val(n),pos(n);
        for(ll i=0;i<n;i++)
        {
            p[i]--;
            val[i]=st[p[i]];
            pos[p[i]]=i;

        }

        segTree sg(n);

        sg.build(0,0,n-1,val);

        for(ll i=0;i<n;i++)
        {
            ll node=order[i];

            for(auto & [l,r,i]:que[node])
            {
                 ll mn =sg.query(0,0,n-1,l,r);

                 ans[i]=mn<=en[node]?"YES":"NO";
            }

            sg.update(0,0,n-1,pos[node],1e9);
        }

        printString(ans);
    }
    
    return 0;
}