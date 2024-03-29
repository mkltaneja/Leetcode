// DAY 1 (Array Nesting)=============================================================================

int arrayNesting(vector<int> &nums)
{
    int maxcycle = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        int size = 0, j = i;
        while (nums[j] != -1)
        {
            int nxt = nums[j];
            nums[j] = -1;
            j = nxt;
            size++;
        }
        maxcycle = max(maxcycle, size);
    }
    return maxcycle;
}

// DAY 2 (Unique Binary Search Trees 2)=========================================================================

vector<TreeNode *> makeTree(int st, int end, vector<vector<vector<TreeNode *>>> &dp)
{
    if (st > end)
        return {nullptr};
    if (st == end)
        return dp[st][end] = {new TreeNode(st)};
    if (!dp[st][end].empty())
        return dp[st][end];

    vector<TreeNode *> curr;
    for (int x = st; x <= end; x++)
    {
        vector<TreeNode *> left = makeTree(st, x - 1, dp);
        vector<TreeNode *> right = makeTree(x + 1, end, dp);
        for (TreeNode *l : left)
            for (TreeNode *r : right)
                curr.push_back(new TreeNode(x, l, r));
    }
    return dp[st][end] = curr;
}

vector<TreeNode *> generateTrees(int n)
{
    vector<vector<vector<TreeNode *>>> dp(n + 1, vector<vector<TreeNode *>>(n + 1));
    return makeTree(1, n, dp);
}

// DAY 3 (Erect The Fence)=============================================================================

int crossProduct(vector<int> &a, vector<int> &b, vector<int> &c)
{
    // CROSS PRODUCT OF AB and AC --> x1*y2 - x2*y1
    return ((b[0] - a[0]) * (c[1] - a[1]) - (c[0] - a[0]) * (b[1] - a[1]));
}

vector<vector<int>> outerTrees(vector<vector<int>> &trees)
{
    int n = trees.size();
    if (n <= 3)
        return trees;
    sort(trees.begin(), trees.end(), [](auto const &a, auto const &b)
         { return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0]; });

    vector<vector<int>> upper;
    upper.push_back(trees[0]);
    upper.push_back(trees[1]);
    for (int i = 2; i < n; i++)
    {
        int sz = upper.size();
        while (sz >= 2 && crossProduct(upper[sz - 2], upper[sz - 1], trees[i]) > 0)
        {
            upper.pop_back();
            sz--;
        }
        upper.push_back(trees[i]);
    }

    vector<vector<int>> lower;
    lower.push_back(trees[n - 1]);
    lower.push_back(trees[n - 2]);
    for (int i = n - 3; i >= 0; i--)
    {
        int sz = lower.size();
        while (sz >= 2 && crossProduct(lower[sz - 2], lower[sz - 1], trees[i]) > 0)
        {
            lower.pop_back();
            sz--;
        }
        lower.push_back(trees[i]);
    }

    upper.pop_back();
    lower.pop_back();

    for (auto v : lower)
        upper.push_back(v);

    sort(upper.begin(), upper.end());
    upper.erase(unique(upper.begin(), upper.end()), upper.end());

    return upper;
}

// DAY 4 (Sum of Distances in Tree)===========================================================================

vector<int> cnt, ans;
void dfs1(int u, int p, vector<vector<int>> &gp)
{
    for (int v : gp[u])
    {
        if (v != p)
        {
            dfs1(v, u, gp);
            cnt[u] += cnt[v];
            ans[u] += ans[v] + cnt[v];
        }
    }
}
void dfs2(int u, int p, vector<vector<int>> &gp)
{
    for (int v : gp[u])
    {
        if (v != p)
        {
            ans[v] = ans[u] - cnt[v] + (gp.size() - cnt[v]);
            dfs2(v, u, gp);
        }
    }
}

vector<int> sumOfDistancesInTree(int n, vector<vector<int>> &edges)
{
    vector<vector<int>> gp(n);
    for (auto e : edges)
    {
        gp[e[0]].push_back(e[1]);
        gp[e[1]].push_back(e[0]);
    }
    cnt.resize(n, 1), ans.resize(n, 0);
    dfs1(0, -1, gp);
    dfs2(0, -1, gp);

    return ans;
}

// DAY 5 (Orderly Queue)===================================================================

string orderlyQueue(string s, int k)
{
    if (k > 1)
    {
        sort(s.begin(), s.end());
        return s;
    }
    char minc = 'z';
    for (char c : s)
        minc = min(minc, c);
    string ans = s;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == minc)
        {
            string x = s.substr(i, s.size()) + s.substr(0, i);
            if (x < ans)
                ans = x;
        }
    }
    return ans;
}

