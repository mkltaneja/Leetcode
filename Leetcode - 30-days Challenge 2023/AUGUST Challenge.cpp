
// DAY 1 (77. Combinations)=================================================================================

vector<vector<int>> ans;
void dfs(int x, int n, int k, vector<int> &curr)
{
    if(curr.size() == k) 
    {
        ans.push_back(curr);
        return;
    }

    for(int y = x; y <= n; y++)
    {
        curr.push_back(y);
        dfs(y+1, n, k, curr);
        curr.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) 
{
    vector<int> curr;
    dfs(1, n, k, curr);
    return ans;
}

// DAY 2 (46. Permutations)======================================================================================

vector<vector<int>> ans;
void dfs(int i, vector<int> &nums)
{
    if(i == nums.size()-1)
    {
        ans.push_back(nums);
        return;
    }

    for(int j = i; j < nums.size(); j++)
    {
        swap(nums[i], nums[j]);
        dfs(i+1, nums);
        swap(nums[i], nums[j]);
    }
}

vector<vector<int>> permute(vector<int>& nums)
{
    dfs(0, nums);
    return ans;
}

// DAY 3 (17. Letter Combinations of a Phone Number)================================================================================================

vector<string> keys = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
vector<string> ans;

void dfs(int i, string &word, string &digits)
{
    if(i == digits.size())
    {
        if(!word.empty())
            ans.push_back(word);
        return;
    }

    for(char c : keys[digits[i]-'2'])
    {
        word += c;
        dfs(i+1, word, digits);
        word.pop_back();
    }
}

vector<string> letterCombinations(string digits) 
{
    string word = "";
    dfs(0, word, digits);
    return ans;
}

// DAY 4 (139. Word Break)===============================================================================================

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

    void insert(string &word, Trie* root)
    {
        Trie* curr = root;
        for(char c : word)
        {
            if(!curr->child[c-'a'])
                curr->child[c-'a'] = new Trie();
            curr = curr->child[c-'a'];
        }
        curr->wordEnd = true;
    }
};
Trie* root = new Trie();

bool canSegment(int i, Trie* itr, string &s, vector<int> &dp)
{
    if(i == s.size()) return true;
    if(dp[i] != -1) return dp[i];

    Trie* curr = itr;
    for(int j = i; j < s.size() && curr->child[s[j]-'a']; j++)
    {
        Trie* nxt = curr->child[s[j]-'a'];
        if(nxt->wordEnd)
            if(canSegment(j+1, root, s, dp))
                return dp[j] = 1;
        curr = nxt;
    }
    return dp[i] = 0;
}

bool wordBreak(string s, vector<string>& wordDict) 
{
    for(string &word : wordDict)
        root->insert(word, root);
    
    Trie* itr = root;
    vector<int> dp(s.size(), -1);
    return canSegment(0, itr, s, dp);
}

// DAY 5 (95. Unique Binary Search Trees II)==================================================================

vector<TreeNode*> dfs(int l, int r)
{
    if(l >= r)
    {
        if(l == r) 
            return {new TreeNode(l)};
        return {nullptr};
    }


    vector<TreeNode*> currAns;
    for(int x = l; x <= r; x++)
    {
        vector<TreeNode*> lans = dfs(l, x-1);
        vector<TreeNode*> rans = dfs(x+1, r);

        for(TreeNode* lTree : lans)
            for(TreeNode* rTree : rans)
                currAns.push_back(new TreeNode(x, lTree, rTree));
    }

    return currAns;
}

vector<TreeNode*> generateTrees(int n) 
{
    return dfs(1, n);
}

// DAY 6 (920. Number of Music Playlists)====================================================================================

#define ll long long
int mod = 1e9 + 7;
ll nn = 0, kk = 0;
ll totalPlaylists(ll i, ll j, vector<vector<ll>> &dp)
{
    if(i == 0 && j == 0) return 1ll;
    if(i == 0 || j == 0) return 0ll;
    if(dp[i][j] != -1) return dp[i][j];

    ll uniqueSong = (totalPlaylists(i-1, j-1, dp) % mod
                     * (nn - (i - 1)) % mod) % mod;
    ll existingSong = i > kk? ((totalPlaylists(i, j-1, dp) % mod
                     * (i - kk) % mod) % mod) : 0ll;

    return dp[i][j] = (uniqueSong % mod + existingSong % mod) % mod;
}

int numMusicPlaylists(int n, int goal, int k) 
{
    nn = n, kk = k;
    vector<vector<ll>> dp(n+1, vector<ll>(goal+1, -1));
    return totalPlaylists(n, goal, dp);
}

// DAY 7 (74. Search a 2D Matrix)=============================================================================================

bool searchMatrix(vector<vector<int>>& matrix, int target) 
{
    int n = matrix.size(), m = matrix[0].size();
    int lo = 0, hi = n*m-1;
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        int r = mid / m;
        int c = mid % m;
        if(matrix[r][c] == target)
            return true;
        if(matrix[r][c] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return false;
}
