// DAY 2 (Course Schedule 3)======================================================================

// APPROACH 1 (Subsequence) --> <O(2^n)
// TLE

int subseq(int i, int day, vector<vector<int>> &v)
{
    if (i == v.size())
        return 0;

    int ans = 0;
    if (day + v[i][0] <= v[i][1])
        ans = subseq(i + 1, day + v[i][0], v) + 1;
    ans = max(ans, subseq(i + 1, day, v));

    return ans;
}

int scheduleCourse(vector<vector<int>> &courses)
{
    sort(courses.begin(), courses.end(), [](auto const &a, auto const &b) {
        return (a[1] == b[1]) ? a[0] < b[0] : a[1] < b[1];
    });
    return subseq(0, 0, courses);
}

// APPROACH 2 (Greedy -- Taking the minimum durations to maximize course count) --> O(n*logn)
// METHOD 1
// AC

int scheduleCourse(vector<vector<int>> &courses)
{
    sort(courses.begin(), courses.end(), [](auto const &a, auto const &b) {
        return (a[1] == b[1]) ? a[0] < b[0] : a[1] < b[1];
    });

    priority_queue<int> pq;
    int day = 0;
    for (vector<int> v : courses)
    {
        int dur = v[0], lim = v[1];
        if (day + dur <= lim)
        {
            day += dur;
            pq.push(dur);
        }
        else if (!pq.empty() && pq.top() > dur)
        {
            day += dur - pq.top();
            pq.pop();
            pq.push(dur);
        }
    }
    return pq.size();
}

// METHOD 2 (Shorter version of METHOD 1)

int scheduleCourse(vector<vector<int>> &courses)
{
    sort(courses.begin(), courses.end(), [](auto const &a, auto const &b) {
        return (a[1] == b[1]) ? a[0] < b[0] : a[1] < b[1];
    });

    priority_queue<int> pq;
    int day = 0;
    for (vector<int> v : courses)
    {
        int dur = v[0], lim = v[1];
        day += dur;
        pq.push(dur);
        if (day > lim)
        {
            day -= pq.top();
            pq.pop();
        }
    }
    return pq.size();
}

// DAY 3 (Running Sum of 1D Array)============================================

vector<int> runningSum(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); i++)
        nums[i] += nums[i - 1];
    return nums;
}

// DAY 4 (Non - Decreasing Array)=====================================================

// METHOD 1 (Comparing with Previous) --> O(n)
bool checkPossibility(vector<int> &nums)
{
    int n = nums.size();
    bool changed = false;
    int prev = nums[0];
    for (int i = 1; i < n; i++)
    {
        if (nums[i] >= prev)
        {
            prev = nums[i];
            continue;
        }
        if (changed)
            return false;
        changed = true;
        if (i - 2 == -1 || nums[i] >= nums[i - 2])
            prev = nums[i];
    }
    return true;
}

// DAY 5 (Jump Game 2)==================================================================

// APPROACH 1 (Using DP) --> O(n^2)

int jump(vector<int> &nums)
{
    int n = nums.size();
    vector<int> jumps(n, n);
    jumps[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--)
        for (int j = i + 1; j <= i + nums[i] && j < n; j++)
            jumps[i] = min(jumps[i], jumps[j] + 1);
    return jumps[0];
}

// APPROACH 2 (Storing max jumps at every "i" and updating total "jumps" whenever moves become 0) --> O(n)

int jump(vector<int> &nums)
{
    int n = nums.size();
    int jumps = 1;
    int jumplen = nums[0], moves = jumplen;
    for (int i = 1; i < n; i++)
    {
        if (i == n - 1)
            return jumps;
        jumplen = max(jumplen, i + nums[i]);
        if (--moves == 0)
        {
            moves = jumplen - i;
            jumps++;
        }
    }
    return 0;
}

// DAY 6 (Convert Sorted List to Binary Search Tree)===================================================

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    TreeNode *constructBST(int st, int end, vector<int> &arr)
    {
        if (st > end)
            return nullptr;
        if (st == end)
            return new TreeNode(arr[st]);
        int mid = (st + end) >> 1;
        return new TreeNode(arr[mid], constructBST(st, mid - 1, arr), constructBST(mid + 1, end, arr));
    }

    TreeNode *sortedListToBST(ListNode *head)
    {
        vector<int> arr;
        while (head)
        {
            arr.push_back(head->val);
            head = head->next;
        }
        return constructBST(0, arr.size() - 1, arr);
    }
};

// DAY 7 (Delete Operation of 2 Strings)==============================================

int minDistance(string word1, string word2)
{
    int n = word1.size(), m = word2.size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int a = (i - 1 >= 0) ? dp[i - 1][j] : 0;
            int b = (j - 1 >= 0) ? dp[i][j - 1] : 0;
            int c = (i - 1 >= 0 && j - 1 >= 0) ? dp[i - 1][j - 1] : 0;
            if (word1[i] == word2[j])
                dp[i][j] = c + 1;
            else
                dp[i][j] = max(a, b);
        }
    }
    int len = dp[n - 1][m - 1];
    return (n - len) + (m - len);
}