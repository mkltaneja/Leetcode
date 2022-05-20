// DAY 1 (844. Backspace String Compare)=========================================================================================================================

bool backspaceCompare(string s, string t) 
{
    int i = s.size() - 1, j = t.size() - 1;
    while(i >= 0 || j >= 0)
    {
        int bs = 0, bt = 0;
        while(i >= 0 && s[i] == '#') bs++, i--;
        while(j >= 0 && t[j] == '#') bt++, j--;

        while(i >= 0 && bs)
        {
            if(s[i] == '#') bs++;
            else bs--;
            i--;
        }
        while(j >= 0 && bt)
        {
            if(t[j] == '#') bt++;
            else bt--;
            j--;
        }

        if(i >= 0 && j >= 0 && s[i] != '#' && t[j] != '#')
            if(s[i] != t[j])
                return false;
            else i--, j--;
        else if(((i >= 0 && j < 0 && s[i] != '#') || (j >= 0 && i < 0 && t[j] != '#')))
            return false;
    }

    return true;
}

// DAY 2 (905. Sort Array By Parity)=========================================================================================================================

vector<int> sortArrayByParity(vector<int>& nums) 
{
    int i = 0, j = 0;
    while(i < nums.size())
    {
        if(nums[i] & 1 ^ 1) 
            swap(nums[i], nums[j++]);
        i++;
    }
    return nums;
}

// DAY 5 (225. Implement Stack using Queues)=========================================================================================================================

// APPROACH 1 (Using 2 queues)
class MyStack {
public:
    
    queue<int> q1, q2;
    MyStack() {
        
    }
    
