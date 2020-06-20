//DAY 1(Invert Binary Tree)

// Method 1 (by saving the right at every step)
TreeNode *invertTree(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;

    TreeNode *r = root->right;
    root->right = invertTree(root->left);
    root->left = invertTree(r);

    return root;
}

///////////////OR//////////////
// Method 2 (by swaping the left and right at every step)
TreeNode *invertTree(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;

    invertTree(root->left);
    invertTree(root->right);
    swap(root->left, root->right);

    return root;
}

//DAY 2(Delete Node in a Linked List)===============================================

void deleteNode(ListNode *&node)
{
    node->val = node->next->val;
    node->next = node->next->next;
}

///////////////OR///////////////

void deleteNode(ListNode *&node)
{
    *node = *(node->next);
}

//DAY 3()===============================================================================

// (by custom comparator)
static bool sort_bydiff(vector<int> &a, vector<int> &b)
{
    return (a[0] - a[1]) < (b[0] - b[1]);
}

int twoCitySchedCost(vector<vector<int>> &costs)
{
    int n = costs.size();
    int sum = 0;
    sort(costs.begin(), costs.end(), sort_bydiff);

    for (int i = 0; i < n / 2; i++)
        sum += costs[i][0];
    for (int i = n / 2; i < n; i++)
        sum += costs[i][1];

    return sum;
}

/////////////OR//////////////////

// (by LAMBDA OPERATION custom operator)

int twoCitySchedCost(vector<vector<int>> &costs)
{
    int n = costs.size();
    int sum = 0;
    sort(costs.begin(), costs.end(), [](const vector<int> &a, const vector<int> &b) {
        return (a[0] - a[1]) < b[0] - b[1];
    });

    for (int i = 0; i < n / 2; i++)
        sum += costs[i][0];
    for (int i = n / 2; i < n; i++)
        sum += costs[i][1];

    return sum;
}

//DAY 4(Reverse String)==============================================================================

// (using swap function)
void reverseString(vector<char> &s)
{
    for (int i = 0; i < s.size() / 2; i++)
        swap(s[i], s[s.size() - i - 1]);
}

////////////////OR/////////////////
// (using reverse function)
void reverseString(vector<char> &s)
{
    reverse(s.begin(), s.end());
}

///////////////OR/////////////////
// (using 2 pointer approach)
void reverseString(vector<char> &s)
{
    int l = 0, h = s.size() - 1;
    while (l < h)
    {
        char c = s[l];
        s[l] = s[h];
        s[h] = c;
        l++, h--;
    }
}

// DAY 5( Random Pick with Weight)=================================================================

class Solution
{
public:
    vector<int> wsum;
    int sum;
    Solution(vector<int> &w)
    {
        sum = 0;
        for (int i : w)
        {
            sum += i;
            wsum.push_back(sum);
        }
    }

    int binary_search(int val)
    {
        int l = 0, h = wsum.size() - 1;
        while (l < h)
        {
            int mid = (l + h) / 2;
            if (wsum[mid] < val)
                l = mid + 1;
            else
                h = mid;
        }
        return l;
    }

