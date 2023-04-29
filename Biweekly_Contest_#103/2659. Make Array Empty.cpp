class Solution {
public:
    
    #define ll long long 
    #define f first
    #define s second
    class ftree
    {
    public:
        vector<ll> ft;
        int sz;
        ftree(int sz)
        {
            this->sz = sz;
            this->ft.assign(sz, 0);
        }

        void add(int x)
        {
            while (x < sz)
            {
                ft[x]++;
                x += x & -x;
            }
        }

        ll get(int x)
        {
            ll ans = 0;
            while (x)
            {
                ans += ft[x];
                x -= x & -x;
            }

            return ans;
        }
    };

    long long countOperationsToEmptyArray(vector<int>& nums) 
    {
        int n = nums.size();
        ftree ft(1e5+5);
        vector<pair<int,int>> numsi(n);
        for(int i = 0; i < n; i++)
        {
            numsi[i] = {nums[i], i+1};
        }
        sort(numsi.begin(), numsi.end());
        
        int pi = 0;
        ll ans = 0;
        
        for(auto p : numsi)
        {
            if(p.s < pi)
            {
                ans += n - pi;
                ans -= ft.get(n) - ft.get(pi);
                pi = 0;
            }
            
            ans += p.s - pi;
            ans -= ft.get(p.s) - ft.get(pi);
            pi = p.s;
            
            ft.add(p.s);
        }
        
        return ans;
    }
};
