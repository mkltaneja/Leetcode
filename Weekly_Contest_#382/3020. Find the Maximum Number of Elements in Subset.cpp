
// Time Complexity = O(< n * n) || O(n * loga(loga(n))) [a = average value in array]
// Space Complexity = O(n)

class Solution {
public:
    
    #define ll long long
    
    int maximumLength(vector<int>& nums) 
    {
        unordered_map<ll,int> mp;
        int ans = 0;
        for(ll x : nums)
            mp[x]++;
        
        for(auto p : mp)
        {
            ll x = p.first;
            int i = 0;
            if(x == 1) 
            {
                ans = max(ans, mp[1] - (mp[1] & 1 ^ 1));
                continue;
            }
            while(mp.count(x) && mp[x] > 1)
                x *= x, i++;
            if(mp.count(x))
                ans = max(ans, 2*i+1);
            else ans = max(ans, 2*i-1);
        }
        
        return ans;
    }
};
