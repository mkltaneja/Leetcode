class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) 
    {
        int n = nums.size();
        vector<int> cnt(105);
        vector<int> ans;
        for(int i = 0; i < n; i++)
        {
            cnt[nums[i]+50]++;
            if(i >= k) cnt[nums[i - k]+50]--;
            
            int xx = x, val = 0;
            if(i >= k-1)
            {
                for(int j = 0; j < 105 && xx > 0; j++)
                {
                    xx -= cnt[j];
                    if(xx <= 0)
                        val = j - 50;
                }
                if(val > 0)
                    ans.push_back(0);
                else
                    ans.push_back(val);
            }
        }
        return ans;
    }
};
