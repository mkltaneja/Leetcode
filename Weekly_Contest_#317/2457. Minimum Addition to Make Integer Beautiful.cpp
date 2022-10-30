
// APPROACH 1 --> time = O(log10(n) * 2^log10(n))

class Solution {
public:
    #define ll long long
    
    int sod(long long x)
    {
        int sum = 0;
        while(x)
        {
            sum += x%10;
            x /= 10;
        }
        return sum;
    }
    
    long long makeIntegerBeautiful(long long n, int target) 
    {
        ll i = 1, p = 1;
        while(n/p)
        {
            if(i == 1)
            {
                if(sod(n) <= target) return 0;
                int k = (10 - (n%10)) % 10;
                if(sod(n + k) <= target) return k;
                i++;
            }
            for(ll j = (1 << i)-1; j >= (1 << (i-1))-1; j--)
            {
                ll tmp = j, nn = n, pp = 1, x = 0;
                while(tmp)
                {
                    ll ppp = 1;
                    while(tmp&1)
                    {
                        tmp >>= 1;
                        ppp *= 10;
                    }
                    x += ((ppp - (nn % ppp)) % ppp) * pp;
                    tmp >>= 1;
                    nn /= ppp*10;
                    pp *= 10;
                }
                
                if(sod(n+x) <= target) 
                    return x;
            }
            i++;
            p *= 10;
        }
        
        return -1;
    }
};

// APPROACH 2 -> time = (log10(n)^2) [OPTIMIZED]
class Solution {
public:
    #define ll long long
    
    int sod(long long x)
    {
        int sum = 0;
        while(x)
        {
            sum += x%10;
            x /= 10;
        }
        return sum;
    }
    
    long long makeIntegerBeautiful(long long n, int target) 
    {
        if(sod(n) <= target) return 0;
        ll p = 10, tmp = n;
        while(tmp)
        {
            ll k = p - n%p;
            if(sod(n + k) <= target) return k;
            p *= 10;
            tmp /= 10;
        }
        return -1;
    }
};
