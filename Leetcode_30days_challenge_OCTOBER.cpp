// $ DAY 1 (Number of Recent Calls)==========================================================

// METHOD 1 (Using vector)

class RecentCounter
{
public:
    vector<int> time;
    int i;

    RecentCounter()
    {
        this->i = 0;
    }

    int ping(int t)
    {
        time.push_back(t);
        while (time[i] < time.back() - 3000)
            i++;
        return time.size() - i;
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

////////////////////////////////////////////////////////OR//////////////////////////////////////////

// METHOD 2 (Using queue)
// Memory optimized
class RecentCounter
{
public:
    queue<int> time;
    int qsize;

    RecentCounter()
    {
        this->qsize = 0;
    }

    int ping(int t)
    {
        time.push(t);
        qsize++;
        while (time.front() < t - 3000)
        {
            time.pop();
            qsize--;
        }
        return qsize;
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

// $ DAY 2 (Combination Sum)=============================================================================

// Method 1 (Normal Method)
void combisum_rec(int idx, vector<int> &arr, int tar, vector<int> coins, vector<vector<int>> &ans)
{
    if (tar == 0)
    {
        ans.push_back(coins);
        return;
    }
    for (int i = idx; i < arr.size(); i++)
    {
        if (tar - arr[i] >= 0)
        {
            coins.push_back(arr[i]);
            combisum_rec(i, arr, tar - arr[i], coins, ans);
            coins.pop_back();
        }
    }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    vector<vector<int>> ans;
    combisum_rec(0, candidates, target, {}, ans);
    return ans;
}

// METHOD 2 (Subsequence)

void combisum_subseq(int idx, vector<int> &arr, int tar, vector<int> coins, vector<vector<int>> &ans)
{
    if (idx == arr.size())
    {
        if (tar == 0)
            ans.push_back(coins);
        return;
    }
    if (tar - arr[idx] >= 0)
    {
        coins.push_back(arr[idx]);
        combisum_subseq(idx, arr, tar - arr[idx], coins, ans);
        coins.pop_back();
    }

    combisum_subseq(idx + 1, arr, tar, coins, ans);
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    vector<vector<int>> ans;
    combisum_subseq(0, candidates, target, {}, ans);
    return ans;
}

// $ DAY 3 (K-diff Pairs in an Array)=============================================================================

int findPairs(vector<int> &nums, int k)
{
    map<int, vector<int>> m;
    for (int i = 0; i < nums.size(); i++)
    {
        m[nums[i]].push_back(i);
    }

    int count = 0;
    if (k == 0)
    {
        for (auto itr : m)
            if (itr.second.size() > 1)
                count++;
        return count;
    }
    unordered_map<int, int> unique;
    for (auto i : m)
        if (m.find(i.first + k) != m.end())
            unique.insert({i.first, i.first + k});
    return unique.size();
}

// DAY 4 (Remove Covered Intervals)=====================================================================

// METHOD 1 --> O(n^2)
int removeCoveredIntervals(vector<vector<int>> &intervals)
{
    int n = intervals.size();
    sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
    });
    // for(auto v : intervals)
    //     cout<<v[0]<<" "<<v[1]<<", ";
    // cout<<endl;
    int i = 0, count = 0;
    set<int> covered;

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (intervals[j][1] <= intervals[i][1])
                covered.insert(j);
    return n - covered.size();
}

///////////////////////////////////////////////OR////////////////////////////////////

// METHOD 2 --> O(n)

int removeCoveredIntervals(vector<vector<int>> &intervals)
{
    int n = intervals.size();
    sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
    });
    // for(auto v : intervals)
    //     cout<<v[0]<<" "<<v[1]<<", ";
    // cout<<endl;
    int start = intervals[0][0], end = intervals[0][1];
    int covered = 0;

    for (int i = 1; i < n; i++)
    {
        if (intervals[i][0] >= start && intervals[i][1] <= end)
            covered++;
        else
        {
            start = intervals[i][0];
            end = intervals[i][1];
        }
    }
    return n - covered;
}

// DAY 5 (Complement of Base 10 Integer)====================================================

int bitwiseComplement(int N)
{
    if (N == 0)
        return 1;
    int bits = 0;
    int n = N;
    while (n)
    {
        n >>= 1;
        bits++;
    }
    int i = 0, comp = 0;
    while (i < bits)
    {
        int pol = !(N & (1 << i));
        // cout<<pol<<" ";
        comp |= (pol << i++);
    }
    // cout<<endl;
    return comp;
}

// Method 2
int bitwiseComplement(int N)
{
    int mask = 1;
    while (mask < N)
    {
        mask = (mask << 1) + 1;
    }
    return N ^ mask;
}

// $ DAY 6 (Insert into a Binary Search Tree)====================================================================

TreeNode *insertIntoBST(TreeNode *root, int val)
{
    if (root == nullptr)
        return new TreeNode(val);
    if (root->val == val)
        return nullptr;

    if (root->val < val)
        root->right = insertIntoBST(root->right, val);
    else
        root->left = insertIntoBST(root->left, val);
    return root;
}

