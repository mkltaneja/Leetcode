
// Time Complexity = O(n*logn + n)
// Space Complexity = O(n)

class Solution {
public:
    
    #define ll long long
    long long maximumTotalDamage(vector<int>& power) 
    {
        int n = power.size();
        sort(power.begin(), power.end());
        vector<int> uniPower;
        vector<ll> dp;
        ll ans = 0;
        int lasti = 0;
        
        for(int i = 0; i < n; )
        {
            int j = i;
            while(j < n && power[j] == power[i]) j++;
            ll count = j - i;
            
            while(lasti < uniPower.size() && power[i] - uniPower[lasti] > 2)
                lasti++;
            uniPower.push_back(power[i]);
            
            ll prevMaxExc = dp.empty()? 0 : dp.back();
            ll prevMaxInc = (lasti? dp[lasti-1] : 0) + (count * power[i]);
            dp.push_back(max(prevMaxExc, prevMaxInc));
            
            i = j;
        }
        return dp.back();
    }
};