    int pickIndex()
    {
        int idx = rand() % sum;
        return binary_search(idx + 1);
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */

// DAY 6()==========================================================================================
// (by sorting a[0] in ascending order)
// O(n^2)
vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
{
    int n = people.size();

    sort(people.begin(), people.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[0] < b[0];
    });

    // for(int i=0;i<n;i++)
    //     cout<<people[i][0]<<" "<<people[i][1]<<endl;

    vector<vector<int>> qu(n, vector<int>(2, -1));

    for (int i = 0; i < n; i++)
    {
        int foll = people[i][1];
        for (int j = 0; j < n; j++)
        {
            if (foll == 0 && qu[j][0] == -1)
            {
                qu[j][0] = people[i][0];
                qu[j][1] = people[i][1];
                break;
            }
            else if (foll > 0 && (qu[j][0] == -1 || qu[j][0] >= people[i][0]))
                foll--;
        }
    }
    return qu;
}

/////////////////////OR//////////////////////////
// (by sorting a[0] in descending order and a[1] in ascending order)
// <O(n^2) & >O(n)
vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
{
    int n = people.size();

    sort(people.begin(), people.end(), [](const vector<int> &a, const vector<int> &b) {
        if (a[0] == b[0])
            return a[1] < b[1];
        else
            return a[0] > b[0];
    });

    vector<vector<int>> qu;
    for (vector<int> ar : people)
        qu.insert(qu.begin() + ar[1], ar);

    return qu;
}

// DAY 7()====================================================================

// Method 1 -> by combinations
// <O(tar^n)
// this code msay give TLE
int count_change(int amount, int idx, vector<int> &coins)
{
    if (amount == 0)
        return 1;
    int count = 0;
    for (int i = idx; i < coins.size(); i++)
        if (amount - coins[i] >= 0)
            count += count_change(amount - coins[i], i, coins);
    return count;
}

int change(int amount, vector<int> &coins)
{
    return count_change(amount, 0, coins);
}

///////////////////OR/////////////////

// Method 2 -> by subsequences
// O(2^n)
// this may also TLE
int count_change(int amount, int idx, vector<int> &coins)
{
    if (idx == coins.size() || amount == 0)
    {
        if (amount == 0)
            return 1;
        return 0;
    }

    int count = 0;
    if (amount - coins[idx] >= 0)
        count += count_change(amount - coins[idx], idx, coins);
    count += count_change(amount, idx + 1, coins);

    return count;
}

int change(int amount, vector<int> &coins)
{
    return count_change(amount, 0, coins);
}

////////////////OR//////////////////

// by DP(2D) of subsequence
// O(n^2)
int count_change(int tar, vector<int> &coins, vector<vector<int>> &dp, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= tar; j++)
        {
            if (j == 0)
            {
                dp[i][j] = 1;
                continue;
            }
            if (i == 0)
            {
                dp[i][j] = 0;
                continue;
            }
            if (j - coins[i - 1] >= 0)
                dp[i][j] += dp[i][j - coins[i - 1]] + dp[i - 1][j];
            else
                dp[i][j] += dp[i - 1][j];
        }
    }
    return dp[n - 1][tar];
}

int change(int amount, vector<int> &coins)
{
    vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1, 0));

    return count_change(amount, coins, dp, coins.size() + 1);
}

/////////////////OR/////////////////////

// Method->4(1D DP)
int change(int amount, vector<int> &coins)
{
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for (int coin : coins)
        for (int i = coin; i <= amount; i++)
            dp[i] += dp[i - coin];
    return dp[amount];
}

// DAY 8(Power of Two)===================================================================

bool isPowerOfTwo(int n)
{
    return n > 0 && !(n & (n - 1));
}

// DAY 9(Is Subsequence)======================================================================

// (in 2 loops but O(t.size()))
bool isSubsequence(string s, string t)
{
    int l = 0;
    for (int i = 0; i < s.size(); i++)
    {
        bool f = false;
        for (int j = l; j < t.size(); j++)
        {
            if (t[j] == s[i])
            {
                f = true;
                l = j + 1;
                break;
            }
        }
        if (!f)
            return false;
    }
    return true;
}

//////////////////OR///////////////

// (by 1 loop and O(t.size()))
bool isSubsequence(string s, string t)
{
    int n = s.size();
    int m = t.size();

    if (n > m)
        return false;

    if (n == m && s != t)
        return false;
    else if (n == m && s == t)
        return true;

    int j = 0;
    if (n < m)
    {
        for (int i = 0; i < m; i++)
        {
            if (t[i] == s[j])
                j++;
        }
    }
    return (j == n);
}

// DAY 10(Search Insert Position)=====================================================================

// O(n)
int searchInsert(vector<int> &nums, int target)
{
    for (int i = -0; i < nums.size(); i++)
    {
        if (target <= nums[i])
            return i;
    }
    return nums.size();
}

/////////////////OR//////////////////

// O(log(n))
int searchInsert(vector<int> &nums, int target)
{
    int n = nums.size();
    int l = 0, r = n;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] < target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

/////////////////////OR////////////////////

// <=O(logn)
int searchInsert(vector<int> &nums, int target)
{
    int l = 0;
    int r = nums.size() - 1;

    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            l = mid + 1;
        else if (nums[mid] > target)
            r = mid - 1;
    }
    return l;
}