// $ DAY 7 (Rotate List)========================================================================

ListNode *rotateRight(ListNode *head, int k)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    int size = 0;
    ListNode *temp = head, *last = head;
    while (temp)
    {
        last = temp;
        temp = temp->next;
        size++;
    }
    k = k % size;
    // cout<<size<<" "<<k;
    if (k == 0)
        return head;
    ListNode *right = head, *prevright = head;
    int lsize = size - k;
    while (lsize--)
    {
        prevright = right;
        right = right->next;
    }
    prevright->next = nullptr;
    last->next = head;

    return right;
}

// $ DAY 8 (Binary Search)==================================================

// METHOD 1 --> O(n)
int search(vector<int> &nums, int target)
{
    for (int i = 0; i < nums.size(); i++)
        if (nums[i] == target)
            return i;
    return -1;
}

// METHOD 2 --> O(log n)
int search(vector<int> &nums, int target)
{
    int si = 0, ei = nums.size() - 1;
    while (si <= ei)
    {
        int mid = (si + ei) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] < target)
            si = mid + 1;
        else
            ei = mid - 1;
    }
    return -1;
}

// METHOD 3 --> O(n * logn) (using hashmap)

int search(vector<int> &nums, int target)
{
    map<int, int> m;
    for (int i = 0; i < nums.size(); i++)
        m[nums[i]] = i;
    return (m.find(target) != m.end()) ? m[target] : -1;
}

// DAY 9 (Serialize and Deserialize BST)==================================================================
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec
{
public:
    // Encodes a tree to a single string.
    void preoderenc(string &s, TreeNode *node)
    {
        if (node == nullptr)
            return;
        s += to_string(node->val) + "-";
        preoderenc(s, node->left);
        preoderenc(s, node->right);
    }
    string serialize(TreeNode *root)
    {
        string enc = "";
        preoderenc(enc, root);
        return enc;
    }

    // Decodes your encoded data to tree.
    TreeNode *insertNode(int val, TreeNode *root, string &data)
    {
        if (root == nullptr)
            return new TreeNode(val);
        if (root->val < val)
            root->right = insertNode(val, root->right, data);
        else
            root->left = insertNode(val, root->left, data);
        return root;
    }
    int tonum(string &s)
    {
        int num = 0;
        for (char c : s)
        {
            num *= 10;
            num += c - '0';
        }
        return num;
    }
    TreeNode *deserialize(string data)
    {
        // cout<<data<<endl;
        TreeNode *root = nullptr;
        stringstream ss(data);
        string temp;
        while (getline(ss, temp, '-'))
        {
            // cout<<temp<<endl;
            int num = tonum(temp);
            root = insertNode(num, root, data);
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;

// $ DAY 10 (Minimum Number of Arrows to Burst Balloons===========================================================================

int findMinArrowShots(vector<vector<int>> &points)
{
    if (points.size() == 0)
        return 0;
    sort(points.begin(), points.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
    });
    int lastend = points[0][1];
    int arrows = 0;
    for (int i = 1; i < points.size(); i++)
    {
        if (points[i][0] < lastend && points[i][1] < lastend)
            lastend = points[i][1];
        else if (points[i][0] > lastend)
        {
            arrows++;
            lastend = points[i][1];
        }
    }
    return arrows + 1;
}

// $ DAY 11 (Remove Duplicate Letters)========================================================

string removeDuplicateLetters(string s)
{
    vector<int> count(26);
    for (int i = 0; i < s.size(); i++)
        count[s[i] - 'a']++;
    string res = "";
    vector<bool> vis(26, false);
    for (char c : s)
    {
        count[c - 'a']--;
        if (vis[c - 'a'])
            continue;
        while (c < res.back() && count[res.back() - 'a'])
        {
            vis[res.back() - 'a'] = false;
            res.pop_back();
        }
        res += c;
        vis[c - 'a'] = true;
    }
    return res;
}

// $ DAY 12 (Buddy Strings)===================================================================

bool buddyStrings(string A, string B)
{
    if (A.size() != B.size())
        return false;
    vector<int> a(26, 0);
    vector<int> b(26, 0);
    for (char c : A)
        a[c - 'a']++;
    for (char c : B)
        b[c - 'a']++;
    if (A == B)
    {
        for (int count : a)
            if (count > 1)
                return true;
        return false;
    }
    int p1 = -1, p2 = -1;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] != B[i])
        {
            if (p1 == -1)
                p1 = i;
            else if (p2 == -1)
                p2 = i;
        }
    }
    if (p1 != -1 && p2 != -1)
        swap(A[p1], A[p2]);
    return A == B;
}

// $ DAY 13 (Sort List)=================================================================

