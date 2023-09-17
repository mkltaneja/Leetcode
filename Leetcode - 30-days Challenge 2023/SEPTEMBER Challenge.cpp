
// DAY 1 (338. Counting Bits)====================================================================================================

// METHOD 1 (By Dividing numbers into segments - 2-3, 4-7, 8-15...) --> time = O(n), space = O(n)

vector<int> countBits(int n) 
{
    vector<int> ans(n+1, 0);
    
    if(n == 0) return ans;
    
    ans[1] = 1;
    int start = 0, end = 0, itr = 0, time = 0;
    for(int x = 2; x <= n; x++)
    {
        if((x & (x - 1)) == 0)
        {
            start = x / 2;
            itr = start;
            end = x - 1;
            time = 0;
        }
        ans[x] = ans[itr++] + time;
        if(itr == end+1)
        {
            itr = start;
            time++;
        }
    }

    return ans;
}

// METHOD 2 (Using FACT - odd num has 1 bit more than its half, and even num has equal) --> time = O(n), space = O(n)

vector<int> countBits(int n) 
{
    vector<int> ans(n+1, 0);
    if(n == 0) return ans;
    
    ans[1] = 1;
    for(int x = 2; x <= n; x++)
        ans[x] += ans[x >> 1] + (x & 1);

    return ans;
}

// METHOD 3 (Using FACT - Every num (x) has 1 more bit than its (x & (x-1))) --> time = O(n), space = O(n)

vector<int> countBits(int n) 
{
    vector<int> ans(n+1, 0);
    if(n == 0) return ans;
    
    ans[1] = 1;
    for(int x = 2; x <= n; x++)
        ans[x] += ans[x & (x-1)] + 1;

    return ans;
}

// DAY 2 (2707. Extra Characters in a String)====================================================================================

class Trie
{
    public:
    vector<Trie*> child;
    bool wordEnd;
    Trie()
    {
        this->child.assign(26, nullptr);
        this->wordEnd = false;
    }

    void insert(Trie* t, string &s)
    {
        Trie* tmp = t;
        for(char c : s)
        {
            if(!tmp->child[c-'a'])
                tmp->child[c-'a'] = new Trie();
            tmp = tmp->child[c-'a'];
        }
        tmp->wordEnd = true;
    }
};
Trie* root = new Trie();

// map<pair<int,Trie*>, int> dp;
// Note: We don't need above kind of DP, as we don't have dependency over Trie node for every index, as we are just calling for the root at every call
int dfs(int i, Trie* itr, string &s, vector<int> &dp)
{
    if(i == s.size()) return 0;
    if(dp[i] != -1) return dp[i];

    int ans = dfs(i+1, root, s, dp) + 1;
    for(int j = i; j < s.size(); j++)
    {
        Trie* nxt = itr->child[s[j]-'a'];
        if(!nxt) break;

        if(nxt->wordEnd)
            ans = min(ans, dfs(j+1, root, s, dp));
        itr = nxt;
    }
    return dp[i] = ans;
}

int minExtraChar(string s, vector<string>& dictionary) 
{
    for(string &word : dictionary)
        root->insert(root, word);
    
    vector<int> dp(s.size(), -1);
    return dfs(0, root, s, dp);
}

// DAY 3 (62. Unique Paths)============================================================================

int uniquePaths(int m, int n) 
{
    vector<vector<int>> dp(m, vector<int> (n, 0));
    dp[m-1][n-1] = 1;
    for(int i = m-1; i >= 0; i--)
    {
        for(int j = n-1; j >= 0; j--)
        {
            int rightWays = j == n-1? 0 : dp[i][j+1];
            int downWays = i == m-1? 0 : dp[i+1][j];
            dp[i][j] += rightWays + downWays;
        }
    }

    return dp[0][0];
}

// DAY 4 (141. Linked List Cycle)=============================================================================================

bool hasCycle(ListNode *head) 
{
    ListNode* fast = head, *slow = head;
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(slow == fast) return true;
    }
    return false;
}

// DAY 5 (138. Copy List with Random Pointer)================================================================================

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) 
    {
        unordered_map<Node*, Node*> nodeMap;
        Node* itr = head;
        Node* ans = new Node(0), *ansItr = ans;
        while(itr)
        {
            ansItr->next = new Node(itr->val);

            nodeMap[itr] = ansItr->next;

            itr = itr->next;
            ansItr = ansItr->next;
        }

        ans = ans->next, ansItr = ans, itr = head;

        while(ansItr)
        {
            ansItr->random = nodeMap[itr->random];
            itr = itr->next;
            ansItr = ansItr->next;
        }

        return ans;
    }
};

