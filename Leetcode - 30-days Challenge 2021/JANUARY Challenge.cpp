
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

// APPROACH 1 (Naive)
// METHOD 1 (Recursion) --> O(5^n)
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

// METHOD 2 (DP) --> O(5*n)

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

// APPROACH 2 (Pentalope Number -- It is a no. which in the 5th cell of every row(starting from 6th) in Pascal's triangle)

int countVowelStrings(int n)
{
    n++;
    return (n * (n + 1) * (n + 2) * (n + 3)) / 24;
}

// DAY 18 (Max Number of K-Sum Pairs)============================================================

// APPROACH 1 (Naive) --> O(n^2)
int maxOperations(vector<int> &nums, int k)
{
    int n = nums.size();
    int count = 0;
    vector<bool> vis(n, false);
    for (int i = 0; i < n; i++)
    {
        if (vis[i])
            continue;
        for (int j = i + 1; j < n; j++)
        {
            if (vis[j])
                continue;
            if (nums[i] + nums[j] == k)
            {
                vis[i] = true;
                vis[j] = true;
                count++;
                break;
            }
        }
    }
    return count;
}

// APPROACH 2 (Using unordered_map) --> >O(n)
int maxOperations(vector<int> &nums, int k)
{
    int n = nums.size();
    int count = 0;
    unordered_map<int, int> m;
    for (int i = 0; i < n; i++)
    {
        if (m.count(k - nums[i]) > 0)
        {
            if (--m[k - nums[i]] == 0)
                m.erase(k - nums[i]);
            count++;
        }
        else
            m[nums[i]]++;
    }
    return count;
}

// APPROACH 3 (Sorting -- 2 pointer approach) --> O(nlogn + n) -- (Space and Time OPTIMIZED)
int maxOperations(vector<int> &nums, int k)
{
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int count = 0;
    int st = 0, end = n - 1;

    while (st < end)
    {
        int sum = nums[st] + nums[end];
        if (sum == k)
        {
            count++;
            st++;
            end--;
        }
        else if (sum < k)
            st++;
        else
            end--;
    }
    return count;
}

// DAY 19 (Longest Palindromic Substring)=================================================

// APPROACH 1 (DP) --> O(n^2)
string longestPalindrome(string s)
{
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, 0));
    // cout<<fill_palindromes(0, n-1, s, dp)<<endl;

    int st = -1, end = n + 1;
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                dp[i][j] = true;
            else if (gap == 1)
            {
                if (s[i] == s[j])
                    dp[i][j] = true;
            }
            else if (gap > 1 && s[i] == s[j] && dp[i + 1][j - 1])
                dp[i][j] = true;

            if (dp[i][j] && end != gap + 1)
                st = i, end = gap + 1;
        }
    }
    // for(int i = 0; i < n; i++)
    // {
    //     for(int j = 0; j < n; j++)
    //         cout<<dp[i][j]<<" ";
    //     cout<<endl;
    // }
    // cout<<st<<", "<<end<<endl;
    // cout<<endl;
    return s.substr(st, end);
}

// FOR COUNTING THE NUMBER OF PALINDROMES RECURSIVELY :--

//     int fill_palindromes(int i, int j, string &s, vector<vector<int>> &dp)
//     {
//         if(i > j)
//             return 0;
//         if(i == j)
//             return dp[i][j] = 1;
//         if(dp[i][j] != 0)
//             return dp[i][j];

//         int p_middle = fill_palindromes(i+1, j, s, dp);
//         int middle_s = fill_palindromes(i, j-1, s, dp);
//         int middle = fill_palindromes(i+1, j-1, s, dp);

//         int count = p_middle + middle_s - middle;

//         return dp[i][j] = s[i] == s[j] ? count + 1 : count;
//     }

