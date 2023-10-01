class Solution {
public:
    int minSizeSubarray(vector<int>& nums, int target) 
    {
        long i = 0, j = 0, ci = 0, cj = 0, n = nums.size();
        set<vector<long>> vis;
        long sum = 0, ans = INT_MAX;
        while(true)
        {
            if(vis.count({i, j, ci - cj}))
                return ans == INT_MAX? -1 : ans;
            sum += nums[i];
            while(sum > target)
            {
                sum -= nums[j];
                vis.insert({i, j, ci - cj});
                j = (j+1) % n;
                if(j == 0) cj++;
            }
            if(sum == target) ans = min(ans, (ci - cj)*n + (i-j+1));
            
            i = (i+1) % n;
            if(i == 0) ci++;
        }
        
        return ans == INT_MAX? -1 : ans;
    }
};
