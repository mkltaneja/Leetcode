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

// DAY 12 (Check If a String Contains All Binary Codes of Size K)=========================================================================

// METHOD 1 (Using bitset<>)
bool hasAllCodes(string s, int k)
{
    int n = s.size();
    bitset<10000000> f;
    int num = 0, p = (1 << k);
    for (int i = 0; i < n; i++)
    {
        num = num * 2 + (s[i] - '0');
        if (i >= k)
            num -= (s[i - k] - '0') * p;
        if (i >= k - 1)
            f.set(num);
    }
    for (int i = 0; i < p; i++)
        if (!f.test(i))
            return false;
    return true;
}

// METHOD 2 (Different way) --> OPTIMIZED

bool hasAllCodes(string s, int k)
{
    int n = s.size();
    int num = stoi(s.substr(0, k), 0, 2);
    vector<bool> set((1 << k), false);
    int count = 0;
    for (int i = k; i <= n; i++)
    {
        count += 1 - set[num];
        set[num] = true;
        if (i == n)
            break;
        num &= ~(1 << (k - 1));
        num = (num << 1) | (s[i] - '0');
    }
    // cout<<count<<endl;
    return count == (1 << k);
}

// DAY 13 (Binary Tres with Factors)==================================================================================

int mod = 1000000007;
#define ll long long int
int numFactoredBinaryTrees(vector<int> &arr)
{
    ll ans = 0;
    int n = arr.size();
    unordered_map<int, ll> m;
    sort(arr.begin(), arr.end());

    for (int x : arr)
    {
        double maxi = sqrt(x);
        ll ways = 1;
        for (int i = 0; arr[i] <= maxi; i++)
        {
            if (x % arr[i] != 0)
                continue;
            ways += m[arr[i]] * m[x / arr[i]] * (arr[i] == x / arr[i] ? 1 : 2);
        }
        m[x] = ways;
        ans = (ans + ways) % mod;
    }

    return ans;
}

// DAY 14 (Swapping Nodes in a Linked List)===============================================================================

ListNode *swapNodes(ListNode *head, int k)
{
    int n = 0;
    ListNode *itr = head;
    while (itr)
    {
        itr = itr->next;
        n++;
    }
    k %= (n + 1);
    int kk = n - k + 1;
    // cout<<k<<" "<<kk<<endl;
    ListNode *a = head, *b = head;
    while (--k)
        a = a->next;
    while (--kk)
        b = b->next;
    swap(a->val, b->val);
    return head;
}

// DAY 15 (Encode and Decode TinyURL)======================================================================
class Solution
{
private:
    unordered_map<string, string> long_to_short;
    unordered_map<string, string> short_to_long;

public:
    // Encodes a URL to a shortened URL.
    string encode(string longUrl)
    {
        if (long_to_short.count(longUrl))
            return long_to_short[longUrl];
        string dict = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
        string res = "";
        while (res.empty())
        {
            for (int i = 0; i < 6; i++)
                res += dict[rand() % 62];
            if (short_to_long.count(res))
                res.clear();
        }
        long_to_short[longUrl] = res;
        short_to_long[res] = longUrl;
        return long_to_short[longUrl];
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl)
    {
        return short_to_long[shortUrl];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));

// DAY 16 (Best Time to Buy and Sell Stock with Transaction Fee)===========================================================================

// METHOD 1 (DP --> Keeping the maximum profit for buy and sell stored)
int maxProfit(vector<int> &prices, int fee)
{
    int n = prices.size();
    vector<int> buy(n), sell(n);
    buy[0] = -prices[0], sell[0] = 0;
    for (int i = 1; i < n; i++)
    {
        buy[i] = max(buy[i - 1], sell[i - 1] - prices[i]);
        sell[i] = max(sell[i - 1], buy[i - 1] + (prices[i] - fee));
    }
    return sell[n - 1];
}

// METHOD 2 (Space OPTIMIZED)

int maxProfit(vector<int> &prices, int fee)
{
    int n = prices.size();
    int buy = -prices[0], sell = 0;
    for (int i = 1; i < n; i++)
    {
        buy = max(buy, sell - prices[i]);
        sell = max(sell, buy + (prices[i] - fee));
    }
    return sell;
}

// DAY 17 (Generate Random Points in a Circle)==========================================================
class Solution
{
public:
    double R, X, Y;
    Solution(double radius, double x_center, double y_center)
    {
        srand(time(0));
        this->R = radius;
        this->X = x_center;
        this->Y = y_center;
    }

