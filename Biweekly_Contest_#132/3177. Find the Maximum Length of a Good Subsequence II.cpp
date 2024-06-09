
// APPROACH 1 (Normal tabularized)

// Time Complexity = O(n*k)
// Space Complexity = O(n*k + k)

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) 
    {
        int n = nums.size();
        vector<vector<int>> dp(n+1, vector<int>(k+1, 0));
        vector<int> maxLen(k+1, 0);
        unordered_map<int, int> lastOcc;
        
        for(int i = 0; i < n; i++)
        {
            int lo = lastOcc[nums[i]];
            for(int j = k; j >= 0; j--)
            {
                dp[i+1][j] = max(dp[i+1][j], dp[lo][j] + 1);
                if(j) dp[i+1][j] = max(dp[i+1][j], maxLen[j-1] + 1);
                
                maxLen[j] = max(maxLen[j], dp[i+1][j]);
            }
            lastOcc[nums[i]] = i+1;
        }
        return maxLen[k];
    }
};


// APPROACH 2 (Better Tabularized)

// Time Complexity = <=O(n*k)
// Space Complexity = <=O(n*k + k)

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) 
    {
        int n = nums.size();
        unordered_map<int, int> mp;
        for(int &num : nums)
        {
            if(!mp.count(num))
                mp[num] = mp.size();
            num = mp[num];
        }
        int m = mp.size();
        vector<vector<int>> dp(m, vector<int>(k+1, 0));
        vector<int> maxLen(k+1, 0);
        
        for(int num : nums)
        {
            for(int j = k; j >= 0; j--)
            {
                dp[num][j]++;
                if(j) dp[num][j] = max(dp[num][j], maxLen[j-1] + 1);
                
                maxLen[j] = max(maxLen[j], dp[num][j]);
            }
        }
        return maxLen[k];
    }
};
