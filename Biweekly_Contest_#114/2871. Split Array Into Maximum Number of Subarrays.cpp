class Solution {
public:
    
    int offset = (1 << 30) - 1;
    int maxSubarrays(vector<int>& nums) 
    {
        int minScore = INT_MAX;
        for(int x : nums)
            minScore &= x;
        
        if(minScore) return 1;
        
        int score = offset;
        int ans = 0;
        for(int x : nums)
        {
            score &= x;
            if(score == minScore) 
            {
                ans++;
                score = offset;
            }
        }
        
        return ans;
    }
};
