
// DAY 1 (130. Surrounded Regions)========================================================================

void dfs(int i, int j, int n, int m, vector<vector<char>> &arr)
{
    if (i == -1 || j == -1 || i == n || j == m || arr[i][j] == 'X' || arr[i][j] == '#')
        return;

    arr[i][j] = '#';
    dfs(i + 1, j, n, m, arr);
    dfs(i, j + 1, n, m, arr);
    dfs(i - 1, j, n, m, arr);
    dfs(i, j - 1, n, m, arr);
}

void solve(vector<vector<char>> &board)
{
    int n = board.size(), m = board[0].size();

    for (int i = 0; i < n; i++)
    {
        if (board[i][0] == 'O')
            dfs(i, 0, n, m, board);
        if (board[i][m - 1] == 'O')
            dfs(i, m - 1, n, m, board);
    }
    for (int i = 0; i < m; i++)
    {
        if (board[0][i] == 'O')
            dfs(0, i, n, m, board);
        if (board[n - 1][i] == 'O')
            dfs(n - 1, i, n, m, board);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] == 'O')
                board[i][j] = 'X';
            else if (board[i][j] == '#')
                board[i][j] = 'O';
        }
    }
}

// DAY 2 (980. Unique Paths III)=============================================================================

int dfs(int i, int j, int empty, int n, int m, vector<vector<int>> &arr)
{
    if (i == n || j == m || i == -1 || j == -1 || arr[i][j] == -1)
        return 0;
    if (arr[i][j] == 2)
    {
        if (empty == 0)
            return 1;
        return 0;
    }

    arr[i][j] = -1;
    int ans = dfs(i + 1, j, empty - 1, n, m, arr) +
              dfs(i, j + 1, empty - 1, n, m, arr) +
              dfs(i - 1, j, empty - 1, n, m, arr) +
              dfs(i, j - 1, empty - 1, n, m, arr);
    arr[i][j] = 0;

    return ans;
}

int uniquePathsIII(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    int si, sj, empty = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
                si = i, sj = j;
            else if (grid[i][j] == 0)
                empty++;
        }
    }
    return dfs(si, sj, empty + 1, n, m, grid);
}

// DAY 3 (129. Sum Root to Leaf Numbers)========================================================================================

int ans = 0;
void dfs(TreeNode *node, int x)
{
    if (!node)
        return;
    if (!node->left && !node->right)
    {
        ans += x * 10 + node->val;
        return;
    }
    dfs(node->left, x * 10 + node->val);
    dfs(node->right, x * 10 + node->val);
}

int sumNumbers(TreeNode *root)
{
    dfs(root, 0);
    return ans;
}

// DAY 4 (404. Sum of Left Leaves)=================================================================================

int sumOfLeftLeaves(TreeNode *root)
{
    if (!root)
        return 0;
    int tot = sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);

    return tot + ((root->left && !root->left->left && !root->left->right) ? root->left->val : 0);
}

// DAY 5 (441. Arranging Coins)=================================================================================================

int arrangeCoins(int n)
{
    int l = 1, r = INT_MAX;
    while (l < r)
    {
        long m = l + (r - l) / 2;
        if (m * (m + 1) / 2 == n)
            return m;
        if (m * (m + 1) / 2 < n)
            l = m + 1;
        else
            r = m;
    }
    return l - 1;
}

// DAY 6 (260. Single Number III)===================================================================================

vector<int> singleNumber(vector<int> &nums)
{
    long comb = 0;
    for (int x : nums)
        comb ^= x;
    long rsb = comb & -comb;
    int a = 0, b = 0;
    for (int x : nums)
    {
        if (x & rsb)
            a ^= x;
        else
            b ^= x;
    }
    return {a, b};
}

// DAY 7 (43. Multiply Strings)=====================================================================

string multiply(string num1, string num2)
{
    int n = num1.size(), m = num2.size();
    vector<int> prod(n + m);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            int x = i + j;
            int y = i + j + 1;
            int sum = (num1[i] - '0') * (num2[j] - '0') + prod[y];
            prod[y] = sum % 10;
            prod[x] += sum / 10;
        }
    }

    string ans = "";
    for (int i = 0; i < n + m; i++)
    {
        if (prod[i] == 0 && ans.empty())
            continue;
        ans += prod[i] + '0';
    }

    return ans.empty() ? "0" : ans;
}

// DAY 8 (Unique Binary Search Trees)=============================================================================

// METHOD 1 (Memoized)

int dp[20];
int numTrees(int n)
{
    if (n <= 2)
        return n ? n : 1;
    if (dp[n])
        return dp[n];

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += numTrees(i - 1) * numTrees(n - i);

    return dp[n] = ans;
}

// METHOD 2 (Tabulized)

int numTrees(int n)
{
    vector<int> ans(n + 1);
    ans[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
            ans[i] += ans[j - 1] * ans[i - j];
    }
    return ans[n];
}

// DAY 9 (1178. Number of Valid Words for Each Puzzle)=====================================================================================

