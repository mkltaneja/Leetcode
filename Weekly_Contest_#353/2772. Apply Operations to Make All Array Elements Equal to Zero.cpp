class Solution {
public:
    bool checkArray(vector<int>& nums, int k) 
    {
        int n = nums.size();
        vector<int> altDiff(n+1);
        altDiff[0] = nums[0];
        for(int i = 1; i < n; i++)
            altDiff[i] = nums[i] - nums[i-1];
        
        for(int i = 0; i <= n-k; i++)
        {
            if(altDiff[i] < 0) return false;
            
            if(altDiff[i] && i+k <= n)
            {
                altDiff[i + k] += altDiff[i];
                altDiff[i] = 0;
            }
        }
        for(int i = n-k+1; i < n; i++)
            if(altDiff[i])
                return false;
        
        return true;
    }
};