// DAY 6 (Slowest Key)==================================================================================

char slowestKey(vector<int> &releaseTimes, string keysPressed)
{
    char ans = NULL;
    int maxdur = 0;
    for (int i = 0; i < releaseTimes.size(); i++)
    {
        int dur = releaseTimes[i] - (i ? releaseTimes[i - 1] : 0);
        if (ans == NULL || dur > maxdur)
        {
            ans = keysPressed[i];
            maxdur = dur;
        }
        else if (dur == maxdur && keysPressed[i] > ans)
            ans = keysPressed[i];
    }
    return ans;
}

// DAY 7 (Reverse linked List)=================================================================================

ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr, *curr = head, *forw = head;
    while (curr)
    {
        forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    return prev;
}

// DAY 8 (Shifting Letters)====================================================

string shiftingLetters(string s, vector<int> &shifts)
{
    for (int i = shifts.size() - 1; i >= 0; i--)
    {
        shifts[i] = (shifts[i] + ((i == shifts.size() - 1) ? 0 : shifts[i + 1])) % 26;
        s[i] = char(((s[i] - 'a') + shifts[i]) % 26 + 'a');
        cout << shifts[i] << ", " << s[i] << endl;
    }
    return s;
}

// DAY 9 (Largest Plus Sign)===============================================================

int orderOfLargestPlusSign(int n, vector<vector<int>> &mines)
{
    vector<vector<int>> grid(n, vector<int>(n, 1));
    for (auto v : mines)
        grid[v[0]][v[1]] = 0;
    vector<vector<vector<int>>> arr(vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(4, 0))));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int left = (grid[i][j] && j) ? arr[i][j - 1][0] : 0;
            int up = (grid[j][i] && j) ? arr[j - 1][i][2] : 0;
            int down = (grid[n - j - 1][i] && j) ? arr[n - j][i][1] : 0;
            int right = (grid[i][n - j - 1] && j) ? arr[i][n - j][3] : 0;
            arr[i][j][0] = grid[i][j] + left;
            arr[j][i][2] = grid[j][i] + up;
            arr[n - j - 1][i][1] = grid[n - j - 1][i] + down;
            arr[i][n - j - 1][3] = grid[i][n - j - 1] + right;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans = max(ans, min({arr[i][j][0], arr[i][j][1], arr[i][j][2], arr[i][j][3]}));
    return ans;
}

// DAY 10 (Arithimetic Slices 2 - Subsequence)=============================================================

int numberOfArithmeticSlices(vector<int> &nums)
{
    int n = nums.size();
    vector<unordered_map<long, long>> cnts(n);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            long diff = (long)nums[i] - nums[j];
            cnts[i][diff]++;
            if (cnts[j].count(diff))
            {
                cnts[i][diff] += cnts[j][diff];
                ans += cnts[j][diff];
            }
        }
    }

    return ans;
}

// DAY 11 (Basic Calculator)==========================================================

int calc(int &i, string &s)
{
    int x = 0, pol = 1, sum = 0;
    for (; i < s.size() && s[i] != ')'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            x = x * 10 + (s[i] - '0');
        else if (s[i] == '+' || s[i] == '-')
        {
            sum += pol * x;
            x = 0;
            pol = (s[i] == '+') ? 1 : -1;
        }
        else if (s[i] == '(')
            sum += pol * calc(++i, s);
    }
    return sum + pol * x;
}

int calculate(string s)
{
    int i = 0;
    return calc(i, s);
}

// DAY 12 (Reachable Nodes in Subdivided Graph)==============================================================

#define f first
#define s second

class comp
{
public:
    bool operator()(pair<int, int> &a, pair<int, int> &b)
    {
        return a.s < b.s;
    }
};

