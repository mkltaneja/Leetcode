
// APPROACH 1 (Constructing every possible pallindromic number) -> Time = O(n + 1e5), Space = O(n + 1e5)

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


// APPROACH 2 -> (Greedy) --> Time = O(nlogn + n), Space = O(n)

class Solution {
public:
    
    #define ll long long
    
    string findSmallerPal(string s)
    {
        string t = s;
        int n = s.size();
        for(int i = 0, j = n-1; i < j; t[j--] = t[i++]);
        
        if(t <= s) return t;
        
        for(int i = ((n - 1) >> 1); i >= 0; i--)
        {
            if(t[i] == '0') continue;
            if(i == 0 && t[i] == '1') continue;
            
            t[n-i-1] = --t[i];
            while(++i <= n-i-1)
                t[n-i-1] = t[i] = '9';
            return t;
        }
        
        return string(n-1, '9');
    }
    
    string findGreaterPal(string s)
    {
        string t = s;
        int n = s.size();
        for(int i = 0, j = n-1; i < j; t[j--] = t[i++]);
        
        if(t >= s) return t;
        
        for(int i = ((n - 1) >> 1); i >= 0; i--)
        {
            if(t[i] == '9') continue;
            
            t[n-i-1] = ++t[i];
            while(++i <= n-i-1)
                t[n-i-1] = t[i] = '0';
            return t;
        }
        
        string ret = string(n+1, '0');
        ret[0] = ret[n] = '1';
        return ret;
    }
    
    ll findCost(ll pal, vector<int> &nums)
    {
        ll cost = 0;
        for(int num : nums)
            cost += abs(pal - num);
        return cost;
    }
    
    long long minimumCost(vector<int>& nums) 
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        string sPal = findSmallerPal(to_string(nums[n >> 1]));
        string gPal = findGreaterPal(to_string(nums[n >> 1]));
        ll smallerCost = findCost(stoll(sPal), nums);
        ll greaterCost = findCost(stoll(gPal), nums);
        
        return min(smallerCost, greaterCost);
    }
};
