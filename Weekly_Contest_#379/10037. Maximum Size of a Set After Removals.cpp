
// APPROACH 1 (Using set for common elements)

// Time = O(n)
// Space = O(n)

class Solution {
public:

    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) 
    {
        int c1 = nums1.size()/2;
        int c2 = nums2.size()/2;
        unordered_set<int> st1, st2;
        unordered_set<int> st;
        int ans = 0;
        for(int x : nums1)
            st1.insert(x);
        for(int x : nums2)
            st2.insert(x);
        
        for(int x : st1)
        {
            if(!st2.count(x))
            {
                c1--;
                st.insert(x);
            }
            if(c1 == 0)
                break;
        }
        for(int x : st2)
        {
            if(!st1.count(x))
            {
                c2--;
                st.insert(x);
            }
            if(c2 == 0)
                break;
        }
        
        if(c1)
        {
            for(int x : st1)
            {
                if(st2.count(x) && !st.count(x))
                {
                    c1--;
                    st.insert(x);
                }
                if(c1 == 0)
                    break;
            }
        }
        if(c2)
        {
            for(int x : st2)
            {
                if(st1.count(x) && !st.count(x))
                {
                    c2--;
                    st.insert(x);
                }
                if(c2 == 0)
                    break;
            }
        }
        
        return st.size();
    }
};
