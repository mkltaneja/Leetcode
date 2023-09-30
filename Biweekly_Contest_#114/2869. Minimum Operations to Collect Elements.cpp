class Solution {
public:
    int minOperations(vector<int>& nums, int k) 
    {
        unordered_set<int> st;
        int x = 0;
        for(int i = nums.size()-1; i >= 0 && st.size() < k; i--, x++)
            if(nums[i] <= k)
                st.insert(nums[i]);
        return x;
    }
};
