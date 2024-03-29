// DAY 1 (912. Sort an Array)=====================================================================================================

// APPROACH 2 (Merge Sort) --> Time = O(nlogn), Space = O(n)

vector<int> merge(vector<int> &l, vector<int> &r)
{
    int n = l.size(), m = r.size();
    vector<int> merged(n+m);
    int i = 0, j = 0, k = 0;
    while(i < n || j < m)
    {
        int x = i < n? l[i] : 1e5;
        int y = j < m? r[j] : 1e5;

        merged[k++] = x < y? l[i++] : r[j++];
    }

    return merged;
}

vector<int> mergeSort(int lo, int hi, vector<int> &nums)
{
    if(lo > hi) return {};
    if(lo == hi) return {nums[lo]};

    int mid = lo + ((hi - lo) >> 1);

    vector<int> lans = mergeSort(lo, mid, nums);
    vector<int> rans = mergeSort(mid+1, hi, nums);

    return merge(lans, rans);
}

vector<int> sortArray(vector<int>& nums) 
{
    return mergeSort(0, nums.size()-1, nums);
}

// APPROACH 2 (Heap Sort) --> Time = O(nlogn), Space = O(1)

void maxHeapify(int i, int n, vector<int> &nums)
{
    int l = 2*i + 1, r = 2*i + 2;
    int largest = i;
    if(l < n && nums[l] > nums[largest])
        largest = l;
    if(r < n && nums[r] > nums[largest])
        largest = r;

    if(i != largest)
    {
        swap(nums[i], nums[largest]);
        maxHeapify(largest, n, nums);
    }
}

void heapSort(vector<int> &nums)
{
    int n = nums.size();
    for(int i = n/2-1; i >= 0; i--)
        maxHeapify(i, n, nums);

    for(int i = n-1; i > 0; i--)
    {
        swap(nums[0], nums[i]);
        maxHeapify(0, i, nums);
    }
}

vector<int> sortArray(vector<int>& nums) 
{
    heapSort(nums);
    return nums;
}

// DAY 2 (443. String Compression)=======================================================================================

int compress(vector<char>& chars)
{
    int p = 0, i = 0, n = chars.size();
    while(i < n)
    {
        int j = i;
        while(j < n && chars[j] == chars[i]) j++;
        chars[p++] = chars[i];
        int len = j-i;
        if(len > 1)
        {
            string lenstr = to_string(len);
            int k = 0;
            while(k < lenstr.size())
                chars[p++] = lenstr[k++];
        }
        i = j;
    }
    while(chars.size() > p)
        chars.pop_back();

    return chars.size();
}

// DAY 3 (28. Find the Index of the First Occurrence in a String)=============================================================================

int strStr(string haystack, string needle) 
{
    string comb = needle + "#" + haystack;
    int n = comb.size();
    vector<int> zarray(n);
    int i = 1, len = 0;
    while(i < n)
    {
        if(comb[i] == comb[len]) 
            zarray[i++] = ++len;
        else
        {
            if(len) len = zarray[len-1];
            else i++;
        }
        if(len == needle.size()) return i - 2*needle.size() - 1;
    }

    return -1;
}

// DAY 4 (2444. Count Subarrays With Fixed Bounds)========================================================================================

long long countSubarrays(vector<int>& nums, int minK, int maxK) 
{
    long long ans = 0, lastmx = -1, lastmn = -1, p = -1;
    for(int i = 0; i < nums.size(); i++)
    {
        if(nums[i] == maxK)
            lastmx = i;
        if(nums[i] == minK)
            lastmn = i;
        if(nums[i] > maxK || nums[i] < minK)
            lastmx = lastmn = p = i;
        int mni = min(lastmx, lastmn);
        ans += mni - p;
    }
    return ans;
}

// DAY 5 (1345. Jump Game IV)=================================================================================================

