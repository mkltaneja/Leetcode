
class Solution {
public:
    
    #define ll long long
    
    vector<ll> palindromeNumbers(int limit) 
    {
        vector<ll> pals;

        // For single-digit numbers
        for (int i = 1; i < 10 && i <= limit; ++i)
            pals.emplace_back(i);

        // For even-length palindromes
        for (int i = 1; i <= 100000 && i <= limit; ++i) 
        {
            string s = to_string(i);
            string rev = s;
            reverse(rev.begin(), rev.end());
            ll palindrome = stoll(s + rev);
            if (palindrome <= limit)
                pals.emplace_back(palindrome);
            else
                break;
        }

        // For odd-length palindromes
        for (int i = 1; i <= 100000 && i <= limit; ++i) 
        {
            string s = to_string(i);
            string rev = s;
            rev.pop_back();
            reverse(rev.begin(), rev.end());
            ll palindrome = stoll(s + rev);
            if (palindrome <= limit)
                pals.emplace_back(palindrome);
            else
                break;
        }

        return pals;
    }
    
    long long minimumCost(vector<int>& nums) 
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        ll mx = nums[n-1];
        vector<ll> psum(n);
        for(int i = 0; i < n; i++)
            psum[i] = (ll)nums[i] + (i? psum[i-1] : 0);
        vector<ll> pals = palindromeNumbers(mx*10);
        
        ll minCost = LLONG_MAX;
        for(ll x : pals)
        {
            int lb = lower_bound(nums.begin(), nums.end(), x) - nums.begin();
            ll lsum = lb? psum[lb-1] : 0;
            ll rsum = psum[n-1] - (lb? psum[lb-1] : 0);
            ll lc = lb;
            ll rc = n - lb;
            
            ll cost = (x * lc - lsum) + (rsum - x * rc);
            minCost = min(minCost, cost);
        }
        
        return minCost;
    }
};