    void push(int x) 
    {
        q2.push(x);
        while(!q1.empty())
        {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }
    
    int pop() 
    {
        int x = q1.front();
        q1.pop();
        return x;
    }
    
    int top() 
    {
        return q1.front();
    }
    
    bool empty() 
    {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

// APPROACH 2 (Using 1 queue)
class MyStack {
public:
    
    queue<int> q;
    int size;
    MyStack() 
    {
        this->size = 0;
    }
    
    void push(int x) 
    {
        q.push(x);
        int tmp = size;
        while(tmp--)
        {
            q.push(q.front());
            q.pop();
        }
        size++;
    }
    
    int pop() 
    {
        int x = q.front();
        q.pop();
        size--;
        return x;
    }
    
    int top() 
    {
        return q.front();
    }
    
    bool empty() 
    {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

// DAY 6 (1209. Remove All Adjacent Duplicates in String II)=========================================================================================================================

string removeDuplicates(string s, int k) 
{
    stack<pair<char, int>> st;
    for(char c : s)
    {
        st.push((!st.empty() && st.top().first==c)? make_pair(c, st.top().second+1) : make_pair(c,1));
        if(st.top().second == k)
            while(!st.empty() && st.top().first == c)
                st.pop();
    }
    string ans = "";
    while(!st.empty())
    {
        ans += st.top().first;
        st.pop();
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

// DAY 7 (456. 132 Pattern)=========================================================================================================================

bool find132pattern(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> mn(n);
    mn[0] = nums[0];
    for(int i = 1; i < n; i++)
        mn[i] = min(mn[i-1], nums[i]);

    stack<int> st;
    for(int i = n-1; i >= 0; i--)
    {
        while(!st.empty() && st.top() < nums[i])
        {
            if(st.top() > mn[i])
                return true;
            st.pop();
        }
        st.push(nums[i]);
    }

    return false;
}

// DAY 8 (341. Flatten Nested List Iterator)=========================================================================================================================

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
public:
    
    int itr = 0;
    vector<int> list;
    void flatten(vector<NestedInteger> &nlist)
    {
        for(int i = 0; i < nlist.size(); i++)
        {
            if(!nlist[i].isInteger())
                flatten(nlist[i].getList());
            else list.push_back(nlist[i].getInteger());
        }
    }
    
    NestedIterator(vector<NestedInteger> &nestedList) 
    {
        flatten(nestedList);
    }
    
    int next()
    {
        return list[itr++];
    }
    
    bool hasNext() 
    {
        return itr < list.size();
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

// DAY 9 (17. Letter Combinations of a Phone Number)=========================================================================================================================

vector<string> map = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

vector<string> ans;
void dfs(int i, string tmp, string &dig)
{
    if(i == dig.size()) 
    {
        if(!tmp.empty()) ans.push_back(tmp);
        return;
    }        
    for(int j = 0; j < map[dig[i]-'0'].size(); j++)
        dfs(i+1, tmp+map[dig[i]-'0'][j], dig);
}

vector<string> letterCombinations(string digits) 
{
    dfs(0, "", digits);
    return ans;
}

// DAY 10 (216. Combination Sum III)=========================================================================================================================

vector<vector<int>> ans;
void dfs(vector<int> &curr, int last, int k, int n)
{
    if(k == 0 && n == 0)
    {
        ans.push_back(curr);
        return;
    }

    for(int x = last; x <= 9 && n-x >= 0; x++)
    {
        curr.push_back(x);
        dfs(curr, x+1, k-1, n-x);
        curr.pop_back();
    }
}

vector<vector<int>> combinationSum3(int k, int n) 
{
    vector<int> curr;
    dfs(curr, 1, k, n);
    return ans;
}

// DAY 11 (1641. Count Sorted Vowel Strings)=========================================================================================================================

int dfs(int x, int n, vector<vector<int>> &dp)
{
    if(n == 0) return dp[n][x] = 1;
    if(dp[n][x]) return dp[n][x];

    int ans = 0;
    for(int y = x; y < 5; y++)
        ans += dfs(y, n-1, dp);

    return dp[n][x] = ans;
}

int countVowelStrings(int n) 
{
    vector<vector<int>> dp(n+1, vector<int>(5));
    return dfs(0, n, dp);
}

// DAY 12 (47. Permutations II)=========================================================================================================================

vector<vector<int>> permuteUnique(vector<int>& nums) 
{
    sort(nums.begin(), nums.end());
    set<vector<int>> st;
    do 
    {
        st.insert(nums);
    }
    while(next_permutation(nums.begin(), nums.end()));

    vector<vector<int>> ans;
    for(vector<int> v : st)
        ans.push_back(v);

    return ans;
}

// DAY 13 (117. Populating Next Right Pointers in Each Node II)=========================================================================================================================

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) 
    {
        if(!root) return root;
        queue<Node*> que;
        que.push(root);
        
        while(!que.empty())
        {
            int sz = que.size();
            while(sz--)
            {
                Node* node = que.front();
                que.pop();
                if(sz) node->next = que.front();
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
        }
        
        return root;
    }
};

// DAY 14 (743. Network Delay Time)=========================================================================================================================

int bfs(int u, int n, vector<vector<pair<int,int>>> &graph)
{
    vector<int> vis(n+1, false);
    queue<pair<int,int>> que;
    que.push({u, 0});

    vector<int> time(n+1, INT_MAX);
    time[0] = -1;
    time[u] = 0;
    while(!que.empty())
    {
        int u = que.front().first;
        int tsf = que.front().second;
        que.pop();

        for(pair<int,int> p : graph[u])
        {
            int v = p.first;
            int t = p.second;

            if(tsf + t < time[v])
            {
                time[v] = tsf + t;
                que.push({v, tsf + t});
            }
        }
    }

    int maxtime = 0;
    for(int t : time)
    {
        if(t == INT_MAX)
            return -1;
        maxtime = max(maxtime, t);
    }

    return maxtime;
}

int networkDelayTime(vector<vector<int>>& times, int n, int k) 
{
    vector<vector<pair<int,int>>> graph(n+1);
    for(vector<int> edge : times)
        graph[edge[0]].push_back({edge[1], edge[2]});


    return bfs(k, n, graph);
}

// DAY 15 (1302. Deepest Leaves Sum)=========================================================================================================================

int mxh = -1, sum = 0;
void dfs(int h, TreeNode* node)
{
    if(!node) return;

    if(h > mxh) mxh = h, sum = node->val;
    else if(h == mxh) sum += node->val;

    dfs(h+1, node->left);
    dfs(h+1, node->right);
}

int deepestLeavesSum(TreeNode* root) 
{
    dfs(0, root);

    return sum;
}

// DAY 16 (1091. Shortest Path in Binary Matrix)=========================================================================================================================

#define f first
#define s second

int shortestPathBinaryMatrix(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();
    if(grid[0][0] == 1 || grid[n-1][m-1] == 1) return -1;

    int dir[8][2] = {{1,0},{0,1},{1,1},{-1,0},{0,-1},{-1,-1},{1,-1},{-1,1}};

    queue<pair<pair<int,int>,int>> que;
    que.push({{0,0},1});

    while(!que.empty())
    {
        auto tp = que.front();
        que.pop();
        int r = tp.f.f, c = tp.f.s;

        if(r == n-1 && c == m-1) return tp.s;

        for(int d = 0; d < 8; d++)
        {
            int x = r + dir[d][0], y = c + dir[d][1];
            if(x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 0)
            {
                grid[x][y] = 1;
                que.push({{x,y}, tp.s + 1});
            }
        }
    }

    return -1;
}

// DAY 17 (1379. Find a Corresponding Node of a Binary Tree in a Clone of That Tree)=========================================================================================================================

TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) 
{
    if(!cloned) return nullptr;
    if(cloned->val == target->val) return cloned;

    TreeNode* lans = getTargetCopy(original, cloned->left, target);
    if(lans) return lans;
    TreeNode* rans = getTargetCopy(original, cloned->right, target);
    if(rans) return rans;

    return nullptr;
}

// DAY 18 (1192. Critical Connections in a Network)=========================================================================================================================

vector<vector<int>> graph;
vector<int> disc;
vector<int> low;
vector<int> par;
vector<vector<int>> ans;
int time = 0;

void tarjansAlgo(int u, vector<vector<int>> &graph)
{
    disc[u] = low[u] = time++;
    for(int v : graph[u])
    {
        if(disc[v] == -1)
        {
            par[v] = u;
            tarjansAlgo(v, graph);
            low[u] = min(low[u], low[v]);
            if(low[v] > disc[u])
                ans.push_back({u, v});
        }
        else if(par[u] != v) low[u] = min(low[u], disc[v]);
    }
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) 
{
    graph.resize(n);
    disc.resize(n,-1);
    low.resize(n);
    par.resize(n);
    for(vector<int> e : connections)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    for(int x = 0; x < n; x++)
        if(disc[x] == -1)
            tarjansAlgo(x, graph);

    return ans;
}

// DAY 20 (63. Unique Paths II)=========================================================================================================================

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
{
    int n = obstacleGrid.size(), m = obstacleGrid[0].size();
    if(obstacleGrid[0][0] || obstacleGrid[n-1][m-1]) return 0;

    vector<vector<long>> dp(n, vector<long> (m,0));
    dp[n-1][m-1] = 1;

    for(int i = n-1; i >= 0; i--)
    {
        for(int j = m-1; j >= 0; j--)
        {
            if((i == n-1 && j == m-1) || obstacleGrid[i][j]) continue;
            long dans = i+1 < n? dp[i+1][j] : 0;
            long rans = j+1 < m? dp[i][j+1] : 0;
            dp[i][j] = dans + rans;
        }
    }
    return dp[0][0];
}
