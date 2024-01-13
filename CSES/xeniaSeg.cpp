
#include <bits/stdc++.h>
using namespace std;

void buildSeg(int ind, int low, int high, int arr[], int seg[], bool isOr)
{
    // if overlapped completey
    if (low == high)
    {
        seg[ind] = arr[low];
        return;
    }

    int mid = (low + high) / 2;
    // if no overlap
    buildSeg(2 * ind + 1, low, mid, arr, seg, !isOr);
    buildSeg(2 * ind + 2, mid + 1, high, arr, seg, !isOr);
    if (isOr)
        seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
    else
        seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
}

void update(int ind, int low, int high, int seg[], int i, int val, bool isOr)
{
    if ((low == high))
    {
        seg[ind] = val;
        return;
    }

    int mid = (low + high) / 2;
    if (i <= mid)
        update(2 * ind + 1, low, mid, seg, i, val, !isOr);
    else
        update(2 * ind + 2, mid + 1, high, seg, i, val, !isOr);
    if (isOr)
        seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
    else
        seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
}

int main()
{
    int n, q;
    cin >> n >> q;
    int el = 1 << n;
    int arr[el] = {0};
    for (int i = 0; i < el; i++)
        cin >> arr[i];
    int seg[4 * el] = {0};
    if (n % 2 == 0)
        buildSeg(0, 0, el - 1, arr, seg, 0);
    else
        buildSeg(0, 0, el - 1, arr, seg, 1);
    while (q--)
    {

        int i, val;
        cin >> i >> val;
        i--;
        if (n % 2 == 0)
            update(0, 0, el - 1, seg, i, val, 0);
        else
            update(0, 0, el - 1, seg, i, val, 1);
        cout << seg[0] << endl;
    }

    return 0;
}