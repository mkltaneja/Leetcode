
// Time Complexity = O(n^3 * k)
// Space Complexity = O(n^3 * k)

class Solution {
public:
    
    int k, n;
    vector<int> nums;
    const int MOD = 1e9 + 7;
    
    int modAddition(int a, int b)
    {
        return (a % MOD + b % MOD) % MOD;
    }
    
    int getSumOfPower(int mini, int minj, int i, int len, vector<vector<vector<vector<int>>>> &cache)
    {
        if(i == n)
            return (len == k) * (nums[minj] - nums[mini]);
        if(cache[mini][minj][i][len] != -1)
            return cache[mini][minj][i][len];
        
        int ans = 0;
        if(len < k)
        {
            for(int j = i+1; j < n; j++)
            {
                if(mini == minj || nums[j] - nums[i] < nums[minj] - nums[mini])
                    ans = modAddition(ans, getSumOfPower(i, j, j, len+1, cache));
                else ans = modAddition(ans, getSumOfPower(mini, minj, j, len+1, cache));
            }
        }
        ans = modAddition(ans, getSumOfPower(mini, minj, n, len, cache));
        
        return cache[mini][minj][i][len] = ans;
    }
    
    int sumOfPowers(vector<int>& nums, int k) 
    {
        sort(nums.begin(), nums.end());
        this->k = k;
        n = nums.size();
        this->nums = nums;
        int ans = 0;
        vector<vector<vector<vector<int>>>> cache(n, vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(k+1, -1))));
        for(int i = 0; i < n; i++)
            ans = modAddition(ans, getSumOfPower(0, 0, i, 1, cache));
        return ans;
    }
};