int reachableNodes(vector<vector<int>> &edges, int maxMoves, int n)
{
    vector<unordered_map<int, int>> gp(n);
    for (auto v : edges)
    {
        gp[v[0]].insert({v[1], v[2]});
        gp[v[1]].insert({v[0], v[2]});
    }

    vector<bool> vis(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq;
    pq.push({0, maxMoves});
    int ans = 1;
    while (!pq.empty())
    {
        auto tp = pq.top();
        pq.pop();
        if (vis[tp.f])
        {
            ans--;
            continue;
        }
        vis[tp.f] = true;

        for (auto v : gp[tp.f])
        {
            int rem = v.s;
            if (!vis[v.f] || rem)
            {
                if (rem <= tp.s)
                {
                    if (rem == tp.s)
                        ans--;
                    ans += rem + 1;
                    gp[tp.f][v.f] = 0;
                    gp[v.f][tp.f] = 0;
                }
                else
                {
                    ans += tp.s;
                    gp[tp.f][v.f] = rem - tp.s;
                    gp[v.f][tp.f] = rem - tp.s;
                }
                if (tp.s - rem - 1 >= 0)
                    pq.push({v.f, tp.s - rem - 1});
            }
        }
    }
    return ans;
}

// DAY 13 (Maximum Number of Balloons)===============================================================

int maxNumberOfBalloons(string text)
{
    unordered_map<char, int> req;
    req['b'] = 1, req['a'] = 1, req['l'] = 2, req['o'] = 2, req['n'] = 1;

    unordered_map<char, int> curr;
    for (char c : text)
        curr[c]++;

    int ans = text.size();
    for (auto p : req)
        ans = min(ans, curr[p.first] / p.second);

    return ans;
}

// DAY 14 (Reverse Only Letters)==================================================================

string reverseOnlyLetters(string s)
{
    string t = "";
    for (char c : s)
    {
        char x = tolower(c);
        if (x >= 'a' && x <= 'z')
            t += c;
    }
    reverse(t.begin(), t.end());

    int i = 0;
    for (char &c : s)
    {
        char x = tolower(c);
        if (x >= 'a' && x <= 'z')
            c = t[i++];
    }
    return s;
}

// DAY 15 (Longest Turbulent Subarray)=====================================================================

int maxTurbulenceSize(vector<int> &arr)
{
    int maxans = 1;
    int psmall = 1, plarge = 1;
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] > arr[i - 1])
        {
            plarge = psmall + 1;
            psmall = 1;
        }
        else if (arr[i] < arr[i - 1])
        {
            psmall = plarge + 1;
            plarge = 1;
        }
        else
            psmall = 1, plarge = 1;
        maxans = max({maxans, psmall, plarge});
    }
    return maxans;
}

// DAY 16 (Spiral Matrix)======================================================================

vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    vector<int> ans(n * m);
    int k = 0;
    int sr = 0, sc = 0, er = n - 1, ec = m - 1;
    while (k < n * m)
    {
        for (int i = sc; i <= ec && k < n * m; i++)
            ans[k++] = matrix[sr][i];
        sr++;
        for (int i = sr; i <= er && k < n * m; i++)
            ans[k++] = matrix[i][ec];
        ec--;
        for (int i = ec; i >= sc && k < n * m; i--)
            ans[k++] = matrix[er][i];
        er--;
        for (int i = er; i >= sr && k < n * m; i--)
            ans[k++] = matrix[i][sc];
        sc++;
    }

    return ans;
}

// DAY 17 (Intersection of 2 Arrays)=============================================================

vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
{
    unordered_map<int, int> m;
    for (int x : nums1)
        m[x]++;
    vector<int> ans;
    for (int x : nums2)
    {
        if (m[x])
        {
            ans.push_back(x);
            m[x]--;
        }
    }
    return ans;
}

// DAY 19 (Distinct Subsequences)============================================================

int numDistinct(string s, string t)
{
    int n = s.size(), m = t.size();
    vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1, 0));
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (j == 0)
                dp[i][j] = 1;
            else if (i == 0)
                dp[i][j] = 0;
            else
                dp[i][j] = dp[i - 1][j] + ((s[i - 1] == t[j - 1]) ? dp[i - 1][j - 1] : 0);
        }
    }
    return dp[n][m];
}

// DAY 20 (Find Winner in a Tic Tac Toe Game)==================================================================

string rowwin(vector<vector<int>> &tt)
{
    if (tt[0][0] != -1 && tt[0][0] == tt[0][1] && tt[0][0] == tt[0][2])
        return tt[0][0] ? "B" : "A";
    if (tt[1][0] != -1 && tt[1][0] == tt[1][1] && tt[1][0] == tt[1][2])
        return tt[1][0] ? "B" : "A";
    if (tt[2][0] != -1 && tt[2][0] == tt[2][1] && tt[2][0] == tt[2][2])
        return tt[2][0] ? "B" : "A";
    return "";
}

string colwin(vector<vector<int>> &tt)
{
    if (tt[0][0] != -1 && tt[0][0] == tt[1][0] && tt[0][0] == tt[2][0])
        return tt[0][0] ? "B" : "A";
    if (tt[0][1] != -1 && tt[0][1] == tt[1][1] && tt[0][1] == tt[2][1])
        return tt[0][1] ? "B" : "A";
    if (tt[0][2] != -1 && tt[0][2] == tt[1][2] && tt[0][2] == tt[2][2])
        return tt[0][2] ? "B" : "A";
    return "";
}