// APPROACH 2 (Sliding Window) --> <O(n^2)    [OPTIMIZED -- in terms of time and space BOTH]
string longestPalindrome(string s)
{
    int n = s.size();
    int st = 0, end = -1;

    int i = 0;
    while (i < n)
    {
        int left = i, right = i; // Starting window from i

        while (i + 1 < n && s[i + 1] == s[i])
            i++; // duplicate characters
        right = i;

        while (left - 1 >= 0 && right + 1 < n && s[left - 1] == s[right + 1])
            left--, right++; // expanding window

        if (right - left + 1 > end - st + 1)
            st = left, end = right; // maximizing ans;

        i++;
    }
    return s.substr(st, end - st + 1);
}

// DAY 20 (Valid Parenthesis)===========================================================

bool isValid(string s)
{
    stack<char> st;
    for (char c : s)
    {
        if (c == '(' || c == '[' || c == '{')
            st.push(c);
        else
        {
            if (st.empty())
                return false;
            if (c == ')')
            {
                if (st.top() == '(')
                    st.pop();
                else
                    return false;
            }
            if (c == ']')
            {
                if (st.top() == '[')
                    st.pop();
                else
                    return false;
            }
            if (c == '}')
            {
                if (st.top() == '{')
                    st.pop();
                else
                    return false;
            }
        }
    }
    return st.empty();
}

// DAY 21 (Find the Most Competitive Subsequence)============================================================================

// APPROACH 1 (Brute force) --> O(n*k)
// TLE
int findmin_inrange(int st, int end, vector<int> &nums)
{
    int minidx = st;
    while (st <= end)
    {
        if (nums[st] < nums[minidx])
            minidx = st;
        st++;
    }
    return minidx;
}

vector<int> mostCompetitive(vector<int> &nums, int k)
{
    int idx = -1, i = 0;
    vector<int> ans(k);
    while (i < k)
    {
        idx = findmin_inrange(idx + 1, nums.size() - 1 - (k - i - 1), nums);
        ans[i++] = nums[idx];
    }
    return ans;
}

// APPROACH 2 (Using priority_queue) --> O(n*logn)
// AC
vector<int> mostCompetitive(vector<int> &nums, int k)
{
    int n = nums.size();

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i <= n - k; i++)
        pq.push({nums[i], i});

    vector<int> ans(k);
    int lastidx = -1;
    for (int i = 0; i < k;)
    {
        if (pq.top().second > lastidx)
        {
            ans[i++] = pq.top().first;
            lastidx = pq.top().second;
            pq.pop();
            if (i != k)
                pq.push({nums[n - k + i], n - k + i});
        }
        else
            pq.pop();
    }
    return ans;
}

// APPROACH 3 (Stack) --> O(2*n)
// AC
vector<int> mostCompetitive(vector<int> &nums, int k)
{
    int n = nums.size();
    if (n == k)
        return nums;

    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
        while (!ans.empty() && nums[i] < ans.back() && ans.size() + (n - i) > k)
            ans.pop_back();
        if (ans.size() < k)
            ans.push_back(nums[i]);
    }
    return ans;
}

// DAY 22 (Determine if Two Strings Are Close)==========================================================================

bool closeStrings(string word1, string word2)
{
    // cout<<word1<<" "<<word2<<endl;
    int n = word1.size(), m = word2.size();
    if (n != m)
        return false;

    vector<int> m1(26, 0), m2(26, 0);
    for (char c : word1)
        m1[c - 'a']++;
    for (char c : word2)
        m2[c - 'a']++;

    // int diff = 0;
    for (char c = 'a'; c < 'z'; c++)
    {
        // if(m1[c-'a'] != m2[c-'a'])
        //     diff++;
        if (m1[c - 'a'] != 0 && m2[c - 'a'] == 0)
            return false;
        if (m2[c - 'a'] != 0 && m1[c - 'a'] == 0)
            return false;
    }
    // if(diff & 1)
    //     return false;
    vector<int> c1, c2;
    for (int x : m1)
        if (x)
            c1.push_back(x);
    for (int x : m2)
        if (x)
            c2.push_back(x);
    // for(int i : c1)
    //    cout<<i<<" ";
    // cout<<endl;
    // for(int i : c2)
    //    cout<<i<<" ";
    // cout<<endl<<endl;
    sort(c1.begin(), c1.end());
    sort(c2.begin(), c2.end());
    return c1 == c2;
}

