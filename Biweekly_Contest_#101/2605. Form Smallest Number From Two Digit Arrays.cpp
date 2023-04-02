class Solution {
public:
    int minNumber(vector<int>& nums1, vector<int>& nums2) 
    {
        unordered_set<int> st;
        int mn1 = 9, mn2 = 9;
        for(int x : nums1)
        {
            st.insert(x);
            mn1 = min(mn1, x);
        }
        
        int ans = 100;
        for(int x : nums2)
        {
            if(st.count(x))
                ans = min(ans, x);
            mn2 = min(mn2, x);
        }
        if(mn1 > mn2) swap(mn1, mn2);
        ans = min(ans, mn1*10 + mn2);
        
        return ans;
    }
};
