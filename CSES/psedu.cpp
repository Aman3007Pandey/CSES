#include <bits/stdc++.h>
using namespace std;

void genNum(vector<int> &magicNum)
{
    for (int i = 1; i < 1e6; ++i)
    {
        int p = i;
        while (p)
        {
            int last_digit = p % 10;
            if (last_digit == 4 || last_digit == 5)
            {
                p /= 10;
            }
            else
            {
                break;
            }
        }
        if (p == 0)
        {
            magicNum.push_back(i);
        }
    }
}

int coinChange(vector<int> &nums, int amt)
{
    if (amt == 0)
        return 0;
    if (amt < 0)
        return INT_MAX;
    int mini = INT_MAX;
    for (int i = 0; i < nums.size(); ++i)
    {
        int ans = coinChange(nums, amt - nums[i]);
        if (ans != INT_MAX)
        {
            mini = min(ans + 1, mini);
        }
    }
    return mini;
}
int coinChangeMemo(vector<int> &nums, int amt, vector<int> &dp)
{
    if (amt == 0)
        return 0;
    if (amt < 0)
        return INT_MAX;
    if (dp[amt] != -1)
        return dp[amt];
    int mini = INT_MAX;
    for (int i = 0; i < nums.size(); ++i)
    {
        int ans = coinChangeMemo(nums, amt - nums[i], dp);
        if (ans != INT_MAX)
        {
            mini = min(ans + 1, mini);
        }
    }
    dp[amt] = mini;
    return dp[amt];
}
int main()
{
   int t;
   cin>>t;

   while(t--)
   {
        vector<int> magicNum;
        genNum(magicNum);

        int amt;
        cin >> amt;
        vector<int> dp(amt + 1, -1);
        int ans = coinChangeMemo(magicNum, amt, dp);
        cout << ans;
   }
}