
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    
    #define ll long long
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) 
    {
        int size = nums.size();
        int xored = 0;
        ll minInc = INT_MAX, totSum = 0;
        
        for(ll num : nums)
        {
            ll numXor = num ^ k;
            if(num > numXor)
                totSum += num;
            else totSum += numXor, xored++;
            
            minInc = min(minInc, abs(num - numXor));
        }
        
        return totSum - ((xored & 1)? minInc : 0);
    }
};