int minJumps(vector<int>& arr) 
{
    unordered_map<int,vector<int>> mp;
    int n = arr.size();
    for(int i = 0; i < n; i++)
        mp[arr[i]].push_back(i);

    vector<int> vis(n,0);
    queue<int> que;
    que.push(0);
    vis[0] = 1;
    int ans = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int u = que.front();
            que.pop();

            if(u == n-1) return ans;

            for(int &v : mp[arr[u]])
            {
                if(!vis[v])
                {
                    if(v == n-1) return ans + 1;
                    que.push(v);
                    vis[v] = 1;
                }
            }
            mp[arr[u]].clear();
            for(int d : {-1, 1})
            {
                if(u + d >= 0 && u + d < n && !vis[u+d])
                {
                    if(u+d == 0) return ans + 1;
                    que.push(u+d);
                    vis[u+d] = 1;
                }
            }
        }
        ans++;
    }

    return ans;
}

// DAY 6 (1539. Kth Missing Positive Number)=================================================================================

int findKthPositive(vector<int>& arr, int k) 
{
    int lo = 0, hi = arr.size();
    while(lo < hi)
    {
        int mid = lo + ((hi - lo) >> 1);

        if(arr[mid] - (mid + 1) < k)
            lo = mid + 1;
        else hi = mid;
    }

    return lo + k;
}

// DAY 7 (875. Koko Eating Bananas)=========================================================================================

int checkTime(vector<int> &piles, int k)
{
    int time = 0;
    for(int x : piles)
        time += (x + k - 1) / k;
    return time;
}

int minEatingSpeed(vector<int>& piles, int h) 
{
    int n = piles.size();
    int lo = 1, hi = *max_element(piles.begin(), piles.end());

    while(lo < hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        int time = checkTime(piles, mid);
        if(time <= h) hi = mid;
        else lo = mid + 1;
    }

    return lo;
}

// DAY 9 (142. Linked List Cycle II)======================================================================

ListNode *detectCycle(ListNode *head) 
{
    ListNode* slow = head, *fast = head;
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(slow == fast) break;
    }
    if(!fast || !fast->next) return nullptr;

    slow = head;
    while(slow != fast)
    {
        fast = fast->next;
        slow = slow->next;
    }

    return fast;
}

// DAY 10 (382. Linked List Random Node)===================================================================

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
class Solution {
public:

    ListNode* head = nullptr;
    int n = 0;
    Solution(ListNode* head) 
    {
        this->head = head;
        ListNode* tmp = head;
        while(tmp)
        {
            n++;
            tmp = tmp->next;
        }
    }
    
