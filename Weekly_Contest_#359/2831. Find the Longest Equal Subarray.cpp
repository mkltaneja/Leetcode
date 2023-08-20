class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) 
    {
        int n = nums.size();
        vector<vector<int>> pos(n+1);
        for(int i = 0; i < n; i++)
            pos[nums[i]].push_back(i);
        
        int ans = 1;
        for(int x = 1; x <= n; x++)
        {
            int l = 0, r = 0;
            while(r < pos[x].size())
            {
                while((pos[x][r] - pos[x][l] + 1) - (r - l + 1) > k)
                    l++;
                ans = max(ans, r++ - l + 1);
            }
        }
        
        return ans;
    }
};
