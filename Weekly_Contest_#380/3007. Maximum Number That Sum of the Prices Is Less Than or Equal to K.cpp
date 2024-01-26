
// Time Complexity = O(log2(INF) ^ 3)
// Space Complexity = O(60)

class Solution {
public:
    
    #define ll long long
    #define INF 1e16
    
    ll check(ll num, int x)
    {
        ll totalBits = 0;
        vector<ll> bitCount(60, 0);
        int orig = num;
        while(num >= 1)
        {
            ll lastPowerOf2 = log2(num);
            ll lastPowerOf2Num = (1ll << lastPowerOf2);
            ll cnt1 = num - lastPowerOf2Num + 1;
            ll cnt2 = lastPowerOf2Num / 2;
            
            bitCount[lastPowerOf2] += cnt1;
            for(int idx = lastPowerOf2-1; idx >= 0; idx--)
                bitCount[idx] += cnt2;
            
            num -= lastPowerOf2Num;
        }
        
        for(int idx = 1; idx <= 60; idx++)
            if(idx % x == 0)
                totalBits += bitCount[idx-1];
        
        return totalBits;
    }
    
    long long findMaximumNumber(long long k, int x) 
    {
        ll lo = 1, hi = INF;
        ll ans = -1;
        while(lo <= hi)
        {
            ll mid = lo + (hi - lo) / 2;
            ll cnt = check(mid, x);
            if(cnt <= k)
            {
                lo = mid + 1;
                ans = mid;
            }
            else hi = mid - 1;
        }
        
        return ans;
    }
};
