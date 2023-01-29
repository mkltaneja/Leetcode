class Solution {
public:
    
    #define ll long long
    int MX = 1e4+4;
    
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
            while(x < sz)
            {
                ft[x]++;
                x += x & -x;
            }
        }

        ll get(int x)
        {
            ll ans = 0;
            while(x)
            {
                ans += ft[x];
                x -= x & -x;
            }

            return ans;
        }
    };
    
    long long countQuadruplets(vector<int>& nums) 
    {
        int n = nums.size();
        ll ans = 0;
        
        ftree f1(MX);
        for(int j = 0; j < n; j++)
        {
            ftree f2(MX);
            for(int k = n-1; k > j; k--)
            {
                if(nums[k] > nums[j]) continue;
                
                ll x = f1.get(nums[k]);
                ll y = (n - 1 - k) - f2.get(nums[j]);
                
                ans += x * y;
                
                f2.add(nums[k]);
            }
            f1.add(nums[j]);
        }
        
        return ans;
    }
};
