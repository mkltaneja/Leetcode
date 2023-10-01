
// APPROACH 1 (Sliding window with infinite array) --> Time = O(target/sum(nums) + n), Space = O(n * n * (target / sum(nums)))

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

// APPROACH 2 (Sliding window with Single array) --> Time = O(2*n), Space = O(1) --> [OPTIMIZED]

class Solution {
public:
    int minSizeSubarray(vector<int>& nums, int target) 
    {
        int i = 0, j = 0, n = nums.size();
        long sum = 0;
        for(int x : nums)
            sum += x;
        
        int len = (target / sum) * n;
        target %= sum;
        if(target == 0) return len;
        
        int rsum = 0, rlen = n+1;
        while(j < n)
        {
            rsum += nums[i];
            while(j < n && rsum > target)
                rsum -= nums[j++];
            
            if(rsum == target)
                rlen = min(rlen, i >= j? i-j+1 : n + i-j+1);
            i = (i + 1) % n;
        }
        
        return rlen == n+1? -1 : len + rlen;
    }
};