// DAY 23 (Sort the Matrix Diagonally)=======================================================================================

// METHOD 1 (Using the property of right diagonals)
vector<vector<int>> diagonalSort(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size();
    for (int d = 0; d < m + n - 1; d++)
    {
        int i, j, ii, jj;
        if (d - (m - 1) < 0)
            j = (m - 1) - d;
        else
            j = 0;
        i = j + (d - (m - 1));
        ii = i, jj = j;

        vector<int> tmp;
        for (; i < n && j < m; i++, j++)
            tmp.push_back(mat[i][j]);
        sort(tmp.begin(), tmp.end());
        int k = 0;
        for (; ii < n && jj < m; ii++, jj++)
            mat[ii][jj] = tmp[k++];
    }
    return mat;
}

// METHOD 2 (Simpler Version)
vector<vector<int>> diagonalSort(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size();

    int r = n - 1, c = 0;
    while (c < m)
    {
        vector<int> tmp;
        for (int i = r, j = c; i < n && j < m; i++, j++)
            tmp.push_back(mat[i][j]);
        sort(tmp.begin(), tmp.end());
        int k = 0;
        for (int i = r, j = c; i < n && j < m; i++, j++)
            mat[i][j] = tmp[k++];

        if (r == 0)
            c++;
        else
            r--;
    }
    return mat;
}

// DAY 24 (Merge K Sorted Lists)===========================================================

// METHOD 1 (Iterating over all nodes)
ListNode *mergeKLists(vector<ListNode *> &lists)
{
    int k = lists.size();
    vector<int> ptrs(k, 0);
    ListNode *ans = new ListNode(), *temp = ans;

    while (true)
    {
        int minval = INT_MAX, minidx = -1;
        for (int i = 0; i < k; i++)
        {
            int val = INT_MAX;
            if (lists[i])
                val = lists[i]->val;
            if (val < minval)
            {
                minval = val;
                minidx = i;
            }
        }
        // cout<<minval<<endl;
        if (minval == INT_MAX)
            break;
        temp->next = new ListNode(minval);
        temp = temp->next;
        lists[minidx] = lists[minidx]->next;
    }
    return ans->next;
}

// METHOD 2 (Using Priority Queue)
struct comp
{
    bool operator()(ListNode *a, ListNode *b)
    {
        return a->val > b->val;
    }
};

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    int k = lists.size();
    priority_queue<ListNode *, vector<ListNode *>, comp> pq;
    for (int i = 0; i < k; i++)
        if (lists[i])
            pq.push(lists[i]);
    ListNode *ans = new ListNode(), *temp = ans;

    while (!pq.empty())
    {
        ListNode *node = pq.top();
        pq.pop();
        temp->next = node;
        temp = temp->next;
        node = node->next;
        if (node)
            pq.push(node);
    }
    return ans->next;
}

// METHOD 3(Divide and Conquer)

ListNode *merge2lists(ListNode *&l1, ListNode *&l2)
{
    if (!l1 || !l2)
        return l1 ? l1 : l2;
    if (l1->val < l2->val)
    {
        l1->next = merge2lists(l1->next, l2);
        return l1;
    }
    else
    {
        l2->next = merge2lists(l1, l2->next);
        return l2;
    }
}

ListNode *merge(int st, int end, vector<ListNode *> &lists)
{
    if (st > end)
        return nullptr;
    if (st == end)
        return lists[st];
    if (st == end - 1)
        return merge2lists(lists[st], lists[end]);

    int mid = (st + end) >> 1;
    ListNode *left = merge(st, mid, lists);
    ListNode *right = merge(mid + 1, end, lists);

    return merge2lists(left, right);
}

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    return merge(0, lists.size() - 1, lists);
}

// DAY 25 (Check If All 1's Are at Least Length K Places Away)===============================================================

bool kLengthApart(vector<int> &nums, int k)
{
    int prev = -k - 1;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == 1)
        {
            if (i - prev - 1 < k)
                return false;
            prev = i;
        }
    }
    return true;
}

