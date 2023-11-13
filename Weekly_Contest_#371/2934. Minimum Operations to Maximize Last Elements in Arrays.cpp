class Solution {
public:
    
    int minOperations(vector<int>& nums1, vector<int>& nums2) 
    {
        int n = nums1.size();
        int max = -1, maxi = -1;
        for(int i = 0; i < n; i++)
        {
            if(nums1[i] >= max)
                max = nums1[i], maxi = i;
            if(nums2[i] >= max)
                max = nums2[i], maxi = i;
        }
        if(maxi != n-1) return -1;
        
        int max2 = min(nums1[n-1], nums2[n-1]);
        int ops1 = 0, ops2 = 0;
        for(int i = 0; i < n; i++)
        {
            if(nums1[i] > max2 && nums2[i] > max2)
                return -1;
            ops1 += nums1[i] > max2;
            ops2 += nums2[i] > max2;
        }
        
        return min(ops1, ops2);
    }
};
