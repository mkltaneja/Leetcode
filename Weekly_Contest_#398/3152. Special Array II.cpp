
// Time Complexity = O(n + q)
// Space Complexity = O(n + q)

class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) 
    {
        int n = nums.size();
        vector<int> pref(n,0);
        vector<bool> ans;
        for(int i = 1; i < n; i++)
        {
            int pol = ((nums[i]&1) == (nums[i-1]&1));
            pref[i] = pol + pref[i-1];
        }
        
        for(vector<int> &q : queries)
        {
            int l = q[0], r = q[1];
            if(pref[l] != pref[r])
                ans.push_back(false);
            else ans.push_back(true);
        }
        
        return ans;
    }
};
