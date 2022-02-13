
// DAY 1 (121. Best Time to Buy and Sell Stock)================================================================================

int maxProfit(vector<int> &prices)
{
    int mn = INT_MAX, ans = 0;
    for (int x : prices)
    {
        ans = max(ans, x - mn);
        mn = min(mn, x);
    }
    return ans;
}

// DAY 2 (438. Find All Anagrams in a String)======================================================================

vector<int> findAnagrams(string s, string p)
{
    int n = s.size(), m = p.size();
    vector<int> ans;
    if (n < m)
        return ans;

    vector<int> sx(26, 0), px(26, 0);
    for (int i = 0; i < m; i++)
        sx[s[i] - 'a']++;
    for (int i = 0; i < m; i++)
        px[p[i] - 'a']++;

    if (sx == px)
        ans.push_back(0);

    for (int i = m; i < n; i++)
    {
        sx[s[i] - 'a']++;
        sx[s[i - m] - 'a']--;
        if (sx == px)
            ans.push_back(i - m + 1);
    }

    return ans;
}

// DAY 3 (454. 4Sum II)=========================================================================================

int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4)
{
    int n = nums1.size();
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mp[nums1[i] + nums2[j]]++;

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans += mp[-(nums3[i] + nums4[j])];

    return ans;
}

// DAY 4 (525. Contiguous Array)======================================================================

int findMaxLength(vector<int> &nums)
{
    unordered_map<int, int> mp;
    mp[0] = -1;
    int pol = 0;
    int ans = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        pol += (nums[i] == 1);
        pol -= (nums[i] == 0);
        if (!mp.count(pol))
            mp[pol] = i;
        else
            ans = max(ans, i - mp[pol]);
    }
    return ans;
}

// DAY 5 (23. Merge k Sorted Lists)=============================================================================

// APPROACH 1 (Using Priority Queue) --> O(n*log(k))

struct comp
{
    bool operator()(ListNode *a, ListNode *b)
    {
        return a->val > b->val;
    }
};

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    priority_queue<ListNode *, vector<ListNode *>, comp> pq;
    for (int i = 0; i < lists.size(); i++)
        if (lists[i])
            pq.push(lists[i]);

    ListNode *ans = new ListNode(INT_MIN), *itr = ans;
    while (!pq.empty())
    {
        ListNode *node = pq.top();
        pq.pop();
        ListNode *nxt = node->next;
        if (nxt)
            pq.push(nxt);

        itr->next = node;
        itr = itr->next;
    }

    return ans->next;
}

// APPROACH 2 (DIVIDE)

// METHOD 1 (Brute Force) --> O(n*k) [n -> total nodes]

ListNode *merge2lists(ListNode *l1, ListNode *l2)
{
    ListNode *ans = new ListNode(INT_MIN), *itr = ans;
    while (l1 && l2)
    {
        if (l1->val < l2->val)
        {
            itr->next = l1;
            l1 = l1->next;
        }
        else
        {
            itr->next = l2;
            l2 = l2->next;
        }
        itr = itr->next;
    }
    itr->next = l1 ? l1 : l2;
    return ans->next;
}

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    if (lists.empty())
        return nullptr;

    ListNode *ans = new ListNode(INT_MIN);
    for (int i = 0; i < lists.size(); i++)
        ans = merge2lists(ans, lists[i]);

    return ans->next;
}

// METHOD 2 (Divide and Conquer) --> O(n*logn(k)) [n -> total nodes] [O(1) space]

ListNode *merge2lists(ListNode *l1, ListNode *l2)
{
    ListNode *ans = new ListNode(INT_MIN), *itr = ans;
    while (l1 && l2)
    {
        if (l1->val < l2->val)
        {
            itr->next = l1;
            l1 = l1->next;
        }
        else
        {
            itr->next = l2;
            l2 = l2->next;
        }
        itr = itr->next;
    }
    itr->next = l1 ? l1 : l2;
    return ans->next;
}

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    if (lists.empty())
        return nullptr;

    for (int i = 1; i < lists.size(); i *= 2)
        for (int j = 0; i + j < lists.size(); j += (i * 2))
            lists[j] = merge2lists(lists[j], lists[i + j]);

    return lists[0];
}

