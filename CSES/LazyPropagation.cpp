#include <bits/stdc++.h>
using namespace std;

class segTree
{

public:
    vector<int> seg;
    vector<int> lazy;
    segTree(int n)
    {
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1, 0);
    }

    void build(int idx, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            seg[idx] = arr[low];
            return;
        }

        int mid = low + (high - low) / 2;

        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);

        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    int query(int idx, int low, int high, int l, int r)
    {
        // l r low high or low high l r

        if (r < low || high < l)
            return INT_MAX;

        // complete overlap- l low high r

        if (low >= l and high <= r)
        {
            return seg[idx];
        }

        // partial overlap
        int mid = low + (high - low) / 2;

        int left = query(2 * idx + 1, low, mid, l, r);
        int right = query(2 * idx + 2, mid + 1, high, l, r);

        return min(left, right);
    }

    void update(int idx, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[idx] = val;
            return;
        }

        int mid = low + (high - low) / 2;

        if (i <= mid)
            update(2 * idx + 1, low, mid, i, val);
        else
            update(2 * idx + 2, mid + 1, high, i, val);

        seg[idx] = min(seg[idx * 2 + 1], seg[idx * 2 + 2]);
    }

    void updateRange(int idx, int low, int high, int l, int r, int val)
    {
        if (lazy[idx] != 0)
        {
            seg[idx] += (high - low + 1) * lazy[idx];

            if (low != high)
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }

            lazy[idx] = 0;
        }

        if (high < l || low > r)
            return;

        if (l <= low and r >= high)
        {
            seg[idx] += (high - low + 1) * val;

            if (low != high)
            {
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }

            return;
        }

        int mid = (low + high) / 2;

        updateRange(2 * idx + 1, low, mid, l, r, val);
        updateRange(2 * idx + 2, mid + 1, high, l, r, val);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    int queryLazy(int idx, int low, int high, int l, int r)
    {
        if (lazy[idx] != 0)
        {
            seg[idx] += (high - low + 1) * lazy[idx];

            if (low != high)
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }

            lazy[idx] = 0;
        }

        if (high < l || low > r)
            return 0;

        if (low >= l and high <= r)
            return seg[idx];

        int mid = (low + high) / 2;

        return queryLazy(2 * idx + 1, low, mid, l, r) + queryLazy(2 * idx + 2, mid + 1, high, l, r);
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    segTree sg(n);

    sg.build(0, 0, n - 1, arr);

    sg.updateRange(0, 0, n - 1, 1, 3, 5);
    cout << endl
         << sg.queryLazy(0, 0, n - 1, 0, 4);

    // while (q--)
    // {
    //     int type, l, r, i, val;
    //     cin >> type;

    //     if (type == 1)
    //     {
    //         cin >> l >> r;
    //         cout << sg.query(0, 0, n - 1, l, r);
    //     }
    //     else
    //     {
    //         cin >> i >> val;
    //         sg.update(0, 0, n - 1, i, val);
    //     }
    // }

    return 0;
}
