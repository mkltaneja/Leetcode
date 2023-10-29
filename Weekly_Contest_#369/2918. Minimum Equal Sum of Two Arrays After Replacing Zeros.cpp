class Solution {
public:
    
    #define ll long long
    long long minSum(vector<int>& nums1, vector<int>& nums2) 
    {
        ll sum1 = 0, sum2 = 0, z1 = 0, z2 = 0;
        for(ll x : nums1)
        {
            sum1 += x;
            z1 += x == 0;
        }
        for(ll x : nums2)
        {
            sum2 += x;
            z2 += x == 0;
        }
        
        if(z1 == 0 && z2 == 0)
            return sum1 == sum2? sum1 : -1;
        if(z1 == 0)
            return sum2 + z2 <= sum1? sum1 : -1;
        if(z2 == 0)
            return sum1 + z1 <= sum2? sum2 : -1;
        
        return max(sum1 + z1, sum2 + z2);
    }
};