// DAY 6 (80. Remove Duplicates from Sorted Array II)===========================================================================

int removeDuplicates(vector<int> &nums)
{
    unordered_map<int, int> m;
    int i = 0, j = 0;
    while (i < nums.size())
    {
        if (++m[nums[i]] <= 2)
            swap(nums[i], nums[j++]);
        i++;
    }
    return j;
}

// DAY 7 (389. Find the Difference)=================================================================================================

char findTheDifference(string s, string t)
{
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        ans ^= s[i];
        ans ^= t[i];
    }
    ans ^= t.back();

    return ans;
}

// DAY 8 (258. Add Digits)==========================================================================================================

int addDigits(int num) 
{
    return 1 + (num-1)%9;
}

// DAY 9 (532. K-diff Pairs in an Array)=============================================================================================

int findPairs(vector<int>& nums, int k) 
{
    unordered_map<int,int> mp;
    for(int x : nums)
        mp[x]++;
    int ans = 0;
    for(auto p : mp)
    {
        if(k == 0) ans += (p.second > 1);
    }
    return ans;
}

// DAY 10 (560. Subarray Sum Equals K)============================================================================================================================

int subarraySum(vector<int>& nums, int k) 
{
    unordered_map<int,int> mp;
    mp[0] = 1;
    int psum = 0;
    int ans = 0;
    for(int x : nums)
    {
        psum += x;
        ans += mp[psum-k];
        mp[psum]++;
    }
    return ans;
}

// DAY 11 (567. Permutation in String)==============================================================================================

// APPROACH 1 (Sliding window - with variable size)

bool checkInclusion(string s1, string s2) 
{
    vector<int> map(26);
    for(char c : s1)
        map[c-'a']++;

    int i = 0;
    while(i < s2.size())
    {
        if(!map[s2[i]-'a']) 
        {
            i++;
            continue;
        }

        int n = s1.size();
        vector<int> tmap(26);
        int j = i;
        while(i < s2.size() && map[s2[i]-'a'])
        {
            tmap[s2[i]-'a']++;
            while(j < i && tmap[s2[i]-'a'] > map[s2[i]-'a'])
                tmap[s2[j++]-'a']--;
            i++;
            if(tmap == map) return true;
        }
    }
    return false;
}

// APPROACH 2 (Sliding Window - fixed size)

bool checkInclusion(string s1, string s2) 
{
    vector<int> map1(26), map2(26);
    for(char c : s1)
        map1[c-'a']++;

    for(int i = 0; i < s2.size(); i++)
    {
        if(i >= s1.size()) 
            map2[s2[i-s1.size()]-'a']--;
        map2[s2[i]-'a']++;

        if(map1 == map2) return true;
    }
    return false;
}

// DAY 12 (127. Word Ladder)===============================================================================================

int ladderLength(string beginWord, string endWord, vector<string>& wordList) 
{
    unordered_set<string> st;
    for(string s : wordList)
        st.insert(s);

    if(!st.count(endWord)) return 0;

    queue<string> que;
    que.push(beginWord);

    unordered_set<string> vis;
    vis.insert(beginWord);

    int lvl = 1;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            string x = que.front();
            que.pop();

            if(x == endWord) return lvl;

            for(int i = 0; i < x.size(); i++)
            {
                char c = x[i];
                for(int j = 'a'; j <= 'z'; j++)
                {
                    if(j == c) continue;
                    x[i] = j;
                    if(st.count(x) && !vis.count(x)) 
                    {
                        que.push(x);
                        vis.insert(x);
                    }
                }
                x[i] = c;
            }
        }
        lvl++;
    }

    return 0;
}

// DAY 13 (78. Subsets)======================================================================================================

vector<vector<int>> subsets(vector<int>& nums) 
{
    vector<vector<int>> ans;
    int n = nums.size();
    for(int i = 0; i < (1 << n); i++)
    {
        vector<int> curr;
        for(int j = 0; j < n; j++)
            if(i & (1 << j))
                curr.push_back(nums[j]);
        ans.push_back(curr);
    }
    return ans;
}
