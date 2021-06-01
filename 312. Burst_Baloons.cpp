
// Method 1 (MEMOIZED)
// TLE

// int maxcoins(int l, int r, vector<int> nums, vector<vector<int>> &dp)
// {
//     if(dp[l][r] != -1)
//         return dp[l][r];
//     int ans = 0;
//     for(int i = l+1; i < r; i++)
//     {
//         int coins = maxcoins(l,i,nums,dp)+
//                     (nums[l]*nums[i]*nums[r])+
//                     maxcoins(i,r,nums,dp);
//         // cout<<coins<<endl;
//         ans = max(ans, coins);
//     }
//     return dp[l][r] = ans;
// }

// METHOD 2 (Tabulated)
// AC

int maxcoins(vector<int> nums, vector<vector<int>> &dp)
{
    for (int gap = 1; gap < nums.size(); gap++)
    {
        for (int l = 0, r = gap; r < nums.size(); l++, r++)
        {
            int ans = 0;
            for (int i = l + 1; i < r; i++)
            {
                int coins = dp[l][i] + nums[l] * nums[i] * nums[r] + dp[i][r];
                ans = max(ans, coins);
            }
            dp[l][r] = ans;
        }
    }
    return dp[0][nums.size() - 1];
}

int maxCoins(vector<int> &nums)
{
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    int n = nums.size();
    cout << n << endl;
    vector<vector<int>> dp(n, vector<int>(n, -1));
    // return maxcoins(0, nums.size()-1, nums, dp);
    return maxcoins(nums, dp);
}