int toBit(string s)
{
    int mask = 0;
    for (char c : s)
        mask |= 1 << (c - 'a');

    return mask;
}

vector<int> findNumOfValidWords(vector<string> &words, vector<string> &puzzles)
{
    int n = puzzles.size();
    unordered_map<int, int> m;
    for (string s : words)
        m[toBit(s)]++;

    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        int first = (1 << (puzzles[i][0] - 'a'));
        int tot = m[first];

        int mask = toBit(puzzles[i].substr(1));
        int submask = mask;
        while (submask)
        {
            tot += m[submask | first];
            submask = (submask - 1) & mask;
        }
        ans[i] = tot;
    }
    return ans;
}

// DAY 10 (122. Best Time to Buy and Sell Stock II)======================================================================

int maxProfit(vector<int> &prices)
{
    int bprof = INT_MIN, sprof = 0;
    for (int x : prices)
    {
        int pbprof = bprof;
        bprof = max(bprof, sprof - x);
        sprof = max(sprof, pbprof + x);
    }

    return sprof;
}

// DAY 11 (1413. Minimum Value to Get Positive Step by Step Sum)=========================================================

int minStartValue(vector<int> &nums)
{
    int sum = 0, mn = 100;
    for (int x : nums)
    {
        sum += x;
        mn = min(mn, sum);
    }
    return mn < 1 ? -mn + 1 : 1;
}

// DAY 12 (203. Remove Linked List Elements)===============================================================================

ListNode *removeElements(ListNode *head, int val)
{
    ListNode *prev = nullptr, *curr = head, *next = curr;
    while (curr)
    {
        next = curr->next;
        if (curr->val == val)
        {
            if (prev)
                prev->next = curr->next;
            else
                head = head->next;
            curr = nullptr;
        }
        else
            prev = curr;
        curr = next;
    }

    return head;
}

// DAY 13 (739. Daily Temperatures)============================================================================

vector<int> dailyTemperatures(vector<int> &temperatures)
{
    int n = temperatures.size();
    vector<int> ans(n);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && temperatures[i] > temperatures[st.top()])
        {
            ans[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty())
    {
        ans[st.top()] = 0;
        st.pop();
    }

    return ans;
}

// DAY 14 (1286. Iterator for Combination)============================================================================
class CombinationIterator
{
public:
    string s;
    int n;

    queue<string> ans;
    void combs(int i, string x)
    {
        if (x.size() == n)
        {
            ans.push(x);
            return;
        }

        for (int j = i; j < s.size(); j++)
            combs(j + 1, x + s[j]);
    }

    CombinationIterator(string characters, int combinationLength)
    {
        this->s = characters;
        this->n = combinationLength;
        combs(0, "");
    }

    string next()
    {
        string res = ans.front();
        ans.pop();
        return res;
    }

    bool hasNext()
    {
        return !ans.empty();
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

// DAY 15 (368. Largest Divisible Subset)================================================================================

vector<int> largestDivisibleSubset(vector<int> &nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<int> ans, dp(n, 1), nxti(n, -1);
    int mxi = n - 1;
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (nums[j] % nums[i] == 0 && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                nxti[i] = j;
            }
        }
        if (dp[i] > dp[mxi])
            mxi = i;
    }

    int i = mxi;
    while (i != -1)
    {
        ans.push_back(nums[i]);
        i = nxti[i];
    }

    return ans;
}

// DAY 16 (668. Kth Smallest Number in Multiplication Table)==================================================================

int mid_lb_count(int x, int n, int m)
{
    int count = 0;
    for (int i = 1; i <= n; i++)
        count += min(x / i, m);
    return count;
}

int findKthNumber(int n, int m, int k)
{
    int si = 1, ei = n * m;

    while (si < ei)
    {
        int mid = si + ((ei - si) >> 1);
        if (mid_lb_count(mid, n, m) >= k)
            ei = mid;
        else
            si = mid + 1;
    }

    return si;
}

// DAY 17 (62. Unique Paths)=================================================================================

int uniquePaths(int n, int m) 
{
    vector<vector<int>> paths(n, vector<int>(m, 0));
    paths[n-1][m-1] = 1;
    
    for(int i = n-1; i >= 0; i--)
    {
        for(int j = m-1; j >= 0; j--)
        {
            if(i == n-1 && j == m-1)
                continue;
            int dans = (i == n-1)? 0 : paths[i+1][j];
            int rans = (j == m-1)? 0 : paths[i][j+1];
            
            paths[i][j] = dans + rans;
        }
    }
    
    return paths[0][0];
}

// DAY 18 (448. Find All Numbers Disappeared in an Array)================================================================

vector<int> findDisappearedNumbers(vector<int>& nums) 
{
    vector<int> ans;
    for(int &x : nums)
        nums[abs(x)-1] = -1*abs(nums[abs(x)-1]);
    
    for(int i = 0; i < nums.size(); i++)
        if(nums[i] > 0)
            ans.push_back(i+1);
    
    return ans;
}