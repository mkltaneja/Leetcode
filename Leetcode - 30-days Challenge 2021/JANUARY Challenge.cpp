
// DAY 1 (Check Array Formation Through Concatenation)==============================================================

bool canFormArray(vector<int> &arr, vector<vector<int>> &pieces)
{
    vector<int> indices(101, -1);
    for (int i = 0; i < arr.size(); i++)
        indices[arr[i]] = i;

    for (int i = 0; i < pieces.size(); i++)
        for (int j = 0; j < pieces[i].size(); j++)
            if (indices[pieces[i][j]] == -1)
                return false;

    for (vector<int> v : pieces)
    {
        int i = indices[v[0]];
        for (int x : v)
        {
            if (i != indices[x])
                return false;
            i++;
        }
    }
    return true;
}

// DAY 2 (Find a Corresponding Node of a Binary Tree in a Clone of That Tree)===========================================================

TreeNode *getTargetCopy(TreeNode *original, TreeNode *cloned, TreeNode *target)
{
    if (!cloned)
        return nullptr;
    if (cloned->val == target->val)
        return cloned;
    TreeNode *left = getTargetCopy(original, cloned->left, target);
    if (left)
        return left;
    TreeNode *right = getTargetCopy(original, cloned->right, target);
    if (right)
        return right;

    return nullptr;
}

// DAY 3 (Beautiful Arrangement)==============================================================================

// METHOD 1 (Recursion from start of array -- Takes more time)
int permutations(int idx, vector<int> &arr)
{
    if (idx == arr.size())
        return 1;

    int count = 0;
    for (int i = idx; i < arr.size(); i++)
    {
        swap(arr[i], arr[idx]);
        if (max(arr[idx], idx + 1) % min(arr[idx], idx + 1) == 0)
            count += permutations(idx + 1, arr);
        swap(arr[i], arr[idx]);
    }
    return count;
}

int countArrangement(int n)
{
    vector<int> arr(n);
    for (int i = 1; i <= n; i++)
        arr[i - 1] = i;
    return permutations(0, arr);
}

// METHOD 2 (Recursion from end of array -- MUCH faster than METHOD 1 because geater elements pose more constraints
//                                                                            on what arr[i] can fit and thus remove invalid cases
// OPTIMIZED

int permutations(int n, vector<int> &arr)
{
    if (n == 0)
        return 1;

    int count = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[i], arr[n - 1]);
        if (n % arr[n - 1] == 0 || arr[n - 1] % n == 0)
            count += permutations(n - 1, arr);
        swap(arr[i], arr[n - 1]);
    }
    return count;
}

int countArrangement(int n)
{
    vector<int> arr(n);
    for (int i = 1; i <= n; i++)
        arr[i - 1] = i;
    return permutations(n, arr);
}

// DAY 4 (Merge 2 Sorted Lists)============================================================

// METHOD 1
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    ListNode *ans = new ListNode(-101), *head = ans;
    while (l1 && l2)
    {
        if (l1->val < l2->val)
        {
            ans->next = l1;
            l1 = l1->next;
        }
        else
        {
            ans->next = l2;
            l2 = l2->next;
        }
        ans = ans->next;
    }
    if (l1)
        ans->next = l1;
    if (l2)
        ans->next = l2;
    return head->next;
}

// METHOD 2 (Recursive)
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    if (!l1)
        return l2;
    if (!l2)
        return l1;
    if (l1->val < l2->val)
    {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
    else
    {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

// DAY 4 (Remove Duplicates from Sorted List II)===============================================================

// METHOD 1 (Using map)
ListNode *deleteDuplicates(ListNode *head)
{
    map<int, int> m;
    ListNode *itr = head;
    while (itr)
    {
        m[itr->val]++;
        itr = itr->next;
    }
    ListNode *ans = new ListNode(), *temp = ans;
    for (auto p : m)
    {
        if (p.second == 1)
        {
            temp->next = new ListNode(p.first);
            temp = temp->next;
        }
    }
    return ans->next;
}

// METHOD 2 (Without map)
// OPTIMIZED

ListNode *deleteDuplicates(ListNode *head)
{
    ListNode *itr = head, *ans = new ListNode(), *temp = ans;
    while (itr)
    {
        bool flag = false;
        while (itr->next && itr->next->val == itr->val)
        {
            itr = itr->next;
            flag = true;
        }
        if (!flag)
        {
            temp->next = new ListNode(itr->val);
            temp = temp->next;
        }
        itr = itr->next;
    }
    return ans->next;
}

// DAY 6 (Kth missing positive number)===============================================

// METHOD 1 (Using set) --> O(k)
int findKthPositive(vector<int> &arr, int k)
{
    unordered_set<int> s;
    for (int x : arr)
        s.insert(x);
    int i = 1;
    for (; k != 0; i++)
        if (s.find(i) == s.end())
            k--;
    return --i;
}

// METHOD 2 (Without set) --> O(n)

int findKthPositive(vector<int> &arr, int k)
{
    int missing = 0, last = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        int gap = arr[i] - last - 1;
        missing += gap;
        if (missing >= k)
            return last + gap - (missing - k);
        last = arr[i];
    }
    // cout<<last<<endl;
    return last + (k - missing);
}

// METHOD 3 --> O(log n)
// MOST OPTIMIZED
int findKthPositive(vector<int> &arr, int k)
{
    int lo = 0, hi = arr.size();
    while (lo < hi)
    {
        int mid = (lo + hi) >> 1;
        if (arr[mid] - 1 - mid < k)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo + k;
}

// DAY 7 (Longest Substring Without Repeating Characters)=====================================================

// APPROACH 1 -- (Acquire and Release)

// METHOD 1 (Using Set)  --> <O(2*n)
int lengthOfLongestSubstring(string s)
{
    unordered_set<char> st;
    int maxlen = 0, len = 0, idx = 0;
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        while (st.find(c) != st.end())
        {
            st.erase(s[idx++]);
            len--;
        }
        st.insert(c);
        len++;
        maxlen = max(maxlen, len);
        // cout<<c<<" --> "<<len<<endl;
    }
    // cout<<endl;
    return maxlen;
}

// METHOD 2 (Using vector) --> O(2*n)
int lengthOfLongestSubstring(string s)
{
    vector<bool> vis(256, false);
    int maxlen = 0, len = 0, idx = 0;
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        while (vis[c - ' '] == true)
        {
            vis[s[idx++] - ' '] = false;
            len--;
        }
        vis[c - ' '] = true;
        len++;
        maxlen = max(maxlen, len);
        // cout<<c<<" --> "<<len<<endl;
    }
    // cout<<endl;
    return maxlen;
}

