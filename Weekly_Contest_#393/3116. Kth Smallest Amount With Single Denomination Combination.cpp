
// Time Complexity = O(2^n * n * logn * logn)
// Space Complexity = O(1)

class Solution {
public:
    
    #define ll long long
    
    ll checkIdx(ll num, vector<int> &coins)
    {
        int size = coins.size();
        ll ansIdx = 0;
        for(int mask = 1; mask < (1 << size); mask++)
        {
            int bits = 0;
            ll currIdx = 0, lcm = 1;
            for(int idx = 0; idx < size; idx++)
            {
                if(mask & (1 << idx))
                {
                    bits++;
                    lcm = (lcm / __gcd(lcm, static_cast<ll>(coins[idx]))) * coins[idx];
                    if(lcm > num)
                        break;
                }
            }
            currIdx = num / lcm;
            if(bits & 1)
                ansIdx += currIdx;
            else ansIdx -= currIdx;
        }
        return ansIdx;
    }
    
    long long findKthSmallest(vector<int>& coins, int k) 
    {
        ll lo = 1, hi = 1e15;
        while(lo < hi)
        {
            ll mid = lo + ((hi - lo) >> 1);
            ll idx = checkIdx(mid, coins);
            if(idx < k)
                lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }
};