// METHOD 1 (Using Double pointer - calling by reference)
ListNode *merge(ListNode *h1, ListNode *h2)
{
    if (!h1)
        return h2;
    if (!h2)
        return h1;
    ListNode *sorted = nullptr;
    if (h1->val < h2->val)
    {
        sorted = h1;
        sorted->next = merge(h1->next, h2);
    }
    else
    {
        sorted = h2;
        sorted->next = merge(h1, h2->next);
    }
    return sorted;
}

void mergesort(ListNode **headref)
{
    ListNode *head = *headref;
    if (!head || !head->next)
        return;
    ListNode *slow = head;
    ListNode *fast = head->next; // as it will give the previous of the mid to the "slow"
    while (fast && fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *h1 = head, *h2 = slow->next;
    slow->next = nullptr;

    mergesort(&h1);
    mergesort(&h2);
    *headref = merge(h1, h2);
}

ListNode *sortList(ListNode *head)
{
    if (!head || !head->next)
        return head;
    mergesort(&head);
    return head;
}

// METHOD 2 (Using Single Pointer)

ListNode *merge(ListNode *h1, ListNode *h2)
{
    if (!h1)
        return h2;
    if (!h2)
        return h1;
    ListNode *sorted = nullptr;
    if (h1->val < h2->val)
    {
        sorted = h1;
        sorted->next = merge(h1->next, h2);
    }
    else
    {
        sorted = h2;
        sorted->next = merge(h1, h2->next);
    }
    return sorted;
}

ListNode *getMid(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head->next; // as it will give the previous of the mid to the "slow"
    while (fast && fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode *sortList(ListNode *head)
{
    if (!head || !head->next)
        return head;

    ListNode *mid = getMid(head);
    ListNode *h1 = head, *h2 = mid->next;
    mid->next = nullptr;

    ListNode *nh1 = sortList(h1);
    ListNode *nh2 = sortList(h2);
    return merge(nh1, nh2);
}

// $ DAY 14 (House Robber 2)==============================================================

int maxrob(int si, int n, vector<int> &arr)
{
    int a = arr[si];
    if (n - si == 1)
        return a;
    int b = max(arr[si], arr[si + 1]);
    for (int i = si + 2; i < n; i++)
    {
        int temp = b;
        b = max(b, arr[i] + a);
        a = temp;
    }
    return b;
}

int rob(vector<int> &nums)
{
    int n = nums.size();
    if (n == 1)
        return nums[0];
    return max(maxrob(0, n - 1, nums), maxrob(1, n, nums));
}

// $ DAY 15 (Rotate Array)====================================================================

// METHOD 1 (Inserting in another array)
void rotate(vector<int> &nums, int k)
{
    int n = nums.size();
    k = k % n;
    vector<int> res;
    res.insert(res.begin(), nums.begin() + (n - k), nums.end());
    res.insert(res.begin() + k, nums.begin(), nums.begin() + (n - k));

    nums = res;
}

// $ DAY 16 (Search a 2D Matrix)==========================================================

// Method 1 (Binary Search) --> O(log(n*m))
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size();
    if (n == 0)
        return false;
    int m = matrix[0].size();
    int si = 0, ei = n * m - 1;

    while (si <= ei)
    {
        int mid = (si + ei) / 2;
        int r = mid / m;
        int c = mid % m;
        if (matrix[r][c] == target)
            return true;
        if (matrix[r][c] < target)
            si = mid + 1;
        else
            ei = mid - 1;
    }
    return false;
}

// METHOD 2 (Linear Search) --> O(n*m)
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size();
    if (n == 0)
        return false;
    int m = matrix[0].size();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (matrix[i][j] == target)
                return true;
    return false;
}

// METHOD 3 (MOST OPTIMIZED) --> O(n+m)

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size();
    if (n == 0)
        return false;
    int m = matrix[0].size();

    int r = 0, c = m - 1;
    while (r < n && c >= 0)
    {
        if (matrix[r][c] == target)
            return true;
        if (matrix[r][c] < target)
            r++;
        else
            c--;
    }
    return false;
}

// $ DAY 17 ()===================================================================

// APPROACH 1 --> O((n^2)*logn)
// TLE
vector<string> findRepeatedDnaSequences(string s)
{
    if (s.size() <= 10)
        return {};
    vector<string> ans;
    unordered_set<string> vis;
    for (int i = 0; i < s.size() - 10; i++)
    {
        string t = s.substr(i, 10);
        if (vis.find(t) != vis.end())
            continue;
        for (int j = i + 1; j <= s.size() - 10; j++)
        {
            if (s.substr(j, 10) == t)
            {
                ans.push_back(t);
                vis.insert(t);
                break;
            }
        }
    }
    return ans;
}

// APPROACH 2 --> O(10*n)
// AC
vector<string> findRepeatedDnaSequences(string s)
{
    if (s.size() <= 10)
        return {};
    vector<string> ans;
    unordered_map<string, int> mc;
    for (int i = 0; i <= s.size() - 10; i++)
    {
        string t = s.substr(i, 10);
        if (++mc[t] == 2)
            ans.push_back(t);
    }
    return ans;
}