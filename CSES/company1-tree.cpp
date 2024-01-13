#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
int up[200005][19];

void preprocess(int node, int p)
{
    up[node][0] = p;

    for (int i = 1; i < 19; i++)
    {
        if (up[node][i - 1] != -1)
            up[node][i] = up[up[node][i - 1]][i - 1];
        else
            break;
    }

    for (int v : adj[node])
        preprocess(v, node);
}
int getkthAncestor(int node, int k)
{
    if (k == 0)
        return node;

    if (k == 1)
        return up[node][0];

    int last = -1;
    for (int i = 18; i >= 0; i--)
    {
        int bit = (1 << i) & k;

        if (bit)
            last = i;
    }

    if (last == -1 || up[node][last] == -1)
        return -1;

    return getkthAncestor(up[node][last], k ^ (1 << last));
}

int main()
{
    int n, q, u, node, k;
    cin >> n >> q;
    vector<int> ans;
    adj.resize(n + 1);
    memset(up, -1, sizeof(up));
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u;
        adj[u].push_back(i + 2);
    }

    preprocess(1, -1);

    for (int i = 0; i < q; i++)
    {
        cin >> node >> k;
        ans.push_back(getkthAncestor(node, k));
    }

    for (auto x : ans)
        cout << x << endl;
}