// APPROACH 2 (Using last index of every number) --> O(n)

int lengthOfLongestSubstring(string s)
{
    vector<int> lastidx(256, -1);
    int maxlen = 0, idx = -1;
    for (int i = 0; i < s.size(); i++)
    {
        int j = lastidx[s[i] - ' '];
        idx = max(j, idx);
        maxlen = max(maxlen, i - idx);
        lastidx[s[i] - ' '] = i;
    }
    return maxlen;
}

// DAY 8 (Check If Two String Arrays are Equivalent)============================================================

bool arrayStringsAreEqual(vector<string> &word1, vector<string> &word2)
{
    string a = "", b = "";
    for (string s : word1)
        a += s;
    for (string s : word2)
        b += s;
    return a == b;
}

// DAY 9 (Word Ladder)========================================================

int ladderLength(string beginWord, string endWord, vector<string> &wordList)
{
    queue<string> que;
    unordered_set<string> s;
    for (string a : wordList)
        s.insert(a);
    if (s.count(endWord) > 0)
    {
        que.push(endWord);
        s.erase(endWord);
    }

    int level = 0;
    while (!que.empty())
    {
        int sz = que.size();
        level++;
        while (sz--)
        {
            for (int i = 0; i < beginWord.size(); i++)
            {
                string tp = que.front();
                for (char c = 'a'; c <= 'z'; c++)
                {
                    tp[i] = c;
                    if (tp == beginWord)
                        return level + 1;
                    if (s.count(tp) > 0)
                    {
                        que.push(tp);
                        s.erase(tp);
                    }
                }
            }
            que.pop();
        }
    }
    return 0;
}

// DAY 11 (Merge Sorted Array)=========================================================

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    int i = 0, j = 0;
    while (i < m && j < n)
    {
        // cout<<i<<" "<<j<<endl;
        if (nums1[i] < nums2[j])
            i++;
        else
        {
            int k = m;
            while (k > i)
            {
                nums1[k] = nums1[k - 1];
                k--;
            }
            nums1[i] = nums2[j];
            i++, j++;
            m++;
        }
    }
    while (j < n)
        nums1[i++] = nums2[j++];
}

// DAY 12 (Add 2 Numbers)=======================================================

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    ListNode *ans = new ListNode(-1), *temp = ans;
    int carry = 0;
    while (l1 && l2)
    {
        int sum = l1->val + l2->val + carry;
        // cout<<sum<<" ";
        temp->next = new ListNode(sum % 10);
        carry = sum / 10;
        l1 = l1->next;
        l2 = l2->next;
        temp = temp->next;
    }
    // cout<<endl;
    while (l1)
    {
        int sum = l1->val + carry;
        // cout<<sum<<" ";
        temp->next = new ListNode(sum % 10);
        carry = sum / 10;
        l1 = l1->next;
        temp = temp->next;
    }
    // cout<<endl;
    while (l2)
    {
        int sum = l2->val + carry;
        // cout<<sum<<" ";
        temp->next = new ListNode(sum % 10);
        carry = sum / 10;
        l2 = l2->next;
        temp = temp->next;
    }
    // cout<<endl;
    if (carry > 0)
        temp->next = new ListNode(carry);

    return ans->next;
}

// DAY 14 (Boats to Save people)========================================================================

