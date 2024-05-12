
// Time Complexity = O(q * (log(INF)*60 + 60) + 60)
// Space Complexity = O(q + 60)

class Solution {
public:
    
    #define ll long long
    #define INF 1e16
    
    int multMod(ll a, ll b, ll m)
    {
        return ((a % m) * (b % m)) % m;
    }
    
    int powMod(ll a, ll b, int m)
    {
        int ans = 1;
        while(b)
        {
            if(b & 1ll)
                ans = multMod(ans, a, m);
            a = multMod(a, a, m);
            b >>= 1ll;
        }
        return ans % m;
    }
    
    ll findSum(vector<ll> &bits)
    {
        ll sum = 0;
        for(ll bit : bits)
            sum += bit;
        return sum;
    }
    
    vector<ll> countTotalBits(ll x)
    {
        x++;
        vector<ll> ans(60, 0);
        for(int i = 0; i < 60; i++)
        {
            ll num = (1ll << i);
            ll numGroupSize = num * 2;
            ll wholeGroups = x / numGroupSize;
            ll numGroupOcc = wholeGroups * num;
            ll numRemOcc = (x % numGroupSize) - num;
            if(numRemOcc < 0)
                numRemOcc = 0;
            
            ans[i] = numGroupOcc + numRemOcc;
        }
        return ans;
    }
    
    ll findNumOcc(ll x)
    {
        ll lo = 0, hi = INF;
        ll ans = 0;
        while(lo <= hi)
        {
            ll mid = lo + ((hi - lo) >> 1);
            vector<ll> totalBits = countTotalBits(mid);
            ll bitSum = findSum(totalBits);
            if(bitSum < x)
                lo = mid + 1;
            else
            {
                ans = mid;
                hi = mid - 1;
            }
        }
        return ans;
    }
    
    vector<ll> findNumOccWithLeftover(ll x)
    {
        ll num_ub = findNumOcc(x);
        vector<ll> prevBitsCount = countTotalBits(num_ub - 1);
        ll leftover = x - findSum(prevBitsCount);
        
        for(int i = 0; i < 60; i++)
        {
            if(leftover == 0)
                break;
            if(num_ub & (1ll << i))
            {
                prevBitsCount[i]++;
                leftover--;
            }
        }
        return prevBitsCount;
    }
    
    vector<int> findProductsOfElements(vector<vector<long long>>& queries) 
    {
        vector<int> ans;
        for(vector<ll> &q : queries)
        {
            ll l = q[0], r = q[1], m = q[2];
            vector<ll> lbits = findNumOccWithLeftover(l);
            vector<ll> rbits = findNumOccWithLeftover(r+1);
            int prod = 1;
            for(int i = 0; i < 60; i++)
            {
                rbits[i] -= lbits[i];
                prod = multMod(prod, powMod((1ll << i), rbits[i], m), m);
            }
            ans.push_back(prod);
        }
        return ans;
    }
};
