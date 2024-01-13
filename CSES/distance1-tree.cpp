#include <bits/stdc++.h>
using namespace std;

int child[200005];     // name of the child through which we get max depth
int firstans[200005];  // depth max
int secondans[200005]; // second max deth
vector<vector<int>> adj;
void pre_process(int u, int p)
{
    firstans[u] = 0;
    secondans[u] = 0;

    for (int v : adj[u])
    {
        if (v == p)
            continue;

        pre_process(v, u);
        if (firstans[u] < firstans[v] + 1)
        {
            secondans[u] = firstans[u];
            firstans[u] = firstans[v] + 1;
            child[u] = v;
        }
        else if (secondans[u] < firstans[v] + 1)
            secondans[u] = firstans[v] + 1;
    }
}

void rerooting(int u, int p) // v is the root
{
    for (int v : adj[u])
    {
        if (v == p)
            continue;

        if (child[u] == v) // best we can do if take second max
        {
            if (firstans[v] < secondans[u] + 1)
            {
                secondans[v] = firstans[v];
                firstans[v] = secondans[u] + 1;

                child[v] = u;
            }
            else if (secondans[v] < secondans[u] + 1)
                secondans[v] = secondans[u] + 1;
        }
        else
        {
            secondans[v] = firstans[v];
            firstans[v] = firstans[u] + 1;
            child[v] = u;
        }

        rerooting(v, u);
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, u, v;
    cin >> n;
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    pre_process(1, -1);
    rerooting(1, -1);
    for (int i = 1; i <= n; i++)
        cout << firstans[i] << " ";
}