string diagwin(vector<vector<int>> &tt)
{
    if (tt[0][0] != -1 && tt[0][0] == tt[1][1] && tt[0][0] == tt[2][2])
        return tt[0][0] ? "B" : "A";
    if (tt[0][2] != -1 && tt[0][2] == tt[1][1] && tt[0][2] == tt[2][0])
        return tt[0][2] ? "B" : "A";
    return "";
}

string tictactoe(vector<vector<int>> &moves)
{
    vector<vector<int>> tt(3, vector<int>(3, -1));
    for (int i = 0; i < moves.size(); i++)
        tt[moves[i][0]][moves[i][1]] = (i & 1);

    string rowans = rowwin(tt);
    if (!rowans.empty())
        return rowans;

    string colans = colwin(tt);
    if (!colans.empty())
        return colans;

    string diagans = diagwin(tt);
    if (!diagans.empty())
        return diagans;

    return (moves.size() == 9) ? "Draw" : "Pending";
}

// DAY 21 (Max Consecutive Ones)==============================================================

int findMaxConsecutiveOnes(vector<int> &nums)
{
    int ans = 0, curr = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        curr = nums[i] ? curr + 1 : 0;
        ans = max(ans, curr);
    }
    return ans;
}

// DAY 22 (Maximum Length of a Concatenated String With Unique Characters)=====================================

// METHOD 1 (Subsequences) --> O(2^n)

int checkuni(vector<string> &conc)
{
    int map[26] = {0};
    int ans = 0;
    for (string s : conc)
    {
        for (char c : s)
        {
            if (map[c - 'a'])
                return 0;
            map[c - 'a']++;
            ans++;
        }
    }
    return ans;
}

int maxLength(vector<string> &arr)
{
    int n = arr.size();
    int ans = 0;
    for (int i = 0; i < (1 << n); i++)
    {
        int x = i;
        int j = 0;
        vector<string> tmp;
        while (x)
        {
            if (x & 1)
                tmp.push_back(arr[j]);
            j++;
            x >>= 1;
        }
        ans = max(ans, checkuni(tmp));
    }
    return ans;
}

// METHOD 2 (Using DP and Bitmask) --> O(n^2)

int cntbits(int x)
{
    int ans = 0;
    while (x)
    {
        x &= x - 1;
        ans++;
    }
    return ans;
}

int maxLength(vector<string> &arr)
{
    vector<int> dp;
    int ans = 0;
    for (string s : arr)
    {
        int x = 0;
        bool valid = true;
        for (char c : s)
        {
            if (x & (1 << (c - 'a')))
            {
                valid = false;
                break;
            }
            x |= (1 << (c - 'a'));
        }
        if (!valid)
            continue;
        int n = cntbits(x);
        ans = max(ans, n);

        for (int i = dp.size() - 1; i >= 0; i--)
        {
            if (dp[i] & x)
                continue;
            dp.push_back(dp[i] | x);
            ans = max(ans, cntbits(dp[i]) + n);
        }
        dp.push_back(x);
    }
    return ans;
}

// DAY 23 (Break a Palindrome)========================================================================

string breakPalindrome(string s)
{
    int n = s.size();
    if (n == 1)
        return "";

    for (int i = 0; i < n / 2; i++)
    {
        if (s[i] == 'a')
            continue;
        s[i] = 'a';
        return s;
    }
    s[n - 1] = 'b';

    return s;
}

// DAY 24 (N-th Tribonacci Number)===============================================================================

int tribonacci(int n)
{
    int a = 0, b = 1, c = 1, sum = 1;

    if (n == 0)
        return a;

    for (int i = 3; i <= n; i++)
    {
        sum = a + b + c;
        a = b;
        b = c;
        c = sum;
    }
    return sum;
}

// DAY 26 (Shortest Path in a Grid with Obstacle Elimination)============================================================

#define f first
#define s second