// DAY 6 (725. Split Linked List in Parts)================================================================================================

vector<ListNode*> splitListToParts(ListNode* head, int k) 
{
    int size = 0;
    ListNode* itr = head;
    while(itr)
    {
        size++;
        itr = itr->next;
    }

    int partSize = size / k;
    int extras = size % k;
    itr = head;
    vector<ListNode*> ans;
    while(ans.size() < k)
    {
        ListNode* curr = itr;
        for(int nodes = 1; nodes <= partSize-1; nodes++)
            itr = itr->next;
        if(extras-- > 0 && partSize)
            itr = itr->next;

        ans.push_back(curr);

        if(itr)
        {
            ListNode* nxt = itr->next;
            itr->next = nullptr;
            itr = nxt;
        }
    }

    return ans;
}

// DAY 7 (92. Reverse Linked List II)=======================================================================================

ListNode* reverseBetween(ListNode* head, int left, int right) 
{
    ListNode* curr = nullptr, *prev = nullptr, *forw = nullptr;
    ListNode* itr = head, *last = nullptr, *rangeStart = head;
    int index = 1;
    while(itr)
    {
        bool inRange = false;
        if(index == left)
        {
            rangeStart = itr;
            prev = itr;
            curr = itr->next;
        }
        else if(index >= left && index <= right)
        {
            forw = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forw;
            itr = forw;
            inRange = true;
        }
        else if(index == left - 1)
            last = itr;
        else if(index == right + 1)
        {
            if(last) 
                last->next = prev;
            rangeStart->next = itr;
        }
        
        if(!inRange)
            itr = itr->next;
        index++;
    }
    if(left == 1)
        head = prev;
    if(right == index-1)
    {
        if(last)
            last->next = prev;
        rangeStart->next = nullptr;
    }

    return head;
}

// DAY 8 (118. Pascal's Triangle)============================================================================================

vector<vector<int>> generate(int numRows) 
{
    vector<vector<int>> ans(numRows);
    for(int i = 0; i < numRows; i++)
    {
        ans[i].resize(i+1);
        for(int j = 0; j <= i; j++)
            ans[i][j] = (j == 0 || j == i)? 1 : (ans[i-1][j-1] + ans[i-1][j]);
    }

    return ans;
}

// DAY 9 (377. Combination Sum IV)=================================================================================================

int combinationSum4(vector<int>& nums, int target) 
{
    vector<unsigned int> dp(target+1, 0);
    sort(nums.begin(), nums.end());
    dp[0] = 1;
    for(int tar = 1; tar <= target; tar++)
        for(int i = 0; i < nums.size() && nums[i] <= tar; i++)
            dp[tar] += dp[tar - nums[i]];
    return dp[target];
}

// DAY 10 (1359. Count All Valid Pickup and Delivery Options)==============================================================================================================

int mod = 1e9 + 7;
int countOrders(int n) 
{
    long ans = 1;
    for(int x = 2; x <= n; x++)
        ans = (ans * (2*x * (2*x - 1) / 2)) % mod;  // After placing (x-1) P-D pairs,  2*(x-1) + 1 = 2*x - 1 places are remaining to place the xth pair. Then after placing Px, we have ∑2i-1 (1 <= i <= x) combinations

    return ans;
}

// DAY 11 (1282. Group the People Given the Group Size They Belong To)===========================================================================================

// METHOD 1 (Using 3D vector)

vector<vector<int>> groupThePeople(vector<int>& groupSizes) 
{
    int n = groupSizes.size();
    vector<vector<vector<int>>> gsize(n+1);
    int person = 0;
    for(int size : groupSizes)
    {
        if(gsize[size].empty() || gsize[size].back().size() == size)
        {
            vector<int> newGroup(1, person++);
            gsize[size].push_back(newGroup);
        }
        else gsize[size].back().push_back(person++);
    }

    vector<vector<int>> ans;
    for(int size = 1; size <= n; size++)
    {
        while(!gsize[size].empty())
        {
            ans.push_back(gsize[size].back());
            gsize[size].pop_back();
        }
    }
    return ans;
}

// METHOD 2 (Without 3D vector)

vector<vector<int>> groupThePeople(vector<int>& groupSizes) 
{
    int n = groupSizes.size();
    vector<vector<int>> gsize(n+1);
    for(int person = 0; person < n; person++)
        gsize[groupSizes[person]].push_back(person);

    vector<vector<int>> ans;
    for(int size = 1; size <= n; size++)
    {
        vector<int> tmp;
        while(!gsize[size].empty())
        {
            tmp.push_back(gsize[size].back());
            gsize[size].pop_back();
            if(tmp.size() == size)
            {
                ans.push_back(tmp);
                tmp.clear();
            }
        }
    }
    return ans;
}

