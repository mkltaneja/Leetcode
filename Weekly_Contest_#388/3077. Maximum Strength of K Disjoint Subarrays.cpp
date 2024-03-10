
// APPROACH 1 (Giving every choice and choosing Maximum)

// Time Complexity = O(n*k*n)
// Space Complexity = O(n*k)

class Solution {
public:
    
    #define ll long long
    
    ll dfs(int i, int turn, int k, vector<int> &nums, vector<vector<ll>> &dp)
    {
        if(k == 0) return 0;
        if(dp[i][k] != LLONG_MAX)
            return dp[i][k];
        
        ll sum = 0, currMax = LLONG_MIN;
        
        ll sign = (turn & 1)? 1 : -1;
        ll msum = LLONG_MIN;
        for(int j = i; j <= nums.size() - k; j++)
        {
            sum += (ll)nums[j];
            ll ret = dfs(j+1, (turn ^ 1), k-1, nums, dp);
            if(ret == LLONG_MIN) continue;
            if(turn)
                currMax = max(currMax, ret + (sum * k));
            else
                currMax = max(currMax, ret - (sum * k));
            
            if(sum * sign < 0)
                sum = 0;
        }
        return dp[i][k] = currMax;
    }
    
    long long maximumStrength(vector<int>& nums, int k) 
    {
        vector<ll> psum(nums.size(), 0);
        for(int i = 0; i < nums.size(); i++)
            psum[i] = nums[i] + (i? psum[i-1] : 0);
        vector<vector<ll>> dp(nums.size(), vector<ll>(k+1, LLONG_MAX));
        return dfs(0, 1, k, nums, dp);
    }
};


// APPROACH 2 (Choosing Greedily for every value of k (1 to k) among the current subarray maximum and the previous subarray maximum)

// Time Complexity = O(n*k)
// Space Complexity = O(n)

class Solution {
public:
    
    #define ll long long
    const int MIN_INF = LLONG_MIN;
    long long maximumStrength(vector<int>& nums, int k) 
    {
        int size = nums.size();
        vector<ll> cache(size, MIN_INF);
        for(int kDash = 1; kDash <= k; kDash++)
        {
            vector<ll> prevCache = cache;
            int sign = (kDash & 1)? 1 : -1;
            for(int idx = kDash-1; idx < size; idx++)
            {
                ll currSubPrev = idx? prevCache[idx-1] : MIN_INF;
                ll prevSubPrev = idx? cache[idx-1] : MIN_INF;
                
                cache[idx] = max(currSubPrev, prevSubPrev) + 1ll * sign * (k - kDash + 1) * nums[idx];
            }
        }
        
        return *max_element(cache.begin() + k - 1, cache.end());
    }
};
