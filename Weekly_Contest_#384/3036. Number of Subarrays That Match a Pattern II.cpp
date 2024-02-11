
// Time Complexity = O(3 * (n + m + 1))
// Space Complexity = O(n + m + 1)

class Solution {
public:
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) 
    {
        int n = nums.size(), m = pattern.size();
        vector<int> kmp = pattern;
        kmp.emplace_back(-2);
        for(int i = 0; i < n-1; i++)
        {
            int d = nums[i+1] - nums[i];
            kmp.push_back(d > 0? 1 : (d < 0? -1 : 0));
        }
        
        vector<int> lps(kmp.size(), 0);
        int len = 0;
        for(int i = 1; i < kmp.size(); )
        {
            if(kmp[i] == kmp[len])
                lps[i++] = ++len;
            else
            {
                if(len) len = lps[len-1];
                else i++;
            }
        }
        
        int ans = 0;
        for(int i = 1; i < kmp.size(); i++)
            if(lps[i] == m)
                ans++;
        
        return ans;
    }
};
