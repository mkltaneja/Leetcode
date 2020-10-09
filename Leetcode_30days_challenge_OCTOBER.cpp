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