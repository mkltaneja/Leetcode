class Solution {
public:
    
    int MOD = 1e9 + 7;
    #define ll long long
    
    int prod(ll a, ll b, ll x)
    {
        return ((a ^ x) % MOD) * ((b ^ x) % MOD) % MOD;
    }
    
    int maximumXorProduct(long long a, long long b, int n) 
    {
        ll x = 0;
        for(int i = n-1; i >= 0; i--)
        {
            if((b ^ x) > (a ^ x)) swap(a, b);
            
            int on1 = (a >> i) & 1;
            int on2 = (b >> i) & 1;
            if(on1 && on2) continue;
            if(!on1 && !on2)
                x |= (1ll << i);
            else if(!on2) 
                x |= (1ll << i);
        }
        
        return prod(a, b, x);
    }
};
