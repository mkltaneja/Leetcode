class Solution {
public:
    
    int mod = 1e9+7;
    #define ll long long
    
    int binpowmod(ll a, ll b)
    {
        ll ans = 1;
        while(b)
        {
            if(b&1)
                ans *= a;
            a *= a;
            b >>= 1;

            ans %= mod;
            a %= mod;
        }
        
        return ans;
    }

    
    int monkeyMove(int n) 
    {
        int pow = binpowmod(2, n);
        return (pow - 2 + mod) % mod;
    }
};
