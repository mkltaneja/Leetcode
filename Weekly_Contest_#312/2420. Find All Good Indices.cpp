class Solution {
public:
    vector<int> goodIndices(vector<int>& nums, int k) 
    {
        int n = nums.size();
        vector<int> inc(n+1,0), inc2(n+1,0);
        for(int i = 0; i < n; i++)
            inc[i] = i? (nums[i] <= nums[i-1]? inc[i-1] + 1 : 1) : 1;
        for(int i = n-1; i >= 0; i--)
            inc2[i] = i < n-1? (nums[i] <= nums[i+1]? inc2[i+1] + 1 : 1) : 1;
        
        vector<int> ans;
        for(int i = k; i < n-k; i++)
            if(inc[i-1] >= k && inc2[i+1] >= k)
                ans.push_back(i);
        
        return ans;
    }
};