// DAY 26 (Path with Minimum Effort)=================================================

bool bfs(int n, int m, vector<vector<int>> &arr, int maxdiff)
{
    queue<pair<int, int>> que;
    que.push({0, 0});
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vis[0][0] = true;
    while (!que.empty())
    {
        auto tp = que.front();
        que.pop();
        int i = tp.first;
        int j = tp.second;

        if (i == n - 1 && j == m - 1)
            return true;

        if (i + 1 != n && !vis[i + 1][j] && abs(arr[i + 1][j] - arr[i][j]) <= maxdiff)
        {
            vis[i + 1][j] = true;
            que.push({i + 1, j});
        }
        if (j + 1 != m && !vis[i][j + 1] && abs(arr[i][j + 1] - arr[i][j]) <= maxdiff)
        {
            vis[i][j + 1] = true;
            que.push({i, j + 1});
        }
        if (i - 1 >= 0 && !vis[i - 1][j] && abs(arr[i - 1][j] - arr[i][j]) <= maxdiff)
        {
            vis[i - 1][j] = true;
            que.push({i - 1, j});
        }
        if (j - 1 >= 0 && !vis[i][j - 1] && abs(arr[i][j - 1] - arr[i][j]) <= maxdiff)
        {
            vis[i][j - 1] = true;
            que.push({i, j - 1});
        }
    }
    return false;
}

int minimumEffortPath(vector<vector<int>> &heights)
{
    int n = heights.size(), m = heights[0].size();
    int l = 0, r = 1e6;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (bfs(n, m, heights, mid))
            r = mid;
        else
            l = mid + 1;
    }
    return r;
}

// DAY 27 (Concatenation of Consecutive Binary Numbers)===================================================================

// APPROACH 1 (Brute force) --> >O(32*n)
// TLE

int mod = 1e9 + 7;
// string binvals[100005] = {""};

string binary(int n)
{
    string bin = "";
    int x = n;
    while (x)
    {
        // if(binvals[x] != "")
        // {
        //     bin += binvals[x];
        //     break;
        // }
        bin += x % 2 + '0';
        x /= 2;
    }
    // binvals[n] = bin;
    reverse(bin.begin(), bin.end());
    return bin;
}

int decimal(string bin)
{
    int dec = 0;
    for (int i = 0; i < bin.size(); i++)
        dec = ((dec * 2) % mod + bin[i] - '0') % mod;
    return dec % mod;
}

int concatenatedBinary(int n)
{
    string bin = "";
    for (int i = 1; i <= n; i++)
        bin += binary(i);
    cout << bin.size() << endl;
    return decimal(bin);
}

// APPROACH 2
// METHOD 1 (Optimized using logarithmic power function
//          and finding binary to decimal along with traversing from 1 to n) --> >O(n*logn)

// AC

int mod = 1e9 + 7;

