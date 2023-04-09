class Solution {
public:
    
    #define ll long long
    #define f first
    #define s second
    vector<long long> distance(vector<int>& nums) 
    {
        int n = nums.size();
        unordered_map<ll,vector<ll>> mp, mp2;
        for(int i = 0; i < n; i++)
            mp[nums[i]].push_back(i);
        
        for(auto &p : mp)
        {
            vector<ll> tmp = p.s;
            for(int i = 0; i < tmp.size(); i++)
                tmp[i] += i? tmp[i-1] : 0;
            mp2[p.f] = tmp;
        }
        
        vector<ll> ans(n);
        for(ll i = 0; i < n; i++)
        {
            ll lb = lower_bound(mp[nums[i]].begin(), mp[nums[i]].end(), i) - mp[nums[i]].begin();
            ll s1 = mp2[nums[i]][lb];
            ll s2 = mp2[nums[i]].back() - mp2[nums[i]][lb];
            
            ll x = (i*(lb+1) - s1);
            ll y = (s2 - i*(mp2[nums[i]].size() - lb - 1));
            ll curr = x + y;
            ans[i] = curr;
        }
        
        return ans;
    }
};