    int getRandom() 
    {
        int x = rand() % n;
        ListNode* tmp = head;
        int ans = tmp->val;
        while(x--)
        {
            tmp = tmp->next;
            ans = tmp->val;
        }
        
        return ans;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */

// DAY 12 (23. Merge k Sorted Lists)=========================================================================================

ListNode* mergeKLists(vector<ListNode*>& lists) 
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    int k = lists.size();
    for(int i = 0; i < k; i++)
    {
        if(!lists[i]) continue;
        pq.push({lists[i]->val, i});
    }

    ListNode* head = new ListNode(INT_MIN), *itr = head;
    while(!pq.empty())
    {
        int x = pq.top().first;
        int i = pq.top().second;
        pq.pop();

        itr->next = new ListNode(x);
        itr = itr->next;
        if(lists[i]->next)
        {
            lists[i] = lists[i]->next;
            pq.push({lists[i]->val, i});
        }
    }

    return head->next;
}

// DAY 13 (101. Symmetric Tree)===============================================================================================

bool isSymmetricHelper(TreeNode* lptr, TreeNode* rptr)
{
    if(!lptr && !rptr) return true;
    if(!lptr || !rptr) return false;
    if(lptr->val != rptr->val) return false;

    return isSymmetricHelper(lptr->left, rptr->right)
        && isSymmetricHelper(lptr->right, rptr->left);
}

bool isSymmetric(TreeNode* root) 
{
    return isSymmetricHelper(root->left, root->right);
}

// DAY 14 (129. Sum Root to Leaf Numbers)======================================================================================

int ans = 0;
void dfs(TreeNode* node, long curr)
{
    if(!node) return;
    if(!node->left && !node->right)
    {
        ans += curr*10 + node->val;
        return;
    }

    dfs(node->left, curr*10 + node->val);
    dfs(node->right, curr*10 + node->val);
}

int sumNumbers(TreeNode* root) 
{
    dfs(root, 0);
    return ans;
}

// DAY 15 (958. Check Completeness of a Binary Tree)==============================================================================

int countNodes(TreeNode* node)
{
    return node? countNodes(node->left) + countNodes(node->right) + 1 : 0;
}

bool dfs(TreeNode* node, int idx, int tot)
{
    if(!node) return true;
    if(idx > tot) return false;

    return dfs(node->left, 2*idx, tot) && dfs(node->right, 2*idx+1, tot);
}

bool isCompleteTree(TreeNode* root) 
{
    int tot = countNodes(root);
    return dfs(root, 1, tot);
}

// DAY 16 (106. Construct Binary Tree from Inorder and Postorder Traversal)============================================================

unordered_map<int,int> mp;

TreeNode* construct(int &i, int l, int r, vector<int> &post)
{
    if(i == -1 || l > r) return nullptr;

    TreeNode* curr = new TreeNode(post[i]);
    int x = mp[post[i--]];

    if(l == r) return curr;

    curr->right = construct(i, x+1, r, post);
    curr->left = construct(i, l, x-1, post);

    return curr;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) 
{
    int n = inorder.size();
    for(int i = 0; i < n; i++)
        mp[inorder[i]] = i;

    int i = n-1;
    return construct(i, 0, n-1, postorder);
}

// DAY 17 (208. Implement Trie (Prefix Tree))================================================================================

class Node
{
    public:
    vector<Node*> trie;
    bool wordEnd;
    Node()
    {
        trie.assign(26, nullptr);
        this->wordEnd = false;
    }
};

class Trie {
public:

    Node* root;
    Trie() 
    {
        root = new Node();
    }
    
    void insert(string word) 
    {
        Node* tmp = root;
        for(char c : word)
        {
            if(!tmp->trie[c-'a'])
                tmp->trie[c-'a'] = new Node();
            tmp = tmp->trie[c-'a'];
        }
        tmp->wordEnd = true;
    }
    
    bool search(string word) 
    {
        Node* tmp = root;
        for(char c : word)
        {
            if(!tmp->trie[c-'a'])
                return false;
            tmp = tmp->trie[c-'a'];
        }
        return tmp->wordEnd;
    }
    
