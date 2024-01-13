#include <bits/stdc++.h>
using namespace std;

#define pll pair<long, long>
#define pii pair<ll, ll>
#define pb push_back
#define ll long long
#define all(arr) arr.begin(), arr.end()
#define _test     \
    ll _TEST;     \
    cin >> _TEST; \
    while (_TEST--)

class segTree
{

public:
    vector<ll> seg;
    vector<ll> lazy;
    segTree(ll n)
    {
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1, 0);
    }

    void build(ll idx, ll low, ll high, vector<ll> &arr)
    {
        if (low == high)
        {
            seg[idx] =arr[low];
            return;
        }

        ll mid = low + (high - low) / 2;

        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);

        seg[idx] = seg[2 * idx + 1]^seg[2 * idx + 2];
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

        return left^right;
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

    void updateRange(ll idx, ll low, ll high, ll l, ll r, ll val)
    {
        if (lazy[idx] != 0)
        {
            seg[idx] += (high - low + 1) * lazy[idx];
            seg[idx]%=26;

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

        ll mid = (low + high) / 2;

        updateRange(2 * idx + 1, low, mid, l, r, val);
        updateRange(2 * idx + 2, mid + 1, high, l, r, val);

        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }

    ll queryLazy(ll idx, ll low, ll high, ll l, ll r)
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

        ll mid = (low + high) / 2;

        return queryLazy(2 * idx + 1, low, mid, l, r) + queryLazy(2 * idx + 2, mid + 1, high, l, r);
    }
};


void work()
{
    ll n;
    cin>>n; 
    
    vector<ll>arr(n);
    for(auto & e:arr)
    cin>>e;

    string s;
    cin>>s;

    segTree sg(n);
    sg.build(0, 0, n - 1, arr);

    ll one=0,z=0;
    for(ll i=0;i<n;i++)
    {
         if(s[i]=='0')
         z^=arr[i];
         else
         one^=arr[i];
    }

    ll q; cin>>q;
    while(q--)
    {
        ll type; cin>>type;
        if(type==1)
        {
            ll l,r;
            cin>>l>>r;
            l--,r--;

            ll u=sg.query(0,0,n-1,l,r);
            one^=u;
            z^=u;
        }
        else
        {
            ll g;
            cin>>g;
            if(g)
            cout<<one<<" ";
            else
            cout<<z<<" ";
        }
    }

}
int main()
{
       _test{
          work();
       }
}    