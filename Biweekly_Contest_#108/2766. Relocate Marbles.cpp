class Solution {
public:
    vector<int> relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo) 
    {
        unordered_set<int> st;
        for(int i = 0; i < nums.size(); i++)
            st.insert(nums[i]);
        for(int i = 0; i < moveFrom.size(); i++)
        {
            st.erase(moveFrom[i]);
            st.insert(moveTo[i]);
        }
        
        vector<int> ans;
        for(int x : st)
            ans.push_back(x);
        
        sort(ans.begin(), ans.end());
        
        return ans;
    }
};
