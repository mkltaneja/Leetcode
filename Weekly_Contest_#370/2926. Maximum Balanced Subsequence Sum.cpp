class Solution {
public:
    
    #define ll long long
    
    class fTree
    {
        public:
        vector<ll> f;
        int sz;
        fTree(int sz)
        {
            this->sz = sz;
            f.assign(sz, 0);
        }
        
        ll get(int x)
        {
            ll ans = LLONG_MIN;
            while(x)
            {
                ans = max(ans, this->f[x]);
                x -= x & -x;
            }
            
            return ans;
        }
        
        void set(int x, ll mx)
        {
            while(x < this->sz)
            {
                this->f[x] = max(this->f[x], mx);
                x += x & -x;
            }
        }
    };
    
    long long maxBalancedSubsequenceSum(vector<int>& nums) 
    {
        int n = nums.size();
        vector<pair<int,int>> pos(n);
        for(int i = 0; i < n; i++)
            pos[i] = {nums[i] - i, i};
        sort(pos.begin(), pos.end());
        
        fTree ft(n+1);
        ll ans = LLONG_MIN;
        for(int i = 0; i < n; i++)
        {
            ll mx = ft.get(pos[i].second+1) + pos[i].first + pos[i].second;
            ans = max(ans, mx);
            ft.set(pos[i].second+1, mx);
        }
        
        return ans;
    }
};