// METHOD 1 --> O((n*logn) + (n*min(people)))
int numRescueBoats(vector<int> &people, int limit)
{
    sort(people.begin(), people.end(), greater<int>());

    unordered_map<int, int> m;
    for (int x : people)
        m[x]++;

    int boats = 0, wt = 0, count = 0;
    int n = people.size();
    for (int i = 0; i < n; i++)
    {
        if (m[people[i]] == 0)
            continue;
        m[people[i]]--;
        int other = limit - people[i];
        while (other > 0)
        {
            if (m[other] > 0)
            {
                m[other]--;
                break;
            }
            other--;
        }
        boats++;
    }

    return boats;
}

// DAY 14 (Minimum Operations to Reduce X to Zero)====================================================================

// APPROACH (BFS)
// TLE
#define f first
#define s second
int minOperations(vector<int> &nums, int x)
{
    int n = nums.size();
    cout << n << endl;
    queue<pair<pair<int, int>, int>> que;
    que.push({{0, n - 1}, x});

    int level = 0;
    while (!que.empty())
    {
        int sz = que.size();
        while (sz--)
        {
            auto p = que.front();
            cout << p.f.f << ", " << p.f.s << " --> " << p.s << endl;
            que.pop();
            if (p.s == 0)
                return level;
            if (p.s - nums[p.f.f] >= 0)
            {
                if (p.s - nums[p.f.f] == 0)
                    return level + 1;
                if (p.f.f + 1 <= p.f.s)
                    que.push({{p.f.f + 1, p.f.s}, p.s - nums[p.f.f]});
            }
            if (p.s - nums[p.f.s] >= 0)
            {
                if (p.s - nums[p.f.s] == 0)
                    return level + 1;
                if (p.f.s - 1 >= p.f.f)
                    que.push({{p.f.f, p.f.s - 1}, p.s - nums[p.f.s]});
            }
        }
        level++;
    }
    return -1;
}

// APPROACH 2 (Sliding Window) --> O(2*n)
// AC

int minOperations(vector<int> &nums, int x)
{
    int l = 0, r = 0;
    int n = nums.size();
    int total = 0;
    for (int x : nums)
        total += x;
    int goal = total - x;
    if (goal < 0)
        return -1;

    int sum = 0;
    int minops = INT_MAX;
    bool flag = false;
    while (l < n)
    {
        if (sum == goal)
        {
            flag = true;
            minops = min(minops, n - (r - l));
            if (r < n)
                sum += nums[r++];
            else
                break;
        }

        else if (sum < goal && r < n)
            sum += nums[r++];

        else if (sum > goal)
            sum -= nums[l++];

        else
            break;
    }
    if (flag)
        return minops;
    return -1;
}

// DAY 15 (Get Maximum in Generated Array)====================================================

int getMaximumGenerated(int n)
{
    if (n == 0)
        return 0;
    vector<int> arr(n + 1);
    arr[0] = 0;
    arr[1] = 1;
    int maxi = 1;
    for (int i = 1; 2 * i <= n; i++)
    {
        arr[2 * i] = arr[i];
        maxi = max(maxi, arr[2 * i]);
        if (2 * i + 1 <= n)
        {
            arr[2 * i + 1] = arr[i] + arr[i + 1];
            maxi = max(maxi, arr[2 * i + 1]);
        }
    }
    return maxi;
}

// DAY 16 (Kth Largest Element in an Array)=========================================================

// APPROACH 1 (Sorting in decreasing order) --> O(n*logn)
int findKthLargest(vector<int> &nums, int k)
{
    int n = nums.size();
    if (n == 0)
        return -1;
    sort(nums.begin(), nums.end(), greater<int>());
    int i = 0;
    for (; k > 1; k--)
        i++;
    if (i >= n)
        return -1;
    return nums[i];
}

// APPROACH 2 (Using Priority Queue) --> O(n*logn)

// METHOD 1 (Max priority queue)
int findKthLargest(vector<int> &nums, int k)
{
    int n = nums.size();
    if (n == 0)
        return -1;
    priority_queue<int> pq;
    for (int x : nums)
        pq.push(x);
    while (--k)
        pq.pop();
    return pq.size() > 0 ? pq.top() : -1;
}

// METHOD 2 (Min Priority Queue) --> (Space OPTIMIZED --> O(k))
int findKthLargest(vector<int> &nums, int k)
{
    int n = nums.size();
    if (n == 0 || k > n)
        return -1;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int x : nums)
    {
        pq.push(x);
        if (pq.size() > k)
            pq.pop();
    }
    return pq.top();
}

// DAY 17 (Count Sorted Vowel Strings)=====================================================================

// METHOD 1 (Recursion)
int rec(int n, int idx)
{
    if (n == 1)
        return idx;
    int count = 0;
    for (int i = idx; i >= 1; i--)
        count += rec(n - 1, i);
    return count;
}

int countVowelStrings(int n)
{
    return rec(n, 5);
}

// METHOD 2 (DP)

int rec(int n, int idx, vector<vector<int>> &dp)
{
    if (n == 1)
        return dp[n][idx] = idx;
    if (dp[n][idx] != -1)
        return dp[n][idx];
    int count = 0;
    for (int i = idx; i >= 1; i--)
        count += rec(n - 1, i, dp);
    return dp[n][idx] = count;
}

int countVowelStrings(int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(6, -1));
    return rec(n, 5, dp);
}