//DAY 11(Sort colors)=======================================================================================

// O(n)
// by counting 0,1,2 -> 2 pass algo
void sortColors(vector<int> &nums)
{
    int count0 = 0;
    int count1 = 0;
    int count2 = 0;
    for (int i : nums)
    {
        if (i == 0)
            count0++;
        else if (i == 1)
            count1++;
        else
            count2++;
    }
    for (int i = 0; i < nums.size(); i++)
    {
        if (count0 > 0)
        {
            nums[i] = 0;
            count0--;
            continue;
        }
        else if (count1 > 0)
        {

            nums[i] = 1;
            count1--;
            continue;
        }
        else if (count2 > 0)
        {

            nums[i] = 2;
            count2--;
            continue;
        }
    }
}

/////////////////OR////////////////

// O(n)
// by swapping --> 1 pass algo
void sortColors(vector<int> &nums)
{
    int i = 0, p1 = 0, p2 = nums.size() - 1;
    while (i < nums.size())
    {
        if (nums[i] == 0)
        {
            swap(nums[i], nums[p1]);
            i++;
            p1++;
        }
        else if (nums[i] == 1)
        {
            i++;
        }
        else if (nums[i] == 2)
        {
            while (nums[p2] == 2)
            {
                if (p2 == i)
                    return;
                p2--;
            }
            swap(nums[i], nums[p2]);
        }
    }
}

// DAY 12(Insert Delete GetRandom O(1))====================================================================

// this code will return random in O(n) and not in O(1)
class RandomizedSet
{
public:
    /** Initialize your data structure here. */
    set<int> s;
    RandomizedSet()
    {
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        if (s.find(val) == s.end())
        {
            s.insert(val);
            return true;
        }
        return false;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
        if (s.find(val) != s.end())
        {
            s.erase(val);
            return true;
        }
        return false;
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        return *next(s.begin(), rand() % s.size()); // --> next will iterate to the next one but rand will give any random address
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

///////////////////OR///////////////////////

// less complex insert and remove
class RandomizedSet
{
public:
    unordered_set<int> s;
    RandomizedSet()
    {
    }

    bool insert(int val)
    {
        return s.insert(val).second; //   -->  the second of the insert iterator is bool and first is int
    }                                //   -->  if element is present it will return false

    bool remove(int val)
    {
        return s.erase(val); // -> will return false if not present
    }

    int getRandom()
    {
        return *next(s.begin(), rand() % s.size());
    }
};

/////////////////OR//////////////////////////

// O(1)
class RandomizedSet
{
public:
    vector<int> arr;
    unordered_map<int, int> m;

    RandomizedSet()
    {
    }

    bool insert(int val)
    {
        if (m.find(val) != m.end())
            return false;

        arr.emplace_back(val);
        m[val] = arr.size() - 1;
        return true;
    }

    bool remove(int val)
    {
        if (m.find(val) == m.end())
            return false;

        int idx = m[val];
        arr[idx] = arr[arr.size() - 1];
        m[arr[idx]] = idx;

        arr.pop_back();
        m.erase(val);
        return true;
    }

    int getRandom()
    {
        return arr[rand() % arr.size()];
    }
};

//DAY 13()=========================================================================

// O(n^2) time and O(n^2) space --> this may give TLE

vector<int> largestDivisibleSubset(vector<int> &nums)
{
    int n = nums.size();
    if (n <= 1)
        return nums;
    // vector<int> nums1 = nums;
    sort(nums.begin(), nums.end());

    vector<vector<int>> maxmult(n, vector<int>());
    // for(int i=0;i<n;i++)

    int maxlen = 0;
    int maxidx = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        maxmult[i].push_back(nums[i]);
        int maxsize = 0;
        int k = i;
        for (int j = i + 1; j < n; j++)
        {
            cout << j << " ";
            if (nums[j] % nums[i] == 0 && maxmult[j].size() > maxsize)
            {
                maxsize = maxmult[j].size();
                k = j;
            }
        }
        if (k != i)
        {
            maxmult[i].insert(maxmult[i].end(), maxmult[k].begin(), maxmult[k].end());
            if (maxmult[i].size() > maxlen)
            {
                maxlen = maxmult[i].size();
                maxidx = i;
                // cout<<maxidx<<" "<<maxlen<<endl;
            }
        }
    }

    // cout<<endl;
    // for(int i=0;i<maxmult.size();i++)
    // {
    //     for(int j=0;j<maxmult[i].size();j++)
    //         cout<<maxmult[i][j]<<" ";
    //     cout<<endl;
    // }
    return maxmult[maxidx];
}

////////////////////OR//////////////////////

// O(n^2) time and O(n) space --> this won't give TLE

vector<int> largestDivisibleSubset(vector<int> &nums)
{
    int n = nums.size();
    if (n <= 1)
        return nums;
    // vector<int> nums1 = nums;
    sort(nums.begin(), nums.end());

    vector<int> next_idx(n, -1);
    vector<int> sizes(n, 1);
    // for(int i=0;i<n;i++)

    int maxlen = 0;
    int maxidx = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int maxsize = 0;
        int k = i;
        for (int j = i + 1; j < n; j++)
        {
            if (nums[j] % nums[i] == 0 && sizes[j] > maxsize)
            {
                maxsize = sizes[j];
                k = j;
            }
        }
        if (k != i)
        {
            sizes[i] += sizes[k];
            next_idx[i] = k;
            if (sizes[i] > maxlen)
            {
                maxlen = sizes[i];
                maxidx = i;
                // cout<<maxidx<<" "<<maxlen<<endl;
            }
        }
    }
    vector<int> maxmult;
    int curr = maxidx;
    while (curr != -1)
    {
        maxmult.push_back(nums[curr]);
        curr = next_idx[curr];
    }