    bool startsWith(string prefix) 
    {
        Node* tmp = root;
        for(char c : prefix)
        {
            if(!tmp->trie[c-'a'])
                return false;
            tmp = tmp->trie[c-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

// DAY 18 (1472. Design Browser History)=============================================================================================

class BrowserHistory {
public:

    vector<string> history;
    int currPage;
    BrowserHistory(string homepage) 
    {
        history.push_back(homepage);
        currPage = 0;
    }
    
    void visit(string url) 
    {
        while(history.size() > currPage+1)
            history.pop_back();
        history.push_back(url);
        currPage++;
    }
    
    string back(int steps) 
    {
        currPage = max(0, currPage - steps);
        return history[currPage];
    }
    
    string forward(int steps) 
    {
        currPage = min((int)history.size()-1, currPage + steps);
        return history[currPage];
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */

// DAY 19 (211. Design Add and Search Words Data Structure)==============================================================================

class trie
{
    public:
    vector<trie*> t;
    bool wordEnd;
    trie()
    {
        this->t.assign(26, nullptr);
        this->wordEnd = false;
    }
};

class WordDictionary {
public:

    trie* root;
    WordDictionary() 
    {
        this->root = new trie();
    }
    
    void addWord(string word) 
    {
        trie* tmp = root;
        for(char c : word)
        {
            if(!tmp->t[c-'a'])
                tmp->t[c-'a'] = new trie();
            tmp = tmp->t[c-'a'];
        }
        tmp->wordEnd = true;
    }

    bool searchHelper(int i, trie* curr, string &word)
    {
        if(i == word.size()) return curr->wordEnd;
        if(word[i] != '.')
        {
            if(curr->t[word[i]-'a'])
                return searchHelper(i+1, curr->t[word[i]-'a'], word);
            else return false;
        }
        else 
        {
            for(int j = 0; j < 26; j++)
                if(curr->t[j] && searchHelper(i+1, curr->t[j], word))
                    return true;
            return false;
        }
    }
    
    bool search(string word) 
    {
        return searchHelper(0, root, word);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

// DAY 20 (605. Can Place Flowers)=====================================================================================

bool canPlaceFlowers(vector<int>& flowerbed, int n) 
{
    int avail = 0, z = 1;
    for(int i = 0; i < flowerbed.size(); i++)
    {
        if(flowerbed[i] == 0)
            z++;
        else 
        {
            avail += (z - 1) / 2;
            z = 0;
        }
    }

    return (avail + z/2) >= n;
}

// DAY 21 (2348. Number of Zero-Filled Subarrays)===================================================================

long long zeroFilledSubarray(vector<int>& nums) 
{
    int n = nums.size();
    long long ans = 0;
    for(int i = 0; i < n; )
    {
        if(nums[i] != 0)
        {
            i++;
            continue;
        }
        int j = i;
        while(j < n && nums[j] == 0)
            ans += (++j) - i;
        i = j;
    }

    return ans;
}

// DAY 22 (2492. Minimum Score of a Path Between Two Cities)=======================================================

// APPROACH 1 (DFS on Edges)

vector<vector<vector<int>>> gp;
unordered_set<int> vis;
int minDist = INT_MAX;
void findMinDist(int u)
{
    for(vector<int> &v : gp[u])
    {
        if(!vis.count(v[2]))
        {
            vis.insert(v[2]);
            minDist = min(minDist, v[1]);
            findMinDist(v[0]);
        }
    }
}

int minScore(int n, vector<vector<int>>& roads) 
{
    gp.resize(n+1);
    int edgeCode = 0;
    for(vector<int> &road : roads)
    {
        int u = road[0];
        int v = road[1];
        int w = road[2];
        gp[u].push_back({v, w, edgeCode});
        gp[v].push_back({u, w, edgeCode++});
    }

    findMinDist(1);

    return minDist;
}

// APPROACH 2 (Using DSU) --> MUCH OPTIMIZED

vector<int> par;
int findPar(int u)
{
    return par[u] == u? u : findPar(par[u]);
}

int minScore(int n, vector<vector<int>>& roads) 
{
    par.resize(n+1);
    for(int i = 1; i <= n; i++)
        par[i] = i;
    vector<int> minDist(n+1, INT_MAX);
    for(vector<int> &road : roads)
    {
        int u = road[0];
        int v = road[1];
        int w = road[2];

        int pu = findPar(u);
        int pv = findPar(v);
        if(pu > pv) swap(pu, pv);
        par[pv] = pu;

        minDist[pu] = min({minDist[pu], minDist[pv], w});
    }

    return minDist[findPar(n)];
}

// DAY 23 (1319. Number of Operations to Make Network Connected)====================================================================

vector<int> par;
int findPar(int u)
{
    return par[u] = (par[u] == u)? u : findPar(par[u]);
}

int makeConnected(int n, vector<vector<int>>& connections) 
{
    if(connections.size() < n-1) return -1;
    par.resize(n);
    int ans = n - 1;
    for(int i = 0; i < n; i++) par[i] = i;

    for(vector<int> &connection : connections)
    {
        int p1 = findPar(connection[0]);
        int p2 = findPar(connection[1]);
        if(p1 == p2)
            continue;
        ans--;
        if(p1 > p2) swap(p1, p2);
        par[p2] = p1;
    }

    return ans;
}

// DAY 24 (1466. Reorder Routes to Make All Paths Lead to the City Zero)===================================================================

int rev = 0;
void dfs(int p, int u, vector<vector<vector<int>>> &gp)
{
    for(vector<int> &v : gp[u])
    {
        if(v[0] == p) continue;
        rev += v[1];
        dfs(u, v[0], gp);
    }
}

int minReorder(int n, vector<vector<int>>& connections) 
{
    vector<vector<vector<int>>> gp(n);
    for(vector<int> &e : connections)
    {
        gp[e[0]].push_back({e[1], 1}); // gp[x][2] = 1 : valid edge
        gp[e[1]].push_back({e[0], 0}); // gp[x][2] = 0 : invalid edge
    }

    dfs(-1, 0, gp);
    return rev;
}

// DAY 25 (2316. Count Unreachable Pairs of Nodes in an Undirected Graph)=============================================================================

// APPROACH 1 (DFS)

vector<vector<int>> gp;
int dfs(int u, vector<bool> &vis)
{
    vis[u] = true;
    int count = 0;
    for(int v : gp[u])
        if(!vis[v])
            count += dfs(v, vis);
    return count + 1;
}

long long unreachablePairs(int tsum, vector<int> &comps)
{
    long long ans = 0;
    for(int x : comps)
    {
        tsum -= x;
        ans += (long long) tsum * x;
    }
    return ans;
}

long long countPairs(int n, vector<vector<int>>& edges) 
{
    vector<int> comps;
    gp.resize(n);
    for(vector<int> &e : edges)
    {
        gp[e[0]].push_back(e[1]);
        gp[e[1]].push_back(e[0]);
    }

    vector<bool> vis(n);
    for(int i = 0; i < n; i++)
        if(!vis[i])
            comps.push_back(dfs(i, vis));

    return unreachablePairs(n, comps);
}

// APPROACH 2 (DSU)

vector<vector<int>> gp;
vector<int> par;
vector<int> parSize;

int findPar(int u)
{
    return par[u] = (par[u] == u)? u : findPar(par[u]);
}

void unionBySize(int u, int v)
{
    int pu = findPar(u);
    int pv = findPar(v);

    if(pu == pv) return;
    if(pu > pv) swap(pu, pv);

    par[pv] = pu;
    parSize[pu] += parSize[pv];
}

long long countPairs(int n, vector<vector<int>>& edges) 
{
    vector<int> comps;
    gp.resize(n);
    par.resize(n);
    parSize.assign(n, 1);
    for(int i = 0; i < n; i++)
        par[i] = i;
    for(vector<int> &e : edges)
    {
        gp[e[0]].push_back(e[1]);
        gp[e[1]].push_back(e[0]);
        unionBySize(e[0], e[1]);
    }

    long long ans = 0;
    for(int i = 0; i < n; i++)
    {
        int pi = findPar(i);
        ans += n - parSize[findPar(i)];
    }

    return ans/2;
}

// DAY 26 (2360. Longest Cycle in a Graph)============================================================================

int maxCycle = -1;
int longestCycle(vector<int>& edges) 
{
    int n = edges.size();
    vector<int> visTime(n, 0);
    int time = 1;
    for(int u = 0; u < n; u++)
    {
        if(visTime[u]) continue;

        int v = u;
        int startTime = time;
        while(v != -1 && visTime[v] == 0)
        {
            visTime[v] = time++;
            v = edges[v];
        }
        if(v != -1 && visTime[v] >= startTime)
            maxCycle = max(maxCycle, time - visTime[v]);
    }

    return maxCycle;
}

// DAY 27 (64. Minimum Path Sum)==============================================================================================

int minPathSum(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    for(int i = n-1; i >= 0; i--)
    {
        for(int j = m-1; j >= 0; j--)
        {
            int down = i == n-1? INT_MAX : dp[i+1][j];
            int right = j == m-1? INT_MAX : dp[i][j+1];
            int restPathMin = min(right, down);
            dp[i][j] = grid[i][j] + (restPathMin == INT_MAX? 0 : restPathMin);
        }
    }

    return dp[0][0];
}

// DAY 28 (983. Minimum Cost For Tickets)============================================================================

int mincostTickets(vector<int>& days, vector<int>& costs) 
{
    int N = 365;
    vector<int> minCost(N+2, 0);
    for(int day = N, j = days.size()-1; day; day--)
    {
        if(j == -1 || days[j] < day)
        {
            minCost[day] = minCost[day+1];
            continue;
        }
        int oneDayPassCost = costs[0] + ((day + 1 <= N+1)? minCost[day + 1] : 0);
        int sevenDayPassCost = costs[1] + ((day + 7 <= N+1)? minCost[day + 7] : 0);
        int thirtyDayPassCost = costs[2] + ((day + 30 <= N+1)? minCost[day + 30] : 0);

        minCost[day] = min({oneDayPassCost, sevenDayPassCost, thirtyDayPassCost});
        j--;
    }

    return minCost[1];
}

// DAY 30 (1402. Reducing Dishes)=======================================================================================

// APPROACH 1 (Using DP (Memoization)) --> time = O(n^2)

int dfs(int i, int x, vector<int>& satisfaction, vector<vector<int>> &dp)
{
    if(i == satisfaction.size()) return 0;
    if(dp[i][x] != INT_MIN) return dp[i][x];
    return dp[i][x] = max(dfs(i+1, x+1, satisfaction, dp) + x * satisfaction[i],
                dfs(i+1, x, satisfaction, dp));
}

int maxSatisfaction(vector<int>& satisfaction) 
{
    int n = satisfaction.size();
    sort(satisfaction.begin(), satisfaction.end());
    vector<vector<int>> dp(n, vector<int>(n+1, INT_MIN));
    return dfs(0, 1, satisfaction, dp);
}

// APPROACH 2 (Mathematically) --> time = O(n)

int maxSatisfaction(vector<int>& satisfaction) 
{
    sort(satisfaction.rbegin(), satisfaction.rend());
    int sum = 0, ans = 0;
    for(int x : satisfaction)
    {
        ans = max(ans, ans + sum + x);
        sum += x;
    }

    return ans;
}

// DAY 30 (87. Scramble String)===================================================================================================

unordered_map<string,bool> dp;
bool isScramble(string s1, string s2) 
{

    if(s1 == s2) return true;

    int n = s1.size();
    string key = s1 + " " + s2;
    if(dp.count(key)) return dp[key];

    for(int i = 1; i < s1.size(); i++)
    {
        if(isScramble(s1.substr(0, i), s2.substr(0, i)) && 
            isScramble(s1.substr(i), s2.substr(i)))
            return dp[key] = true;
        if(isScramble(s1.substr(0, i), s2.substr(n-i)) && 
            isScramble(s1.substr(i), s2.substr(0, n-i)))
            return dp[key] = true;
    }

    return dp[key] = false;
}

// DAY 31 (1444. Number of Ways of Cutting a Pizza)==============================================================================

int mod = 1e9 + 7;
int dfs(int i, int j, int n, int m, int k, vector<vector<int>> &psum, vector<vector<vector<int>>> &dp)
{
    if(psum[i][j] == 0) return 0;
    if(k == 0) return 1;
    if(dp[i][j][k] != -1) return dp[i][j][k];

    int ways = 0;
    for(int ii = i+1; ii < n; ii++)
    {
        if(psum[i][j] - psum[ii][j] > 0)
            ways = ways % mod + dfs(ii, j, n, m, k-1, psum, dp) % mod % mod;
    }
    for(int jj = j+1; jj < m; jj++)
    {
        if(psum[i][j] - psum[i][jj] > 0)
            ways = ways % mod + dfs(i, jj, n, m, k-1, psum, dp) % mod % mod;
    }

    return dp[i][j][k] = ways;
}

int ways(vector<string>& pizza, int k) 
{
    int n = pizza.size(), m = pizza[0].size();
    vector<vector<int>> psum(n+1, vector<int>(m+1,0));
    for(int i = n-1; i >= 0; i--)
    {
        for(int j = m-1; j >= 0; j--)
        {
            psum[i][j] = (pizza[i][j] == 'A') + 
                psum[i+1][j] + psum[i][j+1] - psum[i+1][j+1];
        }
    }

    vector<vector<vector<int>>> dp(n, vector<vector<int>> (m, vector<int> (k, -1)));
    return dfs(0, 0, n, m, k-1, psum, dp);
}
