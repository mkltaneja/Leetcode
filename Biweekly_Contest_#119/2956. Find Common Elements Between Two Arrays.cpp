class Solution {
public:
    vector<int> findIntersectionValues(vector<int>& nums1, vector<int>& nums2) 
    {
        unordered_map<int,int> mp1, mp2;
        for(int x : nums1)
            mp1[x]++;
        for(int x : nums2)
            mp2[x]++;
        
        int c1 = 0, c2 = 0;
        for(int x : nums1)
            if(mp2[x])
                c1++;
        for(int x : nums2)
            if(mp1[x])
                c2++;
        
        return {c1, c2};
    }
};
