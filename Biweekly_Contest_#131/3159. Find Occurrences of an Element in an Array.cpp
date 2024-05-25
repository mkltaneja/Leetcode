
// Time Complexity = O(n + q)
// Space Complexity = O(n + q)

class Solution {
public:
    vector<int> occurrencesOfElement(vector<int>& nums, vector<int>& queries, int x) 
    {
        int n = nums.size();
        vector<int> ans;
        vector<int> occ;
        for(int i = 0; i < n; i++)
            if(nums[i] == x)
                occ.push_back(i);
        for(int q : queries)
        {
            if(q <= occ.size())
                ans.push_back(occ[q-1]);
            else ans.push_back(-1);
        }
        return ans;
    }
};
