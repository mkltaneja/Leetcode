// DAY 1 (Distribute Candies)=============================================================

// METHOD 1 (Using Set) --> O(n*logn)
int distributeCandies(vector<int> &candyType)
{
    int n = candyType.size();
    unordered_set<int> s;
    for (int x : candyType)
        s.insert(x);
    return (s.size() < n / 2) ? s.size() : n / 2;
}

// METHOD 2 (Using Bitset) --> O(n)

int distributeCandies(vector<int> &candyType)
{
    int n = candyType.size();
    bitset<200005> f;
    for (int x : candyType)
        f.set(x + 100000);
    int count = f.count();
    // cout<<count<<endl;
    return (count < n / 2) ? count : n / 2;
}

// DAY 2 (Set Mismatch)===============================================================

vector<int> findErrorNums(vector<int> &nums)
{
    vector<int> cnt(nums.size(), 0);
    for (int x : nums)
        cnt[x - 1]++;
    vector<int> ans(2);
    for (int i = 0; i < cnt.size(); i++)
        if (cnt[i] == 2)
            ans[0] = i + 1;
        else if (cnt[i] == 0)
            ans[1] = i + 1;
    return ans;
}

// DAY 3 (Missing Number)===========================================================

// METHOD 1 (Using Array)
int missingNumber(vector<int> &nums)
{
    int n = nums.size();
    vector<int> a(n + 1, 0);
    for (int x : nums)
        a[x] = 1;
    for (int i = 0; i <= n; i++)
        if (!a[i])
            return i;
    return -1;
}

// METHOD 2 (Without Extra space)

int missingNumber(vector<int> &nums)
{
    int n = nums.size();
    int sum = 0;
    for (int x : nums)
        sum += x;
    return (n * (n + 1)) / 2 - sum;
}

// DAY 4 (Intersection of 2 Linked Lists)=============================================================================

// APPROACH 1 (Using Cycle property of Linked list) --> O(n)
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    ListNode *t1 = headA;
    if (!headA || !headB)
        return nullptr;

    while (t1->next)
        t1 = t1->next;
    t1->next = headB;
    ListNode *s = headA, *f = headA;
    while (f->next && f->next->next)
    {
        s = s->next;
        f = f->next->next;
        if (s == f)
            break;
    }
    if (!f->next || !f->next->next)
    {
        t1->next = nullptr;
        return nullptr;
    }
    s = headA;
    while (f != s)
    {
        f = f->next;
        s = s->next;
    }
    // cout<<s->val<<" "<<f->val<<endl;
    t1->next = nullptr;
    return f;
}

// APPROACH 2 (Using 2 pointer approach) --> >O(n)

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    ListNode *t1 = headA, *t2 = headB;
    while (t1 != t2)
    {
        t1 = t1 ? t1->next : headB;
        t2 = t2 ? t2->next : headA;
    }
    return t1;
}

// DAY 5 (Average of Levles in Binary Tree)===========================================================

