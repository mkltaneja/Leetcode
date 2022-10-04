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

// DAY 3 (1578. Minimum Time to Make Rope Colorful)=============================================================================

int minCost(string colors, vector<int>& neededTime) 
{
    int n = colors.size();
    int ans = 0;
    for(int i = 0; i < n; )
    {
        int j = i+1;
        int mxt = neededTime[i];
        int sumt = neededTime[i];
        bool same = false;
        while(j < n && colors[j] == colors[i])
        {
            sumt += neededTime[j];
            mxt = max(mxt, neededTime[j++]);
            same = true;
        }
        ans += same? sumt - mxt : 0;
        i = j;
    }

    return ans;
}

// DAY 4 (112. Path Sum)===============================================================================================

bool hasPathSum(TreeNode* root, int targetSum) 
{
    if(!root) return false;
    if(!root->left && !root->right) 
        return (targetSum - root->val) == 0;
    return hasPathSum(root->left, targetSum - root->val) || 
            hasPathSum(root->right, targetSum - root->val);
}