    // cout<<endl;
    // for(int i=0;i<maxmult.size();i++)
    // {
    //     for(int j=0;j<maxmult[i].size();j++)
    //         cout<<maxmult[i][j]<<" ";
    //     cout<<endl;
    // }
    return maxmult;
}

// DAY 14()=================================================================

// Method 1 -> DFS
// this may give TLE
class Solution
{
public:
    int mcost = INT_MAX;
    int mincost_dfs(vector<vector<pair<int, int>>> &graph, vector<bool> &vis, int src, int dest, int k, int cost)
    {
        if (src == dest)
            return cost;

        if (k == 0)
            return INT_MAX;

        for (pair<int, int> itr : graph[src])
        {
            if (!vis[itr.first])
            {
                vis[itr.first] = true;
                cost += itr.second;
                k--;

                mcost = min(mcost, mincost_dfs(graph, vis, itr.first, dest, k, cost));

                vis[itr.first] = false;
                cost -= itr.second;
                k++;
            }
        }
        return mcost;
    }

    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dest, int K)
    {
        vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());

        for (int i = 0; i < flights.size(); i++)
            graph[flights[i][0]].push_back({flights[i][1], flights[i][2]});

        vector<bool> vis(n, false);
        vis[src] = true;
        mincost_dfs(graph, vis, src, dest, K + 1, 0);
        return mcost == INT_MAX ? -1 : mcost;
    }
};

// DAY 15(Search in Binary Search Tree)=================================================================

// Method 1 -> by declaring statically
TreeNode *node = nullptr;
void findnode(TreeNode *root, int val)
{
    if (root == nullptr)
        return;
    if (root->val == val)
    {
        node = root;
        return;
    }
    if (root->val < val)
        findnode(root->right, val);
    else if (root->val > val)
        findnode(root->left, val);
}

TreeNode *searchBST(TreeNode *root, int val)
{
    if (root == nullptr)
        return root;
    findnode(root, val);
    return node;
}

////////////////OR///////////////////

// Method 2 -> direct returning
TreeNode *searchBST(TreeNode *root, int val)
{
    if (root == nullptr || root->val == val)
        return root;
    if (root->val < val)
        return searchBST(root->right, val);
    else
        return searchBST(root->left, val);
    // return root;
}

// DAY 16(Validate IP Address)================================================================================