long powerlog(long a, int b)
{
    long ans = 1;
    while (b)
    {
        if (b & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans % mod;
}

int concatenatedBinary(int n)
{
    long ans = 0;
    for (long i = 1; i <= n; i++)
    {
        int shifts = log2(i) + 1;
        ans = ((ans * powerlog(2, shifts)) % mod + i) % mod;
    }
    return (int)ans;
}

// APPROACH 2
// METHOD 2 -- [MOST OPTIMIZED] (Using DP to store previous answer) --> O(n*logn)

int mod = 1e9 + 7;

int concatenatedBinary(int n)
{
    vector<long> dp(n + 1);
    dp[1] = 1;
    for (long i = 2; i <= n; i++)
    {
        int shifts = log2(i) + 1;
        long pow2 = (1l << shifts) % mod;
        dp[i] = ((dp[i - 1] * pow2) % mod + i) % mod;
    }
    return (int)dp[n];
}

// DAY 28 (Smallest String With A Given Numeric Value)================================================================

// APPROACH 1 (Recursion and Backtracking) --> <<O(26^n)
// string ans = "zzzzzzzzzzzzzzzzzzzzzzzzzz";
bool recurs(int n, int k, string &s)
{
    if (26 * n < k)
        return false;
    if (n == 0)
    {
        // ans = s;
        return true;
    }
    bool res = false;
    for (char c = 'a'; c <= 'z'; c++)
    {
        s += c;
        res |= recurs(n - 1, k - (c - 'a' + 1), s);
        if (res)
            return res; // OPTIMIZATION STEP
        s.pop_back();
    }
    return res;
}

string getSmallestString(int n, int k)
{
    string ans = "";
    recurs(n, k, ans);
    return ans;
}

// APPROACH 2 (Add 'a' then 'other character' then 'z') --> O(n)

string getSmallestString(int n, int k)
{
    string ans = "";
    while (n)
    {
        if (26 * (n - 1) - (k - 1) >= 0)
        {
            ans += "a";
            k--;
        }
        else
        {
            ans += (char)((k - 26 * (n - 1)) + 'a' - 1);
            // cout<<k - 26*(n-1)<<" ";
            k = 26 * (n - 1);
        }
        n--;
    }
    // cout<<endl;
    return ans;
}

// APPROACH 3 (Greedy) --> O(k/26)

string getSmallestString(int n, int k)
{
    string ans(n, 'a');
    int i = n - 1;
    k -= n;
    while (k)
    {
        int ch = min(25, k);
        ans[i] += ch;
        k -= ch;
    }
    return ans;
}

// DAY 29 (Vertical Order Traversal of a Binary Tree)=========================================================

void dfs(TreeNode *node, int width, int &lm, int &rm)
{
    if (!node)
        return;
    lm = min(lm, width);
    rm = max(rm, width);
    dfs(node->left, width - 1, lm, rm);
    dfs(node->right, width + 1, lm, rm);
}

void bfs(TreeNode *node, vector<vector<int>> &ans, int lm, int rm)
{
    queue<pair<TreeNode *, int>> que;
    que.push({node, 0});
    ans[-lm].push_back(node->val);
    while (!que.empty())
    {
        vector<vector<int>> tmp(ans.size(), vector<int>());
        int sz = que.size();
        while (sz--)
        {
            auto tp = que.front();
            que.pop();
            if (tp.first->left)
            {
                que.push({tp.first->left, tp.second - 1});
                tmp[-lm + (tp.second - 1)].push_back(tp.first->left->val);
            }
            if (tp.first->right)
            {
                que.push({tp.first->right, tp.second + 1});
                tmp[-lm + (tp.second + 1)].push_back(tp.first->right->val);
            }
        }
        for (int i = 0; i < tmp.size(); i++)
        {
            sort(tmp[i].begin(), tmp[i].end());
            for (int j = 0; j < tmp[i].size(); j++)
                ans[i].push_back(tmp[i][j]);
        }
    }
}

vector<vector<int>> verticalTraversal(TreeNode *root)
{
    int leftmost = INT_MAX, rightmost = INT_MIN;
    dfs(root, 0, leftmost, rightmost);
    // cout<<leftmost<<" "<<rightmost<<endl;
    vector<vector<int>> ans(rightmost - leftmost + 1, vector<int>());
    bfs(root, ans, leftmost, rightmost);
    return ans;
}

// DAY 30 (Minimize Deviation in Array)================================================

int minimumDeviation(vector<int> &nums)
{
    int mini = INT_MAX;
    priority_queue<int> pq;
    for (int i = 0; i < nums.size(); i++)
    {
        while (nums[i] & 1)
            nums[i] *= 2;
        pq.push(nums[i]);
        mini = min(mini, nums[i]);
    }

    int mindev = pq.top() - mini;
    while (pq.top() % 2 == 0)
    {
        int x = pq.top();
        pq.pop();
        x /= 2;
        mini = min(mini, x);
        pq.push(x);
        mindev = min(mindev, pq.top() - mini);
    }

    return mindev;
}

//  DAY 31 (Next Permutation)=========================================================

// APPROACH 1   :)
void nextPermutation(vector<int>& nums) 
{
    next_permutation(nums.begin(), nums.end());
}


