
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

// APPROACH 2 (Finding uniques and commons mathematically)

// Time = O(n)
// Space = O(n)

class Solution {
public:

    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) 
    {
        unordered_set<int> st1, st2;
        int n = nums1.size(), m = (n >> 1);
        for(int x : nums1)
            st1.insert(x);
        for(int x : nums2)
            st2.insert(x);
        int uni1 = 0, uni2 = 0;
        for(int x : st1)
            if(!st2.count(x))
                uni1++;
        for(int x : st2)
            if(!st1.count(x))
                uni2++;
        int common = st1.size() - uni1;
        uni1 = min(uni1, m);
        uni2 = min(uni2, m);
        
        int ans = uni1 + uni2 + min(n - (uni1 + uni2), common);
        
        return ans;
    }
};