vector<double> averageOfLevels(TreeNode *root)
{
    queue<TreeNode *> que;
    que.push(root);
    vector<double> ans;
    while (!que.empty())
    {
        int sz = que.size();
        int count = sz;
        long long int sum = 0;
        while (sz--)
        {
            TreeNode *node = que.front();
            que.pop();
            sum += node->val;
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
        ans.push_back(1.0 * sum / count);
    }
    return ans;
}

// DAY 6 (Short Encoding of Words)========================================================

int minimumLengthEncoding(vector<string> &words)
{
    for (string &word : words)
        reverse(word.begin(), word.end());
    sort(words.begin(), words.end());
    // for(string word : words)
    //     cout<<word<<" ";
    // cout<<endl;

    int len = 0;
    int i = 0, n = words.size();
    while (i < n)
    {
        while (i + 1 < n && words[i + 1].substr(0, words[i].size()) == words[i])
            i++;
        len += words[i++].size() + 1;
    }
    return len;
}

// DAY 7 (Design HashMap)===========================================================================

// METHOD 1 (Hashing Style 1 -> making array of array of pairs, and sorting the 2nd dimension array everytime) --> O(m*logm) (m = no. of same (key%n))
// AC
class MyHashMap
{
private:
    int n;
    vector<vector<pair<int, int>>> bucket;
    // bool count = true;
public:
    /** Initialize your data structure here. */
    MyHashMap()
    {
        // cout<<(boolalpha)<<count<<endl;
        this->n = 1000;
        this->bucket.assign(n, vector<pair<int, int>>());
    }

    int find(vector<pair<int, int>> &arr, int val)
    {
        int si = 0, ei = arr.size() - 1;
        while (si <= ei)
        {
            int mid = (si + ei) >> 1;
            if (arr[mid].first == val)
                return mid;
            if (arr[mid].first < val)
                si = mid + 1;
            else
                ei = mid - 1;
        }
        return -1;
    }

    /** value will always be non-negative. */
    void put(int key, int value)
    {
        int idx = key % n;
        int foundi = find(bucket[idx], key);
        // cout<<foundi<<endl;
        if (foundi == -1)
        {
            bucket[idx].push_back({key, value});
            sort(bucket[idx].begin(), bucket[idx].end());
            // cout<<bucket[idx].size()<<endl;
        }
        else
            bucket[idx][foundi].second = value;
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key)
    {
        int idx = key % n;
        int foundi = find(bucket[idx], key);
        return foundi == -1 ? -1 : bucket[idx][foundi].second;
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key)
    {
        int idx = key % n;
        int foundi = find(bucket[idx], key);
        if (foundi != -1)
            bucket[idx].erase(bucket[idx].begin() + foundi);
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

// METHOD 2 (Actual Implementation) (Allocating the space in a normal 2D array according to the given maximum size of key) --> O(1)
// AC

class MyHashMap
{
private:
    int n;
    vector<vector<int>> bucket;

public:
    /** Initialize your data structure here. */
    MyHashMap()
    {
        this->n = 1000;
        this->bucket.assign(n, vector<int>());
    }

    /** value will always be non-negative. */
    void put(int key, int value)
    {
        if (bucket[key / n].empty())
            bucket[key / n].resize(n, -1);
        bucket[key / n][key % n] = value;
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key)
    {
        if (bucket[key / n].empty() || bucket[key / n][key % n] == -1)
            return -1;
        return bucket[key / n][key % n];
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key)
    {
        if (!bucket[key / n].empty() && bucket[key / n][key % n] != -1)
            bucket[key / n][key % n] = -1;
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

// DAY 8 (Remove Palindromic Subsequences)============================================================================

// APPROACH 1 (In General Approach - for any no. of distinct characters)
// TLE
#define f first
#define s second

vector<int> longest_ps(string &s)
{
    int n = s.size();
    vector<vector<pair<int, vector<int>>>> dp(n, vector<pair<int, vector<int>>>(n, {0, vector<int>()}));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
            {
                dp[i][j].f = 1;
                dp[i][j].s.push_back(i);
                continue;
            }
            int pre = dp[i + 1][j].f;
            int suf = dp[i][j - 1].f;
            int mid = dp[i + 1][j - 1].f + ((s[i] == s[j]) ? 2 : 0);
            int maxi = 0;
            if (mid > maxi)
            {
                maxi = mid;
                dp[i][j].f = mid;
                dp[i][j].s = dp[i + 1][j - 1].s;
                if (s[i] != s[j])
                    continue;
                dp[i][j].s.push_back(i);
                dp[i][j].s.push_back(j);
            }
            if (pre > maxi)
            {
                maxi = pre;
                dp[i][j].f = pre;
                dp[i][j].s = dp[i + 1][j].s;
            }
            if (suf > maxi)
            {
                maxi = suf;
                dp[i][j].f = suf;
                dp[i][j].s = dp[i][j - 1].s;
            }
        }
    }
    return dp[0][n - 1].s;
}

int removePalindromeSub(string s)
{
    int count = 0;
    while (!s.empty())
    {
        auto v = longest_ps(s);
        sort(v.begin(), v.end());
        // for(int x : v)
        //     cout<<x<<" ";
        string temp = "";
        int k = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (k < v.size() && i == v[k])
                k++;
            else
                temp += s[i];
        }
        // cout<<s<<" - "<<temp<<endl;
        s = temp;
        count++;
    }
    // cout<<endl;
    return count > 2 ? 2 : count;
}

// APPROAH 2 (Actual Approach -- with 2 characters included)

bool ispal(string &s)
{
    int n = s.size();
    for (int i = 0; i < n / 2; i++)
        if (s[i] != s[n - i - 1])
            return false;
    return true;
}
int removePalindromeSub(string s)
{
    if (s.empty())
        return 0;
    if (ispal(s))
        return 1;
    return 2;
}

// DAY 9 (Add One Row to Tree)===============================================================================

void addRow(TreeNode *node, int v, int d)
{
    if (!node)
        return;
    if (d == 2)
    {
        TreeNode *l = new TreeNode(v, node->left, nullptr);
        TreeNode *r = new TreeNode(v, nullptr, node->right);
        node->left = nullptr;
        node->right = nullptr;
        node->left = l;
        node->right = r;
        return;
    }
    addRow(node->left, v, d - 1);
    addRow(node->right, v, d - 1);
}

TreeNode *addOneRow(TreeNode *root, int v, int d)
{
    TreeNode *nnode = new TreeNode(v);
    if (d == 1)
        return new TreeNode(v, root, nullptr);

    addRow(root, v, d);
    return root;
}

// DAY 10 (Integer to Roman)=====================================================

// APPROACH 1 (Using extra space)
string intToRoman(int num)
{
    unordered_map<int, string> m;
    m[1] = "I", m[5] = "V", m[10] = "X", m[50] = "L", m[100] = "C", m[500] = "D", m[1000] = "M";
    vector<string> ans(4);
    int i = 3;
    int p = 1;
    while (num)
    {
        int x = (num % 10);
        if (x == 4 || x == 9)
            ans[i] = m[p] + m[(x * p) + p];
        else
        {
            if (x >= 5)
                ans[i] = m[x * p - (x % 5) * p];
            while (x-- % 5)
                ans[i] += m[p];
        }
        i--;
        p *= 10;
        num /= 10;
    }
    string res = "";
    for (string s : ans)
        res += s;
    return res;
}

// APPROACH 2 (Space and time optimized)

string intToRoman(int num)
{
    string ans = "";
    while (num)
    {
        if (num >= 1000)
        {
            num -= 1000;
            ans += "M";
        }
        else if (num >= 900)
        {
            num -= 900;
            ans += "CM";
        }
        else if (num >= 500)
        {
            num -= 500;
            ans += "D";
        }
        else if (num >= 400)
        {
            num -= 400;
            ans += "CD";
        }
        else if (num >= 100)
        {
            num -= 100;
            ans += "C";
        }
        else if (num >= 90)
        {
            num -= 90;
            ans += "XC";
        }
        else if (num >= 50)
        {
            num -= 50;
            ans += "L";
        }
        else if (num >= 40)
        {
            num -= 40;
            ans += "XL";
        }
        else if (num >= 10)
        {
            num -= 10;
            ans += "X";
        }
        else if (num >= 9)
        {
            num -= 9;
            ans += "IX";
        }
        else if (num >= 5)
        {
            num -= 5;
            ans += "V";
        }
        else if (num >= 4)
        {
            num -= 4;
            ans += "IV";
        }
        else if (num >= 1)
        {
            num -= 1;
            ans += "I";
        }
    }
    return ans;
}

// DAY 11 (Coin Change)==============================================================================

// APPROACH 1 (DP) --> o(amount*n)
int coinChange(vector<int> &coins, int amount)
{
    int n = coins.size();
    vector<vector<int>> dp(amount + 1, vector<int>(n + 1, INT_MAX));
    for (int i = 0; i <= amount; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == 0)
            {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = ((i - coins[j - 1]) >= 0 && dp[i - coins[j - 1]][j] != INT_MAX) ? min(dp[i][j - 1], dp[i - coins[j - 1]][j] + 1) : dp[i][j - 1];
        }
    }
    return (dp[amount][n] == INT_MAX) ? -1 : dp[amount][n];
}

// APPROACH 2 (Sorting the array initially to make Pro-active calls during recursion) --> <<O(amount*n)

void dfs(int idx, int amount, int cnt, vector<int> &coins, int &ans)
{
    if (amount == 0)
    {
        ans = cnt;
        return;
    }
    if (idx == coins.size())
        return;
    for (int i = amount / coins[idx]; i >= 0 && cnt + i < ans; i--)
        dfs(idx + 1, amount - (i * coins[idx]), cnt + i, coins, ans);
}

int coinChange(vector<int> &coins, int amount)
{
    sort(coins.rbegin(), coins.rend());
    int ans = amount + 1;
    dfs(0, amount, 0, coins, ans);
    return (ans == amount + 1) ? -1 : ans;
}