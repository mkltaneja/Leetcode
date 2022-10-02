// DAY 1 (91. Decode Ways)=======================================================================================

int numDecodings(string s) 
{
    int n = s.size();
    vector<int> dp(n+2,0);
    dp[n] = 1;
    for(int i = n-1; i >= 0; i--)
    {
        if(s[i] == '0') continue;
        dp[i] = dp[i+1] + (((s[i]-'0')*10 + (s[i+1]-'0') <= 26)? dp[i+2] : 0);
    }
    return dp[0];
}

// DAY 2 (1155. Number of Dice Rolls With Target Sum)====================================================================

#define ll long long
int mod = 1e9 + 7;
int dfs(ll n, ll k, ll tar, vector<vector<ll>> &dp)
{
    if(tar == 0) return 0;
    if(n == 1) return tar && tar <= k;
    if(dp[n][tar] != -1) return dp[n][tar] % mod;

    ll ans = 0;
    for(ll i = 1; i <= k; i++)
        if(i <= tar)
            ans = (ans % mod + dfs(n-1, k, tar-i, dp) % mod) % mod;

    return dp[n][tar] = ans % mod;
}

int numRollsToTarget(int n, int k, int target) 
{
    vector<vector<ll>> dp(n+1, vector<ll>(target+1, -1));
    return dfs(n, k, target, dp) % mod;
}