int shortestPath(vector<vector<int>> &grid, int k)
{
    int n = grid.size(), m = grid[0].size();

    queue<pair<int, int>> que;
    que.push({0, k});

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vector<vector<bool>>> vis(n, vector<vector<bool>>(m, vector<bool>(k + 1, false)));

    int lvl = 0;
    while (!que.empty())
    {
        int sz = que.size();
        while (sz--)
        {
            auto tp = que.front();
            que.pop();
            int i = tp.f / m;
            int j = tp.f % m;

            if (tp.s < 0)
                continue;

            if (i == n - 1 && j == m - 1)
                return lvl;

            for (int d = 0; d < 4; d++)
            {
                int r = i + dir[d][0];
                int c = j + dir[d][1];
                if (r != -1 && c != -1 && r != n && c != m && (tp.s - grid[r][c]) >= 0 && !vis[r][c][tp.s - grid[r][c]])
                {
                    vis[r][c][tp.s - grid[r][c]] = true;
                    que.push({r * m + c, tp.s - grid[r][c]});
                }
            }
        }
        lvl++;
    }
    return -1;
}

// DAY 26 (Transform to Chessboard)==================================================================================================

int movesToChessboard(vector<vector<int>> &board)
{
    int n = board.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if ((board[0][0] ^ board[i][0]) ^ (board[0][j] ^ board[i][j]))
                return -1;
    int ones_in_1st_row = 0, ones_in_1st_col = 0;
    int row_moves = 0, col_moves = 0;
    for (int i = 0; i < n; i++)
    {
        ones_in_1st_row += board[0][i];
        ones_in_1st_col += board[i][0];

        row_moves += (board[i][0] == (i & 1));
        col_moves += (board[0][i] == (i & 1));
    }

    if (ones_in_1st_row < n / 2 || ones_in_1st_row > (n + 1) / 2)
        return -1;
    if (ones_in_1st_col < n / 2 || ones_in_1st_col > (n + 1) / 2)
        return -1;

    if (n & 1)
    {
        if (row_moves & 1)
            row_moves = n - row_moves;
        if (col_moves & 1)
            col_moves = n - col_moves;
    }
    else
    {
        row_moves = min(row_moves, n - row_moves);
        col_moves = min(col_moves, n - col_moves);
    }

    return (row_moves + col_moves) / 2;
}

// DAY 27 (Unique Email Addresses)===============================================================

int numUniqueEmails(vector<string> &emails)
{
    unordered_set<string> st;
    for (string s : emails)
    {
        string lname = "", dname = "";
        int i = 0;
        while (i < s.size() && s[i] != '@' && s[i] != '+')
        {
            if (s[i] == '.')
                i++;
            else
                lname += s[i++];
        }
        if (s[i] == '+')
            while (i < s.size() && s[i] != '@')
                i++;
        while (i < s.size())
            dname += s[i++];
        st.insert(lname + "@" + dname);
        // cout<<lname<<"@"<<dname<<endl;
    }
    return st.size();
}

// DAY 28 (Sort Array by Parity 2)===============================================================================

// METHOD 1 (Using queue)

vector<int> sortArrayByParityII(vector<int> &nums)
{
    queue<int> eo, oe;
    for (int i = 0; i < nums.size(); i++)
    {
        if ((nums[i] & 1) != (i & 1))
        {
            if (i & 1)
            {
                if (!eo.empty())
                {
                    swap(nums[eo.front()], nums[i]);
                    eo.pop();
                }
                else
                    oe.push(i);
            }
            else
            {
                if (!oe.empty())
                {
                    swap(nums[oe.front()], nums[i]);
                    oe.pop();
                }
                else
                    eo.push(i);
            }
        }
    }
    return nums;
}

// METHOD 2 (2 Pointer Approach)

vector<int> sortArrayByParityII(vector<int> &nums)
{
    int i = 0, j = 1;
    while (i < nums.size() && j < nums.size())
    {
        if ((nums[i] & 1) == 0)
            i += 2;
        else if (nums[j] & 1)
            j += 2;
        else
        {
            swap(nums[i], nums[j]);
            i += 2;
            j += 2;
        }
    }
    return nums;
}

// DAY 29 (Split Linked List in Parts)================================================================================

vector<ListNode *> splitListToParts(ListNode *head, int k)
{
    int n = 0;
    ListNode *itr = head;
    while (itr)
    {
        itr = itr->next;
        n++;
    }
    int x = n / k, y = n % k;

    vector<ListNode *> ans(k);

    itr = head;
    int i = 0;
    while (itr && i < k)
    {
        int tmp = x + ((y > 0) ? 1 : 0);
        ListNode *curr = itr;
        while (curr && --tmp)
            curr = curr->next;

        ListNode *tmpnode = nullptr;
        if (curr)
        {
            tmpnode = curr->next;
            curr->next = nullptr;
        }
        ans[i++] = itr;
        itr = tmpnode;
        y--;
    }

    return ans;
}