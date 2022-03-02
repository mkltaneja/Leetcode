// DAY 1 (338. Counting Bits)=========================================================================================================================

// APPROACH 1 (Naive)
vector<int> countBits(int n) 
{
    vector<int> ans(n+1);
    for(int i = 0; i <= n; i++)
    {
        int x = i, cnt = 0;
        while(x)
        {
            x &= x-1;
            cnt++;
        }
        ans[i] = cnt;
    }
    return ans;
}

// APPROACH 2 (DP)

vector<int> countBits(int n) 
{
    vector<int> ans(n+1);
    for(int i = 1; i <= n; i++)
        ans[i] = ans[i & (i-1)] + 1;
    return ans;
}

// DAY 2 (392. Is Subsequence)=========================================================================================================================

bool isSubsequence(string s, string t) 
{
    int i = 0, j = 0, n = s.size(), m = t.size();
    while(i < n && j < m)
    {
        if(s[i] == t[j]) i++;
        j++;
    }
    return i == n;
}
