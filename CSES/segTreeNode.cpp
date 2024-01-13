#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int o, c, f;
    Node(int o, int c, int f)
    {
        this->o = o;
        this->c = c;
        this->f = f;
    }

    Node()
    {
        this->o = 0;
        this->c = 0;
        this->f = 0;
    }
};

Node mergeNodes(Node l, Node r)
{
    Node temp = Node(0, 0, 0);
    int mn = min(l.o, r.c);
    temp.f = l.f + r.f + mn;
    temp.o = l.o + r.o - mn;
    temp.c = l.c + r.c - mn;
    return temp;
}

void build(int idx, int low, int high, Node seg[], string &s)
{
    if (low == high)
    {
        Node temp = Node(0, 0, 0);

        if (s[low] == '(')
            temp.o = 1;
        else
            temp.c = 1;

        seg[idx] = temp;
        return;
    }

    int mid = low + (high - low) / 2;
    build(2 * idx + 1, low, mid, seg, s);
    build(2 * idx + 2, mid + 1, high, seg, s);

    seg[idx] = mergeNodes(seg[2 * idx + 1], seg[2 * idx + 2]);
}

Node query(int idx, int low, int high, int l, int r, Node seg[])
{
    if (r < low || high < l)
    {
        Node temp = Node(0, 0, 0);
        return temp;
    }

    if (low >= l and high <= r)
    {
        return seg[idx];
    }

    int mid = low + (high - low) / 2;
    Node left = query(2 * idx + 1, low, mid, l, r, seg);
    Node right = query(2 * idx + 2, mid + 1, high, l, r, seg);

    return mergeNodes(left, right);
}

int main()
{
    string s;
    cin >> s;
    int m;
    cin >> m;
    int n = s.size();

    Node seg[4 * n + 5];

    build(0, 0, n - 1, seg, s);
    while (m--)
    {
        int l, r;
        cin >> l >> r;

        cout << query(0, 0, n - 1, l - 1, r - 1, seg).f * 2 << endl;
    }

    return 0;
}