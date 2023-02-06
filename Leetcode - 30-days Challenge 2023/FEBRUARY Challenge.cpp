// DAY 1 (1071. Greatest Common Divisor of Strings)=============================================================================

// APPROACH 1 (Finding prime factors)

int gcd(int x, int y)
{
    while(x)
    {
        int z = y % x;
        y = x;
        x = z;
    }
    return y;
}

string gcdOfStrings(string str1, string str2) 
{
    vector<int> pFacs;
    int n = str1.size(), m = str2.size();
    int x = gcd(n, m);
    for(int i = 1; i*i <= x; i++)
    {
        if(x % i) continue;
        pFacs.push_back(i);
        if(i != x/i)
            pFacs.push_back(x/i);
    }

    sort(pFacs.rbegin(), pFacs.rend());
    for(int pf : pFacs)
    {
        bool isAns = true;
        string check = str1.substr(0,pf);
        for(int i = 0; i < n && isAns; i += pf)
        {
            if(str1.substr(i,pf) != check)
                isAns = false;
        }
        for(int i = 0; i < m && isAns; i += pf)
        {
            if(str2.substr(i,pf) != check)
                isAns = false;
        }

        if(isAns) return check;
    }

    return "";
}

// APPROACH 2 (GCD Approach)

string gcdOfStrings(string str1, string str2) 
{
    if(str1.size() < str2.size())
        return gcdOfStrings(str2, str1);
    if(str2.empty()) return str1;
    return str1.substr(0,str2.size()) == str2? gcdOfStrings(str1.substr(str2.size()), str2) : "";
}

// DAY 4 (567. Permutation in String)=================================================================================

bool checkInclusion(string s1, string s2) 
{
    int n = s1.size(), m = s2.size();
    vector<int> mp1(26,0);
    unordered_map<char,int> mp2;
    for(char &c : s1)
        mp1[c-'a']++;

    for(int i = 0; i < 26; i++)
        if(mp1[i])
            mp2[char(i+'a')] = -mp1[i];

    for(int i = 0; i < m; i++)
    {
        if(++mp2[s2[i]] == 0)
            mp2.erase(s2[i]);
        if(i >= n)
            if(--mp2[s2[i - n]] == 0)
                mp2.erase(s2[i - n]);
        if(mp2.empty()) return true;
    }

    return false;
}

// DAY 5 (438. Find All Anagrams in a String)===============================================================================

vector<int> findAnagrams(string s, string p) 
{
    int n = s.size(), m = p.size();
    unordered_map<char,int> mp;
    for(char c : p)
        mp[c]--;

    vector<int> ans;
    for(int i = 0; i < n; i++)
    {
        if(++mp[s[i]] == 0)
            mp.erase(s[i]);
        if(i >= m)
            if(--mp[s[i-m]] == 0)
                mp.erase(s[i-m]);
        if(mp.size() == 0)
            ans.push_back(i-m+1);
    }

    return ans;
}

// DAY 6 (1470. Shuffle the Array)===============================================================================

vector<int> shuffle(vector<int>& nums, int n) 
{
    vector<int> ans(2*n);
    for(int i = 0; i < n; i++)
    {
        ans[2*i] = nums[i];
        ans[2*i+1] = nums[n+i];
    }

    return ans;
}
