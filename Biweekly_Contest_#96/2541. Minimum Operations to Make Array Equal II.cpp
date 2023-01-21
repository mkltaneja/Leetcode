class Solution {
public:
    
    #define ll long long
    long long minOperations(vector<int>& nums1, vector<int>& nums2, int k) 
    {
        ll req = 0, rel = 0;
        for(int i = 0; i < nums2.size(); i++)
        {
            if(abs(nums1[i] - nums2[i]) && !k) return -1;
            if(k && (abs(nums1[i] - nums2[i]) % k)) return -1;
            if(nums1[i] < nums2[i])
                req += nums2[i] - nums1[i];
            else 
                rel += nums1[i] - nums2[i];
        }
        
        return req == rel? (!req? 0 : req/k) : -1;
    }
};
