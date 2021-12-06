// DAY 1 (198. House Robber)======================================================================

int rob(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n);
    dp[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
        dp[i] = max(nums[i] + ((i + 2 < n) ? dp[i + 2] : 0), dp[i + 1]);

    return dp[0];
}

// DAY 3 (152. Maximum Product Subarray)================================================================================

int maxProduct(vector<int> &nums)
{
    int ans = nums[0];
    int maxp = nums[0], minp = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        int x = nums[i];
        if (x < 0)
            swap(minp, maxp);
        maxp = max(maxp * x, x);
        minp = min(minp * x, x);

        ans = max({ans, maxp, minp});
    }

    return ans;
}

// DAY 4 (1032. Stream of Characters)=======================================================================
class StreamChecker
{
public:
    class trie
    {
    public:
        vector<trie *> v;
        bool wordEnd;
        trie()
        {
            this->v.assign(26, nullptr);
            this->wordEnd = false;
        }

        void insert(string &s)
        {
            trie *curr = this;
            for (char c : s)
            {
                if (!curr->v[c - 'a'])
                    curr->v[c - 'a'] = new trie();
                curr = curr->v[c - 'a'];
            }
            curr->wordEnd = true;
        }
    };
    trie *root = new trie();

    StreamChecker(vector<string> &words)
    {
        for (string word : words)
        {
            reverse(word.begin(), word.end());
            root->insert(word);
        }
    }
    string s = "";
    bool query(char letter)
    {
        s += letter;
        trie *curr = root;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (!curr->v[s[i] - 'a'])
                return false;
            if (curr->v[s[i] - 'a']->wordEnd)
                return true;
            curr = curr->v[s[i] - 'a'];
        }
        return curr->wordEnd;
        return true;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */

//  DAY 5 (337. House Robber III)=========================================================================================

// APPROACH 1 (Without DP) --> O(4^h) [h = height of tree]      OR O(n^2)  [n = number of nodes]
// TLE

int rob(TreeNode *root)
{
    if (!root)
        return 0;

    int exc = rob(root->left) + rob(root->right);
    int inc = (root->left ? rob(root->left->left) + rob(root->left->right) : 0) +
              (root->right ? rob(root->right->left) + rob(root->right->right) : 0) + root->val;

    return max(inc, exc);
}

// APPROACH 2 (Using map as DP) --> >O(n)
// AC

unordered_map<TreeNode *, int> dp;
int rob(TreeNode *root)
{
    if (!root)
        return 0;

    if (dp.count(root))
        return dp[root];

    int exc = rob(root->left) + rob(root->right);
    int inc = (root->left ? rob(root->left->left) + rob(root->left->right) : 0) +
              (root->right ? rob(root->right->left) + rob(root->right->right) : 0) + root->val;

    return dp[root] = max(inc, exc);
}

// APPROACH 3 (Without DP -> inc, exc) --> O(n)
// AC

#define f first
#define s second
pair<int, int> dfs(TreeNode *node)
{
    if (!node)
        return {0, 0};

    auto lmax = dfs(node->left);
    auto rmax = dfs(node->right);

    int inc = lmax.s + rmax.s + node->val;
    int exc = max(lmax.f, lmax.s) + max(rmax.f, rmax.s);

    return {inc, exc};
}

int rob(TreeNode *root)
{
    auto ans = dfs(root);
    return max(ans.f, ans.s);
}

// DAY 6 (1217. Minimum Cost to Move Chips to The Same Position)==========================================================================

int minCostToMoveChips(vector<int> &position)
{
    int osum = 0, esum = 0;
    for (int i = 0; i < position.size(); i++)
    {
        osum += (position[i] & 1);
        esum += (position[i] & 1 ^ 1);
    }

    return min(osum, esum);
}