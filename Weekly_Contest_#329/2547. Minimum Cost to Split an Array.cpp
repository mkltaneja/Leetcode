class Solution {
public:
    int minCost(vector<int>& nums, int k) 
    {
        int n = nums.size();
        vector<int> cache(n+1,0);
        for(int i = n-1; i >= 0; i--)
        {
            vector<int> count(n);
            int extra = 0, currCost = INT_MAX;
            for(int j = i; j < n; j++)
            {
                extra += (++count[nums[j]] == 2)? count[nums[j]] : (count[nums[j]] > 2);
                currCost = min(currCost, cache[j+1] + extra + k);
            }
            cache[i] = currCost;
        }
        
        return cache[0];
    }
};
