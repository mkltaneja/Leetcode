class Solution {
public:
    int minimizeMax(vector<int>& nums, int p) 
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        int lo = 0, hi = nums[n-1] - nums[0];
        while(lo < hi)
        {
            int mid = lo + ((hi - lo)>>1);
            int tot = 0;
            
            for(int i = 0; i < n-1; i++)
            {
                if(nums[i+1] - nums[i] <= mid) tot++, i++;
            }
            
            if(tot >= p) hi = mid;
            else lo = mid + 1;
        }
        
        return lo;
    }
};
