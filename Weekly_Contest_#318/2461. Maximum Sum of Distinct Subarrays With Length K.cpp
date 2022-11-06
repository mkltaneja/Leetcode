class Solution {
public:
    
    #define ll long long
    
    long long maximumSubarraySum(vector<int>& nums, int k) 
    {
        int n = nums.size();
        ll ans = 0;
        vector<ll> ps(n);
        for(int i = 0; i < n; i++)
            ps[i] = nums[i] + (i? ps[i-1] : 0);
        
        unordered_set<int> st;
        
        int j = 0;
        for(int i = 0; i < n; i++)
        {
            while(st.count(nums[i]) || (i-j+1 > k))
                st.erase(nums[j++]);
            st.insert(nums[i]);
            
            if(i-j+1 == k) 
                ans = max(ans, (ps[i] - (j? ps[j-1] : 0)));
        }
        
        return ans;
    }
};
