class Solution {
public:
    #define ll long long
    vector<ll> ftree;
    
    ll get(int x)
    {
        ll ans = 0;
        while(x > 0)
        {
            ans += ftree[x];
            x -= (x & -x);
        }
        return ans;
    }
    
    void insert(int x)
    {
        while(x < 1e5)
        {
            ftree[x]++;
            x += (x & -x);
        }
    }
    
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) 
    {
        int y = 2e4+1;
        ftree.resize(1e5);
        int n = nums1.size();
        ll ans = 0;
        for(int i = 0; i < n; i++)
        {
            int x = nums1[i] - nums2[i];
            x += y;
            ll g = get(x + diff);
            ans += g;
            insert(x);
        }
        
        return ans;
    }
};
