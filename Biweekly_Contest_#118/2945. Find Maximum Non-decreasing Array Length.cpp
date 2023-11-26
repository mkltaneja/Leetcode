class Solution {
public:
    
    #define ll long long
    int findMaximumLength(vector<int>& nums) 
    {
        int n = nums.size();
        vector<ll> prevIdx(n+1, 0), dp(n+1, 0), pSum(n+1, 0);
        for(int i = 1; i <= n; i++)
            pSum[i] = pSum[i-1] + nums[i-1];
        
        for(int i = 1; i <= n; i++)
        {
            prevIdx[i] = max(prevIdx[i-1], prevIdx[i]);
            dp[i] = dp[prevIdx[i]] + 1;
            int lo = i, hi = n, nextIdx = 0;
            
            while(lo <= hi)
            {
                int mid = (lo + ((hi - lo) >> 1));
                if(pSum[mid] - pSum[i] >= pSum[i] - pSum[prevIdx[i]])
                {
                    nextIdx = mid;
                    hi = mid - 1;
                }
                else lo = mid + 1;
            }
            
            prevIdx[nextIdx] = i;
        }
        
        return dp[n];
    }
};
