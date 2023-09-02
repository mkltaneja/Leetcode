class Solution {
public:
    
    #define ll long long
    long long maxSum(vector<int>& nums, int m, int k) 
    {
        int n = nums.size();
        unordered_map<int,int> mp;
        ll sum = 0, ans = 0;
        for(int i = 0; i < n; i++)
        {
            mp[nums[i]]++;
            sum += (ll)nums[i];
            if(i >= k)
            {
                if(--mp[nums[i-k]] == 0)
                    mp.erase(nums[i-k]);
                sum -= (ll)nums[i-k];
            }
            if(i >= k-1 && mp.size() >= m)
                ans = max(ans, sum);
        }
        
        return ans;
    }
};
