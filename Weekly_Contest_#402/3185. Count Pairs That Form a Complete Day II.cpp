
// Time Complexity = O(n)
// Space Complexity = O(24)

class Solution {
public:
    
    #define ll long long
    long long countCompleteDayPairs(vector<int>& hours) 
    {
        unordered_map<ll, ll> mp;
        ll ans = 0;
        ll k = 24;
        for(ll x : hours)
        {
            ans += mp[(k - (x % k)) % k];
            mp[x % k]++;
        }
        return ans;
    }
};
