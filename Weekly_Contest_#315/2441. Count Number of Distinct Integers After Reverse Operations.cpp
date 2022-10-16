class Solution {
public:
    int countDistinctIntegers(vector<int>& nums) 
    {
        unordered_set<int> st;
        for(int x : nums)
        {
            int y = 0;
            st.insert(x);
            while(x)
            {
                y = y*10 + x%10;
                x /= 10;
            }
            st.insert(y);
        }
        
        return st.size();
    }
};
