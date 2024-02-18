
// APPROACH 1 (KMP) [JUGAAD]

// Time Complexity = O(n*m*m)
// Space Complexity = O(26*n)

class Solution {
public:
    
    #define ll long long
    
    vector<int> findLPS(string &s)
    {
        vector<int> lps(s.size(), 0);
        for(int i = 1, len = 0; i < s.size(); )
        {
            if(s[i] == s[len])
                lps[i++] = ++len;
            else
            {
                if(len) len = lps[len-1];
                else i++;
            }
        }
        return lps;
    }
    
    long long countPrefixSuffixPairs(vector<string>& words) 
    {
        int n = words.size();
        unordered_map<string, ll> mp;
        vector<unordered_map<ll, ll>> lens(26);
        ll ans = 0;

        for(string s : words)
        {
            vector<int> lps = findLPS(s);
            int len = lps.back();
            if(len == s.size()-1)
            {
                ans += mp[s]++;
                char c = s[0];
                int tmp = len;
                unordered_map<ll,ll> tmp2 = lens[c-'a'];
                while(tmp)
                {
                    if(tmp2.count(tmp))
                        ans += tmp2[tmp];
                    tmp--;
                }
                lens[c-'a'][len+1]++;
                continue;
            }
            while(len)
            {
                string p = s.substr(0, len);
                ans += mp.count(p)? mp[p] : 0;
                len = lps[len-1];
            }
            ans += mp.count(s)? mp[s] : 0;
            mp[s]++;
        }
        
        return ans;
    }
};


// APPROACH 2 (Rolling Hash) [OPTIMIZED]

// Time Complexity = O(n * m * log(n))
// Space Complexity = O(n)

class Solution {
public:
    
    #define ll long long
    const int MOD = 1e9 + 7;
    const int OFFSET = 26;
    
    int modMultiplication(ll x, ll y)
    {
        return ((x % MOD) * (y % MOD)) % MOD;
    }
    
    int modAddition(ll x, ll y)
    {
        return ((x % MOD) + (y % MOD)) % MOD;
    }
    
    long long countPrefixSuffixPairs(vector<string>& words) 
    {
        int n = words.size();
        map<pair<ll, ll>, ll> hashMap;
        ll ans = 0;
        for(string word : words)
        {
            ll hash1 = 0, hash2 = 0, m = word.size();
            for(int idx = 0; idx < m; idx++)
            {
                hash1 = modAddition(modMultiplication(hash1, OFFSET), (word[idx] - 'a' + 1));
                hash2 = modAddition(modMultiplication(hash2, OFFSET), (word[m - idx - 1] - 'a' + 1));
                
                ans += hashMap.count({hash1, hash2})? hashMap[{hash1, hash2}] : 0;
            }
            hashMap[{hash1, hash2}]++;
        }
        
        return ans;
    }
};
