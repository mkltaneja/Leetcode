
// DAY 1 (338. Counting Bits)====================================================================================================

// METHOD 1 (By Dividing numbers into segments - 2-3, 4-7, 8-15...) --> time = O(n), space = O(n)

vector<int> countBits(int n) 
{
    vector<int> ans(n+1, 0);
    
    if(n == 0) return ans;
    
    ans[1] = 1;
    int start = 0, end = 0, itr = 0, time = 0;
    for(int x = 2; x <= n; x++)
    {
        if((x & (x - 1)) == 0)
        {
            start = x / 2;
            itr = start;
            end = x - 1;
            time = 0;
        }
        ans[x] = ans[itr++] + time;
        if(itr == end+1)
        {
            itr = start;
            time++;
        }
    }

    return ans;
}

// METHOD 2 (Using FACT - odd num has 1 bit more than its half, and even num has equal) --> time = O(n), space = O(n)

vector<int> countBits(int n) 
{
    vector<int> ans(n+1, 0);
    if(n == 0) return ans;
    
    ans[1] = 1;
    for(int x = 2; x <= n; x++)
        ans[x] += ans[x >> 1] + (x & 1);

    return ans;
}

// METHOD 3 (Using FACT - Every num (x) has 1 more bit than its (x & (x-1))) --> time = O(n), space = O(n)

vector<int> countBits(int n) 
{
    vector<int> ans(n+1, 0);
    if(n == 0) return ans;
    
    ans[1] = 1;
    for(int x = 2; x <= n; x++)
        ans[x] += ans[x & (x-1)] + 1;

    return ans;
}

// DAY 2 (2707. Extra Characters in a String)====================================================================================

class Trie
{
    public:
    vector<Trie*> child;
    bool wordEnd;
    Trie()
    {
        this->child.assign(26, nullptr);
        this->wordEnd = false;
    }

    void insert(Trie* t, string &s)
    {
        Trie* tmp = t;
        for(char c : s)
        {
            if(!tmp->child[c-'a'])
                tmp->child[c-'a'] = new Trie();
            tmp = tmp->child[c-'a'];
        }
        tmp->wordEnd = true;
    }
};
Trie* root = new Trie();

// map<pair<int,Trie*>, int> dp;
// Note: We don't need above kind of DP, as we don't have dependency over Trie node for every index, as we are just calling for the root at every call
int dfs(int i, Trie* itr, string &s, vector<int> &dp)
{
    if(i == s.size()) return 0;
    if(dp[i] != -1) return dp[i];

    int ans = dfs(i+1, root, s, dp) + 1;
    for(int j = i; j < s.size(); j++)
    {
        Trie* nxt = itr->child[s[j]-'a'];
        if(!nxt) break;

        if(nxt->wordEnd)
            ans = min(ans, dfs(j+1, root, s, dp));
        itr = nxt;
    }
    return dp[i] = ans;
}

int minExtraChar(string s, vector<string>& dictionary) 
{
    for(string &word : dictionary)
        root->insert(root, word);
    
    vector<int> dp(s.size(), -1);
    return dfs(0, root, s, dp);
}

// DAY 3 (62. Unique Paths)============================================================================

int uniquePaths(int m, int n) 
{
    vector<vector<int>> dp(m, vector<int> (n, 0));
    dp[m-1][n-1] = 1;
    for(int i = m-1; i >= 0; i--)
    {
        for(int j = n-1; j >= 0; j--)
        {
            int rightWays = j == n-1? 0 : dp[i][j+1];
            int downWays = i == m-1? 0 : dp[i+1][j];
            dp[i][j] += rightWays + downWays;
        }
    }

    return dp[0][0];
}
