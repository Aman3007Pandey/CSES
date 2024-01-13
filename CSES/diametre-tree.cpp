#include <bits/stdc++.h>
using namespace std;

int depth[200005];
int dp[20005];
int ans;

void solve(int u, vector<vector<int>> &adj, int p)
{
    int mx1 = 0, mx2 = 0, n = 0;

    for (int v : adj[u])
    {
        if (v == p)
            continue;

        n++;
        solve(v, adj, u);

        if (depth[v] > mx1)
        {
            mx2 = mx1;
            mx1 = depth[v];
        }
        else if (depth[v] > mx2)
            mx2 = depth[v];
    }

    if (n >= 2)
        ans = max(ans, mx1 + mx2 + 2);

    else if (n == 1)
        ans = max(ans, mx1 + 1);
}
int pre_process(int u, vector<vector<int>> &adj, int p)
{
    int mx = 0, leaf = 1;
    for (int v : adj[u])
    {
        if (v != p)
        {
            leaf = 0;
            mx = max(pre_process(v, adj, u), mx);
        }
    }

    if (leaf)
        return depth[u] = 0;

    return depth[u] = 1 + mx;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ans = 0;
    int n, u, v;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    while (--n)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    pre_process(1, adj, -1);
    solve(1, adj, -1);

    cout << ans;
}