string validIPAddress(string IP)
{
    if (count(IP.begin(), IP.end(), '.') == 3)
    {
        if (IP[IP.size() - 1] == '.')
            return "Neither";
        stringstream ss(IP);
        string token;
        while (getline(ss, token, '.'))
        {
            if (token.length() == 0 || token.length() > 3)
                return "Neither";
            if (token[0] == '0' && token.length() != 1)
                return "Neither";
            for (char c : token)
                if (!isdigit(c))
                    return "Neither";
            if (stoi(token) < 0 || stoi(token) > 255)
                return "Neither";
        }
        return "IPv4";
    }
    else if (count(IP.begin(), IP.end(), ':') == 7)
    {
        if (IP[IP.size() - 1] == ':')
            return "Neither";
        stringstream ss(IP);
        string token;
        while (getline(ss, token, ':'))
        {
            if (token.length() == 0 || token.length() > 4)
                return "Neither";
            for (char c : token)
                if (!isxdigit(c))
                    return "Neither";
        }
        return "IPv6";
    }
    return "Neither";
}

// DAY 17(Surrounded Regions)==========================================================================

//Method 1(BFS)
//  this solution may give TLE
void bfs(int r, int c, int n, int m, vector<vector<char>> &board)
{
    queue<int> que;
    que.push(r * m + c);

    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!que.empty())
    {
        int rv = que.front();
        board[rv / m][rv % m] = '#';
        que.pop();

        for (int d = 0; d < 4; d++)
        {
            int i = rv / m + dir[d][0];
            int j = rv % m + dir[d][1];
            if (i != n && i != -1 && j != m && j != -1 && board[i][j] == 'O')
                que.push(i * m + j);
        }
    }
}

void solve(vector<vector<char>> &board)
{
    if (board.size() == 0)
        return;

    int n = board.size();
    int m = board[0].size();

    for (int j = 0; j < m; j++)
        if (board[0][j] == 'O')
            bfs(0, j, n, m, board);
    for (int j = 0; j < m; j++)
        if (board[n - 1][j] == 'O')
            bfs(n - 1, j, n, m, board);
    for (int i = 0; i < n; i++)
        if (board[i][0] == 'O')
            bfs(i, 0, n, m, board);
    for (int i = 0; i < n; i++)
        if (board[i][m - 1] == 'O')
            bfs(i, m - 1, n, m, board);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == '#')
                board[i][j] = 'O';
            else if (board[i][j] == 'O')
                board[i][j] = 'X';
}

// Method 2 (DFS)
void dfs(int r, int c, int n, int m, vector<vector<char>> &board)
{
    if (r == n || c == m || r == -1 || c == -1 || board[r][c] != 'O')
        return;

    board[r][c] = '#';

    dfs(r + 1, c, n, m, board);
    dfs(r - 1, c, n, m, board);
    dfs(r, c + 1, n, m, board);
    dfs(r, c - 1, n, m, board);
}

void solve(vector<vector<char>> &board)
{
    if (board.size() == 0)
        return;

    int n = board.size();
    int m = board[0].size();

    for (int j = 0; j < m; j++)
        if (board[0][j] == 'O')
            dfs(0, j, n, m, board);
    for (int j = 0; j < m; j++)
        if (board[n - 1][j] == 'O')
            dfs(n - 1, j, n, m, board);
    for (int i = 0; i < n; i++)
        if (board[i][0] == 'O')
            dfs(i, 0, n, m, board);
    for (int i = 0; i < n; i++)
        if (board[i][m - 1] == 'O')
            dfs(i, m - 1, n, m, board);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == '#')
                board[i][j] = 'O';
            else if (board[i][j] == 'O')
                board[i][j] = 'X';
}

//DAY 21(Permutation Sequence)====================================================================================

string kstr = "";
void kth_perm(int n, int &k, string que, string ans)
{
    if (que.size() == 0)
    {
        // cout<<ans<<endl;
        if (k-- == 1)
            kstr = ans;
        return;
    }
    // cout<<que<<endl;
    for (int i = 0; i < que.size(); i++)
        kth_perm(n, k, que.substr(0, i) + que.substr(i + 1), ans + que[i]);
}

string getPermutation(int n, int k)
{
    string s = "";
    for (int i = 1; i <= n; i++)
        s += to_string(i);
    // cout<<s;
    kth_perm(n, k, s, "");
    return kstr;
}