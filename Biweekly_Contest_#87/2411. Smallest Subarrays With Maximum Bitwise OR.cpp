class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) 
    {
        vector<vector<int>> on(32);
        for(int i = 0; i < nums.size(); i++)
        {
            int x = nums[i];
            int j = 0;
            while(x)
            {
                if(x&1) on[j].push_back(i);
                x >>= 1;
                j++;
            }
        }
        
        vector<int> ans(nums.size(), -1);
        for(int i = 0; i < nums.size(); i++)
        {
            int curr = 1;
            for(int j = 0; j < 32; j++)
            {
                int lb = lower_bound(on[j].begin(), on[j].end(), i) - on[j].begin();
                lb = lb == on[j].size()? i-1 : on[j][lb];
                curr = max(curr, lb-i+1);
            }
            ans[i] = curr;
        }
        
        return ans;
    }
};
