#include<bits/stdc++.h>
using namespace std;

#define ll long long

class DSU
{
    public:

    vector<ll>parent;
    vector<ll>sz;

    DSU(ll n)
    {
        parent.resize(n);
        sz.resize(n);

        for(ll i=0;i<n;i++)
        {
            parent[i]=i;
            sz[i]=0;
        }
    }

    ll findParent(ll x)
    {
        if(parent[x]==x)
        return x;

        return parent[x]=findParent(parent[x]);
    }

    void Union(ll u,ll v)
    {
        u=findParent(u);
        v=findParent(v);

        if(u==v)
        return;

        sz[u]+=sz[v];
        parent[v]=u;
    }
};