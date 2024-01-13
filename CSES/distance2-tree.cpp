#include <bits/stdc++.h>
using namespace std;
#define ll long long
vector<vector<int>> adj;
ll subtreeans[200005];
ll subtreesize[200005];
ll ans[200005];

void rerooting(int u, int p, ll x, int &n) // x==partial answer
{
    ans[u] = subtreeans[u] + x + (n - subtreesize[u]);

    for (int v : adj[u])
    {
        if (v != p)
            rerooting(v, u, ans[u] - subtreeans[v] - subtreesize[v], n);
    }
}
void preprocess(int u, int p)
{
    ll nodesCount = 1;
    ll subans = 0;

    for (int v : adj[u])
    {
        if (v == p)
            continue;

        preprocess(v, u);
        nodesCount += subtreesize[v];
        subans += subtreeans[v] + subtreesize[v];
    }

    subtreeans[u] = subans;
    subtreesize[u] = nodesCount;
}

int main()
{
    int u, v, n;
    cin >> n;
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    preprocess(1, -1);
    rerooting(1, -1, 0, n);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";

    return 0;
}