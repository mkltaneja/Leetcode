class Solution {
public:
    int findMaxK(vector<int>& nums) 
    {
        unordered_set<int> st;
        for(int x : nums)
            st.insert(x);
        int ans = -1;
        for(int x : nums)
            if(x > 0 && st.count(-x))
                ans = max(ans, x);
        return ans;
    }
};
