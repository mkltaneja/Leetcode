
// Time Complexity = O(n^2 + q)
// Space Complexity = O(n^2 + q)

class Solution {
public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries)
    {
        int n = nums.size();
        vector<vector<int>> dp(n+1, vector<int>(n, 0));
        vector<vector<int>> totXor(n+1, vector<int>(n, 0));
        vector<int> ans;
        
        for(int len = 1; len <= n; len++)
        {
            for(int i = 0; i <= n - len; i++)
            {
                if(len == 1)
                {
                    totXor[len][i] = nums[i];
                    dp[len][i] = nums[i];
                    continue;
                }
                totXor[len][i] = totXor[len-1][i] ^ totXor[len-1][i+1];
                dp[len][i] = max({totXor[len][i], dp[len-1][i], dp[len-1][i+1]});
            }
        }
        
        for(vector<int> &query : queries)
        {
            int l = query[0];
            int r = query[1];
            int len = r - l + 1;
            
            ans.push_back(dp[len][l]);
        }
        
        return ans;
    }
};
