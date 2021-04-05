
// DAY 1 (Palindrome Linked List)===============================================================

// METHOD 1 (Using Extra Space (Stack))
bool isPalindrome(ListNode *head)
{
    int n = 0;
    ListNode *itr = head;
    while (itr)
    {
        n++;
        itr = itr->next;
    }
    int i = 0;
    ListNode *tmp = head;
    stack<int> st;
    while (i++ < n / 2)
    {
        st.push(tmp->val);
        tmp = tmp->next;
    }

    if (n & 1)
        tmp = tmp->next;
    while (tmp && !st.empty())
    {
        if (tmp->val != st.top())
            return false;
        tmp = tmp->next;
        st.pop();
    }
    return (st.empty() && !tmp);
}

// METHOD 2 (Const Extra Space) -- (By reversing the lower half of LL)

bool isPalindrome(ListNode *head)
{
    int n = 0;
    ListNode *itr = head;
    while (itr)
    {
        n++;
        itr = itr->next;
    }
    int i = 0;
    ListNode *tmp = head;
    ListNode *curr = head, *prev = nullptr, *forw = head;

    while (i++ < n / 2)
    {
        tmp = tmp->next;
        forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    ListNode *tmp1 = prev;

    if (n & 1)
        tmp = tmp->next;
    while (tmp && tmp1)
    {
        // cout<<tmp->val<<" "<<tmp1->val;
        if (tmp->val != tmp1->val)
            return false;
        tmp = tmp->next;
        tmp1 = tmp1->next;
    }
    return (!tmp && !tmp1);
}

// DAY 2 (Ones and Zeros)====================================================================

// APPROACH 1 (Subsequence Method) --> O(2^n)
// TLE
int subseq(int i, vector<pair<int, int>> &v01, int n, int m)
{
    if (i == v01.size())
        return 0;

    int ans = 0;
    if (n - v01[i].first >= 0 && m - v01[i].second >= 0)
        ans = subseq(i + 1, v01, n - v01[i].first, m - v01[i].second) + 1;
    ans = max(ans, subseq(i + 1, v01, n, m));

    return ans;
}

int findMaxForm(vector<string> &strs, int m, int n)
{
    int sz = strs.size();
    cout << sz << endl;
    vector<pair<int, int>> v01(sz);
    for (int i = 0; i < sz; i++)
    {
        int c0 = 0, c1 = 0;
        for (char c : strs[i])
        {
            if (c == '0')
                c0++;
            else
                c1++;
        }
        v01[i] = {c0, c1};
    }

    return subseq(0, v01, m, n);
}

// METHOD 2 (3D - DP)
// AC

int subseq(int i, vector<pair<int, int>> &v01, int m, int n, vector<vector<vector<int>>> &dp)
{
    if (i == v01.size())
        return dp[i][m][n] = 0;
    if (dp[i][m][n] != -1)
        return dp[i][m][n];
    int ans = 0;
    if (m - v01[i].first >= 0 && n - v01[i].second >= 0)
        ans = subseq(i + 1, v01, m - v01[i].first, n - v01[i].second, dp) + 1;
    ans = max(ans, subseq(i + 1, v01, m, n, dp));

    return dp[i][m][n] = ans;
}

int findMaxForm(vector<string> &strs, int m, int n)
{
    int sz = strs.size();
    // cout<<sz<<endl;
    vector<pair<int, int>> v01(sz);
    for (int i = 0; i < sz; i++)
    {
        int c0 = 0, c1 = 0;
        for (char c : strs[i])
        {
            if (c == '0')
                c0++;
            else
                c1++;
        }
        v01[i] = {c0, c1};
    }

    vector<vector<vector<int>>> dp(sz + 1, (vector<vector<int>>(m + 1, vector<int>(n + 1, -1))));
    return subseq(0, v01, m, n, dp);
}

// DAY 3 (Longest Valid Parenthesis)===================================================================================

// METHOD 1 (Using Stack of pair)
int longestValidParentheses(string s)
{
    stack<pair<int, int>> st;
    int ans = 0, len = 0, plen = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            st.push({i, plen});
            plen = 0;
        }
        else
        {
            if (st.empty())
            {
                plen = 0;
                continue;
            }
            len = (i - st.top().first + 1) + st.top().second;
            ans = max(ans, len);
            plen = len;
            st.pop();
        }
    }
    return ans;
}

// METHOD 2 (SHORTER, CONCISE AND OPTIMIZED WAY)

int longestValidParentheses(string s)
{
    stack<int> st;
    st.push(-1);
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
            st.push(i);
        else
        {
            if (!st.empty())
                st.pop();
            if (st.empty())
                st.push(i);
            else
                ans = max(ans, i - st.top());
        }
    }
    return ans;
}

// DAY 4 (Design Circular Queue)========================================================
class MyCircularQueue
{
public:
    vector<int> arr;
    int n;
    int si, ei;
    MyCircularQueue(int k)
    {
        arr.reserve(k);
        si = -1, ei = -1;
        n = k;
    }

    bool enQueue(int value)
    {
        if ((ei + 1) % n == si)
            return false;
        if (si == -1)
            si++;
        ei = (ei + 1) % n;
        arr[ei] = value;
        return true;
    }

    bool deQueue()
    {
        if (si == -1)
            return false;
        if (si == ei)
            si = -1, ei = -1;
        else
            si = (si + 1) % n;
        return true;
    }

    int Front()
    {
        return (si == -1) ? -1 : arr[si];
    }

    int Rear()
    {
        return (ei == -1) ? -1 : arr[ei];
    }

    bool isEmpty()
    {
        return (si == -1);
    }

    bool isFull()
    {
        return ((ei + 1) % n == si);
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

// DAY 5 (Global and Local Inversions)=====================================================

// APPROACH 1 (Brute Force)
// TLE

bool isIdealPermutation(vector<int> &A)
{
    int n = A.size();
    int a = A[0], b = A[1];
    for (int i = 0; i < n - 2; i++)
        for (int j = i + 2; j < n; j++)
            if (A[j] < A[i])
                return false;
    return true;
}