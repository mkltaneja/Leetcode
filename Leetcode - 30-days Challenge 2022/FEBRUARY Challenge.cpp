
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

// DAY 14 (104. Maximum Depth of Binary Tree)=======================================================================

int maxDepth(TreeNode* root) 
{
    return root? max(maxDepth(root->left), maxDepth(root->right)) + 1 : 0;
}

// DAY 15 (136. Single Number)==================================================================================================

int singleNumber(vector<int>& nums) 
{
    int ans = 0;
    for(int x : nums) ans ^= x;
    return ans;
}

// DAY 16 (24. Swap Nodes in Pairs)========================================================================================================

ListNode* swapPairs(ListNode* head) 
{
    ListNode *prev = nullptr, *next, *itr = head;

    while(itr && itr->next)
    {
        ListNode *a = itr, *b = itr->next;
        a->next = nullptr;
        a->next = b->next;
        b->next = nullptr;
        b->next = a;
        if(prev != nullptr)
            prev->next = b;
        else
            head = b;

        prev = itr;
        itr = itr->next;
    }

    return head;
}

// DAY 17 (39. Combination Sum)===========================================================================================

vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
{
    vector<vector<vector<int>>> ans(target+1);
    for(int x : candidates)
    {
        for(int i = x; i <= target; i++)
        {
            if(x > i) continue;
            if(i == x) ans[i].push_back({x});
            else
            {
                for(vector<int> v : ans[i-x])
                {
                    vector<int> tmp = v;
                    tmp.push_back(x);
                    ans[i].push_back(tmp);
                }
            }
        }
    }
    return ans[target];
}

// DAY 18 (402. Remove K Digits)===========================================================================================

string removeKdigits(string num, int k) 
{
    stack<char> st;
    for(char c : num)
    {
        while(!st.empty() && k && c < st.top())
        {
            st.pop();
            k--;
        }
        if(c == '0' && st.empty()) continue;
        st.push(c);
    }

    while(k-- && !st.empty())
        st.pop();

    string ans = "";
    while(!st.empty())
    {
        ans += st.top();
        st.pop();
    }
    reverse(ans.begin(), ans.end());

    return ans.empty()? "0" : ans;
}

// DAY 19 (1675. Minimize Deviation in Array)===========================================================================================

int minimumDeviation(vector<int>& nums) 
{
    priority_queue<int> pq;
    int mn = INT_MAX;
    for(int x : nums)
    {
        if(x&1) x *= 2;
        mn = min(mn, x);
        pq.push(x);
    }
    int mndev = pq.top() - mn;
    while(pq.top() & 1 ^ 1)
    {
        int tp = pq.top();
        pq.pop();
        tp /= 2;
        pq.push(tp);
        mn = min(mn, tp);
        mndev = min(mndev, pq.top()-mn);
    }

    return mndev;
}

// DAY 20 (1288. Remove Covered Intervals)===========================================================================================

int removeCoveredIntervals(vector<vector<int>>& intervals) 
{
    sort(intervals.begin(), intervals.end(), [](vector<int> &v1, vector<int> &v2){
        return v1[0] == v2[0]? v1[1] > v2[1] : v1[0] < v2[0];
    });

    int mxend = intervals[0][1];
    int rem = 0;
    for(int i = 1; i < intervals.size(); i++)
    {
        if(intervals[i][1] <= mxend) rem++;
        else mxend = intervals[i][1];
    }

    return intervals.size() - rem;
}

// DAY 21 (169. Majority Element)===========================================================================================

int majorityElement(vector<int>& nums) 
{
    int cnt = 0, n = 0;
    for(int x : nums)
    {
        if(cnt == 0) n = x, cnt = 1;
        else if(x == n) cnt++;
        else cnt--;
    }
    return n;
}

// DAY 22 (171. Excel Sheet Column Number)===========================================================================================

int titleToNumber(string columnTitle) 
{
    int ans = 0;
    for(char c : columnTitle)
        ans = ans*26 + (c-'A'+1);
    return ans;
}

// DAY 23 (133. Clone Graph)===========================================================================================

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    
    Node* cloneGraph(Node* node, vector<Node*> &vis)
    {
        if(!node) return node;
        if(vis[node->val]) return vis[node->val];
        
        Node* nnode = new Node(node->val);
        vis[nnode->val] = nnode;
        
        for(Node* nbr : node->neighbors)
            nnode->neighbors.push_back(cloneGraph(nbr, vis));
        return nnode;
    }
    
    Node* cloneGraph(Node* node) 
    {
        vector<Node*> vis(101, nullptr);
        return cloneGraph(node, vis);
    }
};

// DAY 24 (148. Sort List)===========================================================================================

ListNode* getMid(ListNode* head)
{
    ListNode* fast = head, *slow = head;
    while(fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

ListNode* merge(ListNode* l1, ListNode* l2)
{
    ListNode* ans = new ListNode(INT_MIN), *itr = ans;
    while(l1 || l2)
    {
        int x = l1? l1->val : INT_MAX;
        int y = l2? l2->val : INT_MAX;
        if(x < y)
        {
            itr->next = new ListNode(x);
            l1 = l1->next;
        }
        else
        {
            itr->next = new ListNode(y);
            l2 = l2->next;
        }
        itr = itr->next;
    }
    return ans->next;
}

ListNode* sortList(ListNode* head) 
{
    if(!head || !head->next) return head;

    ListNode* mid = getMid(head);
    ListNode* nxt = mid->next;
    mid->next = nullptr;
    ListNode* l1 = sortList(head);
    ListNode* l2 = sortList(nxt);

    ListNode* ans = merge(l1, l2);

    return ans;
}

// DAY 25 (165. Compare Version Numbers)======================================================================

int compareVersion(string version1, string version2) 
{
    int i = 0, j = 0, n = version1.size(), m = version2.size();

    while(i < n || j < m)
    {
        int x = 0, y = 0;
        while(i < n && version1[i] != '.')
            x = x*10 + (version1[i++]-'0');
        while(j < m && version2[j] != '.')
            y = y*10 + (version2[j++]-'0');
        i++, j++;

        if(x > y) return 1;
        else if(x < y) return -1;
    }
    return 0;
}

// DAY 26 (847. Shortest Path Visiting All Nodes)======================================================================

int shortestPathLength(vector<vector<int>>& graph) 
{
    int n = graph.size();
    if(n == 1) return 0;
    int allvis = (1 << n) - 1;

    vector<vector<int>> vis(n, vector<int>((1<<n), 0));

    queue<pair<int,int>> que;
    for(int i = 0; i < n; i++)
    {
        que.push({i, (1<<i)});
        vis[i][(1<<i)] = 1;
    }

    int steps = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            auto p = que.front();
            que.pop();
            int u = p.first;
            int mask = p.second;
            for(int v : graph[u])
            {
                int mask2 = mask | (1 << v);
                if(mask2 == allvis) 
                    return steps+1;

                if(!vis[v][mask2])
                {
                    vis[v][mask2] = 1;
                    que.push({v, mask2});
                }
            }
        }
        steps++;
    }
    return steps;
}