// DAY 12 (1647. Minimum Deletions to Make Character Frequencies Unique)=======================================================================================

int minDeletions(string s) 
{
    int n = s.size();
    vector<int> countMap(26, 0);
    for(char c : s)
        countMap[c-'a']++;
    
    sort(countMap.rbegin(), countMap.rend());
    int deletions = 0;
    for(int i = 1; i < 26 && countMap[i]; i++)
    {
        if(countMap[i] < countMap[i-1]) continue;

        int prevCount = countMap[i];
        countMap[i] = max(countMap[i-1] - 1, 0);
        deletions += prevCount - countMap[i];
    }
    
    return deletions;
}

// DAY 13 (135. Candy)====================================================================================

// APPROACH 1 (Getting current answer by previously-stored answers) --> time = O(n + n*logn), space = O(n)

int candy(vector<int>& ratings) 
{
    int n = ratings.size();
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for(int i = 0; i < n; i++)
        pq.push({ratings[i], i});
    
    vector<int> candies(n, 0);
    int totalCandies = 0;
    while(!pq.empty())
    {
        int rating = pq.top().first;
        int idx = pq.top().second;
        pq.pop();

        int lval = idx && ratings[idx-1] != ratings[idx]? candies[idx-1] : 0;
        int rval = idx != n-1 && ratings[idx+1] != ratings[idx]? candies[idx+1] : 0;
        candies[idx] = max(lval, rval) + 1;
        totalCandies += candies[idx];
    }
    return totalCandies;
}

// APPROACH 2 (Getting current answer by previously-stored answers) --> time = O(3*n), space = O(n) [OPTIMIZED]

int candy(vector<int>& ratings) 
{
    int n = ratings.size();
    int totalCandies = 0;
    vector<int> candies(n, 1);
    for(int i = 1; i < n; i++)
        if(ratings[i] > ratings[i-1])
            candies[i] = candies[i-1] + 1;
    for(int i = n-2; i >= 0; i--)
        if(ratings[i] > ratings[i+1])
            candies[i] = max(candies[i], candies[i+1] + 1);
    for(int i = 0; i < n; i++)
        totalCandies += candies[i];

    return totalCandies;
}

// DAY 14 (332. Reconstruct Itinerary)======================================================================================================

void dfs(string src, unordered_map<string, priority_queue<string, vector<string>, greater<string>>> &gp, vector<string> &ans)
{
    while(!gp[src].empty())
    {
        string dest = gp[src].top();
        gp[src].pop();
        dfs(dest, gp, ans);
    }
    ans.push_back(src);
}

vector<string> findItinerary(vector<vector<string>>& tickets) 
{
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> gp;
    for(vector<string> &ticket : tickets)
        gp[ticket[0]].push(ticket[1]);
    
    vector<string> ans;
    dfs("JFK", gp, ans);
    reverse(ans.begin(), ans.end());
    
    return ans;
}

// DAY 15 (1584. Min Cost to Connect All Points)=========================================================================================================

int minCostConnectPoints(vector<vector<int>>& points)
{
    int n = points.size();
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, 0});
    int minCost = 0;
    vector<bool> vis(n, false);

    while(!pq.empty())
    {
        int wt = pq.top().first;
        int src = pq.top().second;
        pq.pop();

        if(vis[src]) continue;
        vis[src] = true;
        minCost += wt;

        for(int dest = 0; dest < n; dest++)
            if(!vis[dest])
                pq.push({abs(points[src][0] - points[dest][0]) + abs(points[src][1] - points[dest][1]), dest});
    }

    return minCost;
}

// DAY 17 (847. Shortest Path Visiting All Nodes)========================================================================================

int shortestPathLength(vector<vector<int>>& graph) 
{
    int n = graph.size();
    vector<vector<int>> vis(n, vector<int> ((1 << n), 0));
    queue<pair<int, int>> que;
    for(int i = 0; i < n; i++)
    {
        que.push({i, (1 << i)});
        vis[i][(1 << i)] = 1;
    }
    int allVis = (1 << n) - 1;
    
    int traversals = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int src = que.front().first;
            int mask = que.front().second;
            que.pop();
            for(int dest : graph[src])
            {
                int newMask = mask | (1 << dest);
                if(newMask == allVis)
                    return traversals + 1;
                if(!vis[dest][newMask])
                {
                    vis[dest][newMask] = 1;
                    que.push({dest, newMask});
                }
            }
        }
        traversals++;
    }

    return 0;
}