    double random()
    {
        return (double)rand() / RAND_MAX;
    }

    vector<double> randPoint()
    {
        // cout<<random()<<endl;
        double r = sqrt(random()) * R;
        double deg = random() * 2 * M_PI;
        vector<double> ans = {X + r * cos(deg), Y + r * sin(deg)};
        return ans;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj->randPoint();
 */

// DAY 18 (Wiggle Sequence)========================================================================

// METHOD 1 (DP -- Storing ups and downs till ith position)
int wiggleMaxLength(vector<int> &nums)
{
    int n = nums.size();
    vector<int> up(n), down(n);
    up[0] = down[0] = 1;
    for (int i = 1; i < n; i++)
    {
        if (nums[i] > nums[i - 1])
        {
            up[i] = down[i - 1] + 1;
            down[i] = down[i - 1];
        }
        else if (nums[i] < nums[i - 1])
        {
            down[i] = up[i - 1] + 1;
            up[i] = up[i - 1];
        }
        else
        {
            up[i] = up[i - 1];
            down[i] = down[i - 1];
        }
        // cout<<nums[i]<<" --> "<<up[i]<<" "<<down[i]<<endl;
    }
    return max(up[n - 1], down[n - 1]);
}

// METHOD 2 (Space OPTIMIZED)

int wiggleMaxLength(vector<int> &nums)
{
    int n = nums.size();
    bool up = true, down = true;
    int ans = 1;
    for (int i = 1; i < n; i++)
    {
        if (nums[i] > nums[i - 1] && up)
        {
            ans++;
            down = true;
            up = false;
        }
        else if (nums[i] < nums[i - 1] && down)
        {
            ans++;
            down = false;
            up = true;
        }
    }
    return ans;
}

// DAY 19 (Keys and Rooms)====================================================================================

void dfs(int i, vector<vector<int>> &rooms, vector<bool> &vis)
{
    vis[i] = true;
    for (int j : rooms[i])
        if (!vis[j])
            dfs(j, rooms, vis);
}

bool canVisitAllRooms(vector<vector<int>> &rooms)
{
    int n = rooms.size();
    vector<bool> vis(n, false);
    dfs(0, rooms, vis);
    for (bool f : vis)
        if (!f)
            return false;
    return true;
}

// DAY 20 (Design Underground System)============================================================

class UndergroundSystem
{
private:
    unordered_map<int, pair<string, int>> chin;
    unordered_map<string, pair<int, int>> time;

public:
    UndergroundSystem()
    {
    }

    void checkIn(int id, string stationName, int t)
    {
        chin[id] = {stationName, t};
    }

    void checkOut(int id, string stationName, int t)
    {
        string stats = chin[id].first + " " + stationName;
        time[stats].first += t - chin[id].second;
        time[stats].second++;
    }

    double getAverageTime(string startStation, string endStation)
    {
        auto ttime = time[startStation + " " + endStation];
        return 1.0 * ttime.first / ttime.second;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */

// DAY 21 (Rordered Power of 2)============================================================================

// APPROACH 1 (By making all permutations of the given number and checking if it's the pow of 2) --> O(n^n) [n = N.size()]

bool pow2(int n)
{
    return n && !(n & (n - 1));
}

bool checkdigs(int idx, int n, vector<int> &dig, vector<bool> &vis)
{
    // cout<<dig[0]<<endl;
    if (idx == dig.size())
    {
        // cout<<n<<endl;
        if (pow2(n))
            return true;
        return false;
    }
    for (int i = 0; i < dig.size(); i++)
    {
        if (!vis[i] && (n > 0 || dig[i] != 0))
        {
            vis[i] = true;
            if (checkdigs(idx + 1, n * 10 + dig[i], dig, vis))
                return true;
            vis[i] = false;
        }
    }

    return false;
}

bool reorderedPowerOf2(int N)
{
    vector<int> dig;
    int nn = N;
    while (nn)
    {
        dig.push_back(nn % 10);
        nn /= 10;
    }
    vector<bool> vis(dig.size(), false);
    return checkdigs(0, 0, dig, vis);
}

// APPROACH 2 (starting i from 1 till n increasing by factor of 2 and checking if map of N and i are same) --> O(logN)

void count(int n, unordered_map<int, int> &m)
{
    while (n)
    {
        m[n % 10]++;
        n /= 10;
    }
}

bool reorderedPowerOf2(int N)
{
    string s = to_string(N);
    unordered_map<int, int> mn;
    count(N, mn);
    int pow2 = 1;
    for (int i = 0; i < 31; i++)
    {
        string t = to_string(pow2);
        if (t.size() > s.size())
            break;
        if (t.size() == s.size())
        {
            unordered_map<int, int> mi;
            count(pow2, mi);
            if (mn == mi)
                return true;
        }
        pow2 <<= 1;
    }
    return false;
}

// DAY 22 (Vowel Spellchecker)======================================================================

bool isvowel(char c)
{
    c = tolower(c);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return true;
    return false;
}

vector<string> spellchecker(vector<string> &wordlist, vector<string> &queries)
{
    unordered_map<string, int> mcap;
    unordered_map<string, int> mvow;
    unordered_set<string> ss;
    for (int i = 0; i < wordlist.size(); i++)
    {
        string s = wordlist[i];
        ss.insert(s);
        string tmp1 = "";
        string tmp2 = "";
        for (char c : s)
        {
            tmp1 += tolower(c);
            if (isvowel(c))
                tmp2 += "a";
            else
                tmp2 += tolower(c);
        }
        if (mcap.count(tmp1) == 0)
            mcap[tmp1] = i;
        if (mvow.count(tmp2) == 0)
            mvow[tmp2] = i;
    }

    vector<string> ans(queries.size());
    for (int i = 0; i < queries.size(); i++)
    {
        string s = queries[i];
        if (ss.count(s))
        {
            ans[i] = s;
            continue;
        }
        string tmp1 = "";
        string tmp2 = "";
        for (char c : s)
        {
            tmp1 += tolower(c);
            if (isvowel(c))
                tmp2 += "a";
            else
                tmp2 += tolower(c);
        }
        if (mcap.count(tmp1))
            ans[i] = wordlist[mcap[tmp1]];
        else if (mvow.count(tmp2))
            ans[i] = wordlist[mvow[tmp2]];
        else
            ans[i] = "";
    }

    return ans;
}

// DAY 23 (3 Sum with Multiplicity)===============================================================================

int mod = (1e9 + 7);
#define f first
#define s second
int threeSumMulti(vector<int> &arr, int target)
{
    unordered_map<char, long> m;
    for (int x : arr)
        m[x]++;
    long ans = 0;
    for (auto p1 : m)
    {
        for (auto p2 : m)
        {
            int x = target - p1.f - p2.f;
            if (!m.count(x))
                continue;
            if (p1.f == p2.f && p1.f == x)
                ans += (p1.s * (p1.s - 1) * (p1.s - 2)) / 6;
            else if (p1.f == p2.f)
                ans += (m[x] * p1.s * (p1.s - 1)) / 2;
            else if (p1.f < p2.f && p2.f < x)
                ans += m[x] * p1.s * p2.s;
        }
    }
    return ans % mod;
}

// DAY 24 (Advantage Shuffle)=============================================================

#define f first
#define s second
vector<int> advantageCount(vector<int> &A, vector<int> &B)
{
    int n = A.size();
    vector<pair<int, int>> a(n), b(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = {A[i], i};
        b[i] = {B[i], i};
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> ans(n, -1);
    vector<int> tmp;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i].f > b[j].f)
            ans[b[j++].s] = a[i].f;
        else
            tmp.push_back(a[i].f);
    }
    int i = 0;
    while (j < n)
        ans[b[j++].s] = tmp[i++];

    return ans;
}

// DAY 26 (Word Subsets)=====================================================================================

vector<string> wordSubsets(vector<string> &A, vector<string> &B)
{
    int mb[26] = {0};
    for (string s : B)
    {
        int m[26] = {0};
        for (char c : s)
            m[c - 'a']++;
        for (int i = 0; i < 26; i++)
            mb[i] = max(mb[i], m[i]);
    }

    vector<string> ans;
    for (string s : A)
    {
        int ma[26] = {0};
        for (char c : s)
            ma[c - 'a']++;
        bool flag = true;
        // cout<<s<<": \n";
        for (int i = 0; i < 26; i++)
        {
            // cout<<(char)(i+'a')<<" -  "<<ma[i]<<" "<<mb[i]<<endl;
            if (ma[i] < mb[i])
            {
                flag = false;
                break;
            }
        }
        // cout<<endl;
        if (flag)
            ans.push_back(s);
    }

    return ans;
}