class Solution {
public:
    
    #define ll long long
    #define f first
    #define s second
    long long minCost(vector<int>& nums, vector<int>& cost) 
    {
        int n = nums.size();
        ll sum1 = 0, sum2 = 0;
        ll p1 = 0, p2 = 0;
        ll prev = 0;
        vector<pair<ll,ll>> vp(n);
        for(int i = 0; i < n; i++)
        {
            vp[i] = {nums[i], cost[i]};
            sum2 += cost[i];
            p2 += (ll)nums[i] * cost[i];
        }
    
        sort(vp.begin(), vp.end());
        ll ans = LONG_LONG_MAX;
        for(int i = 0; i < n; i++)
        {
            ll d = vp[i].f - prev;
            prev = vp[i].f;

            p1 += sum1 * d;
            p2 -= sum2 * d;
            
            sum1 += vp[i].s;
            sum2 -= vp[i].s;
            
            ans = min(ans, p1 + p2);
        }
        return ans;
    }
};
