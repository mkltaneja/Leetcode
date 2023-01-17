// DAY 1 (290. Word Pattern)================================================================================

bool wordPattern(string pattern, string s) 
{
    vector<string> map(26, "#");
    unordered_set<string> vis;
    int j = 0;
    for(int i = 0; i < pattern.size(); i++)
    {
        string curr = "";
        while(j < s.size() && s[j] != ' ') curr += s[j++];
        j++;
        cout<<pattern[i]<<" -> "<<curr<<endl;
        if(map[pattern[i]-'a'] == curr) continue;
        if(curr.empty() || vis.count(curr)) return false;
        if(map[pattern[i]-'a'] == "#")
        {
            vis.insert(curr);
            map[pattern[i]-'a'] = curr;
        }
        else return false;
    }

    return j == s.size()+1;
}

// DAY 2 (520. Detect Capital)==================================================================================

bool isCap(char &c)
{
    return c >= 'A' && c <= 'Z';
}

bool detectCapitalUse(string word) 
{
    int caps = 0;
    for(char &c : word)
        if(isCap(c))
            caps++;
    return caps == word.size() || caps == 0 || (caps == 1 && isCap(word[0]));
}

// DAY 3 (944. Delete Columns to Make Sorted)====================================================================

int minDeletionSize(vector<string>& strs) 
{
    int dels = 0;
    int n = strs.size(), m = strs[0].size();
    for(int i = 0; i < m; i++)
    {
        for(int j = 1; j < n; j++)
        {
            if(strs[j][i] < strs[j-1][i])
            {
                dels++;
                break;
            }
        }
    }

    return dels;
}

// DAY 4 (2244. Minimum Rounds to Complete All Tasks)=====================================================================

int minimumRounds(vector<int>& tasks) 
{
    unordered_map<int,int> mp;
    for(int &x : tasks)
        mp[x]++;

    int ans = 0;
    for(auto &p : mp)
    {
        if(p.second == 1) return -1;
        ans += (p.second/3) + (p.second%3 > 0);
    }

    return ans;
}

// DAY 5 (452. Minimum Number of Arrows to Burst Balloons)===================================================================

int findMinArrowShots(vector<vector<int>>& points) 
{
    sort(points.begin(), points.end());
    int currEnd = INT_MAX, i = 0, n = points.size(), arrows = 0;
    while(i < n)
    {
        while(i < n && points[i][0] <= currEnd)
            currEnd = min(currEnd, points[i++][1]);
        if(i < n) currEnd = points[i][1];
        arrows++;
    }

    return arrows;
}

// DAY 6 (1833. Maximum Ice Cream Bars)======================================================================================

int maxIceCream(vector<int>& costs, int coins) 
{
    int maxCost = 0, n = costs.size();
    for(int &x : costs)
        maxCost = max(maxCost, x);

    vector<int> costCount(maxCost+1, 0);
    for(int &x : costs)
        costCount[x]++;

    int iceCreams = 0;
    for(int i = 1; i <= maxCost && coins >= i; i++)
    {
        int count = min(coins/i, costCount[i]);
        iceCreams += count;
        coins -= count * i;
    }

    return iceCreams;
}

// DAY 7 (134. Gas Station)=========================================================================================

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
{
    int n = gas.size();
    int i = 0, prevSum = 0, currSum = 0, totSum = 0;
    int ans = -1;
    while(i < n)
    {
        int val = gas[i] - cost[i];
        currSum += val;
        if(currSum < 0) 
        {
            ans = -1;
            currSum = 0;
        }
        else if(ans == -1) 
        {
            ans = i;
            prevSum = totSum;
        }
        totSum += val;
        i++;
    }

    return (ans == -1 || (currSum + prevSum < 0))? -1 : ans;
}

// DAY 8 (149. Max Points on a Line)========================================================================================

double findSlope(vector<int> &a, vector<int> &b)
{
    double yd = b[1] - a[1];
    double xd = b[0] - a[0];
    return (yd < 0 && xd == 0)? abs(yd/xd) : yd/xd;
}

int maxPoints(vector<vector<int>>& points) 
{
    int maxPoints = 0;
    int n = points.size();
    for(int i = 0; i < n; i++)
    {
        unordered_map<double,int> mp;
        for(int j = i+1; j < n; j++)
        {
            double slope = findSlope(points[i], points[j]);
            maxPoints = max(maxPoints, ++mp[slope]);
        }
    }

    return maxPoints+1;
}

// DAY 9 144. Binary Tree Preorder Traversal)==============================================================================

vector<int> preorderTraversal(TreeNode* root) 
{
    vector<int> ans;
    TreeNode* itr = root;
    while(itr)
    {
        if(!itr->left)
        {
            ans.push_back(itr->val);
            itr = itr->right;
        }
        else 
        {
            TreeNode* tmp = itr->left;
            while(tmp->right && tmp->right != itr)
                tmp = tmp->right;
            if(tmp->right)
            {
                tmp->right = nullptr;
                itr = itr->right;
            }
            else 
            {
                ans.push_back(itr->val);
                tmp->right = itr;
                itr = itr->left;
            }
        }
    }

    return ans;
}

// DAY 10 (100. Same Tree)======================================================================================

bool isSameTree(TreeNode* p, TreeNode* q) 
{
    if(!p && !q) return true;
    if(p && !q || !p && q) return false;
    if(p->val != q->val) return false;

    return isSameTree(p->left, q->left) &&
            isSameTree(p->right, q->right);
}

// DAY 11 (1443. Minimum Time to Collect All Apples in a Tree)=======================================================

int dfs(int p, int u, int &totalDistance, vector<vector<int>> &graph, vector<bool> &hasApple)
{
    int currApples = hasApple[u];
    for(int v : graph[u])
    {
        if(v != p)
        {
            int subtreeApples = dfs(u, v, totalDistance, graph, hasApple);
            if(subtreeApples == 0)
                totalDistance -= 2;
            currApples += subtreeApples;
        }
    }

    return currApples;
}

int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) 
{
    vector<vector<int>> graph(n);
    for(vector<int> &e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }
    int totalDistance = 2*(n-1);
    dfs(-1, 0, totalDistance, graph, hasApple);
    return totalDistance;
}

// DAY 12 (1519. Number of Nodes in the Sub-Tree With the Same Label)===============================================================

vector<int> ans;
vector<int> dfs(int parpar, int par, vector<vector<int>> &graph, string &labels)
{
    vector<int> currLabels(26, 0);
    currLabels[labels[par]-'a']++;
    for(int child : graph[par])
    {
        if(child != parpar)
        {
            vector<int> subtreeLabels = dfs(par, child, graph, labels);
            for(int i = 0; i < 26; i++)
                currLabels[i] += subtreeLabels[i];
        }
    }
    ans[par] = currLabels[labels[par]-'a'];

    return currLabels;
}

vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) 
{
    ans.resize(n);
    vector<vector<int>> graph(n);
    for(vector<int> &e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    dfs(-1, 0, graph, labels);

    return ans;
}

// DAY 13 (2246. Longest Path With Different Adjacent Character)===========================================================================

int ans = 0;
int dfs(int parPar, int par, vector<vector<int>> &graph, string &s)
{
    int max1 = 0, max2 = 0;
    for(int child : graph[par])
    {
        if(child == parPar) continue;
        int childMax = dfs(par, child, graph, s);
        if(s[child] != s[par])
        {
            if(childMax > max1)
            {
                max2 = max1;
                max1 = childMax;
            }
            else if(childMax > max2)
                max2 = childMax;
        }
    }

    ans = max(ans, max1 + max2 + 1);
    return max1 + 1;
}

int longestPath(vector<int>& parent, string s) 
{
    int n = parent.size();
    vector<vector<int>> graph(n);
    for(int i = 1; i < n; i++)
    {
        graph[parent[i]].push_back(i);
        graph[i].push_back(parent[i]);
    }

    dfs(-1, 0, graph, s);

    return ans;
}

// DAY 14 (1061. Lexicographically Smallest Equivalent String)=====================================================================

vector<int> par;
int findPar(int u)
{
    return u == par[u]? u : findPar(par[u]);
}

void union_(int u, int v)
{
    int pu = findPar(u);
    int pv = findPar(v);

    if(pu == pv) return;

    if(pu < pv) par[pv] = pu;
    else par[pu] = pv;
}

string smallestEquivalentString(string s1, string s2, string baseStr) 
{
    par.resize(26);
    for(int i = 0; i < 26; i++)
        par[i] = i;

    for(int i = 0; i < s1.size(); i++)
    {
        int u = s1[i]-'a', v = s2[i]-'a';
        union_(u, v);
    }

    string ans = "";
    for(char &c : baseStr)
        ans += char(findPar(c-'a')+'a');

    return ans;
}

// DAY 15 (2421. Number of Good Paths)==============================================================================

#define f first
#define s second

vector<int> par;
int findPar(int u)
{
    return par[u] = (par[u] == u)? u : findPar(par[u]);
}

int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) 
{
    int n = vals.size();
    par.resize(n);
    vector<pair<int,int>> vls(n);
    vector<vector<int>> gp(n);

    for(int i = 0; i < n; i++)
    {
        par[i] = i;
        vls[i] = {vals[i], i};
    }
    sort(vls.begin(), vls.end());

    for(vector<int> &e : edges)
    {
        gp[e[0]].push_back(e[1]);
        gp[e[1]].push_back(e[0]);
    }

    int paths = 0;
    for(int i = 0; i < n; )
    {
        int j = i;
        while(j < n && vls[j].f == vls[i].f)
        {
            for(int v : gp[vls[j].s])
            {
                if(vals[v] > vls[j].f) continue;

                int p1 = findPar(v);
                int p2 = findPar(vls[j].s);

                if(p1 == p2) continue;
                par[p1] = p2;
            }
            j++;
        }

        unordered_map<int,int> reach;
        while(i < j)
            paths += reach[findPar(vls[i++].s)]++;
    }

    return paths + n;
}

// DAY 16 (57. Insert Interval)=========================================================================================

// METHOD 1 (More STRUCTURAL)

bool doesOverlap(int currSt, int currEnd, int newSt, int newEnd)
{
    return (newSt >= currSt && newSt <= currEnd) ||
            (newEnd >= currSt && newEnd <= currEnd) || 
            (currSt >= newSt && currEnd <= newEnd);
}

void merge(int &i, int n, vector<vector<int>> &intervals, int newSt, int newEnd, vector<vector<int>> &ans)
{
    int currSt = min(intervals[i][0], newSt);
    int currEnd = max(intervals[i][1], newEnd);
    while(i < n && currEnd >= intervals[i][0])
    {
        currEnd = max(currEnd, intervals[i++][1]);
    }
    i--;

    ans.push_back({currSt, currEnd});
}

bool liesAfter(int &i, int n, vector<vector<int>> &intervals, int newSt, int newEnd)
{
    return (i < n-1) && (newSt > intervals[i][1] && newEnd < intervals[i+1][0]);
}

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) 
{
    int n = intervals.size();
    int newSt = newInterval[0], newEnd = newInterval[1];
    if(n == 0) return {{newSt, newEnd}};

    sort(intervals.begin(), intervals.end());

    if(newEnd < intervals[0][0])
    {
        intervals.insert(intervals.begin(), {newSt, newEnd});
        return intervals;
    }
    if(newSt > intervals[n-1][1])
    {
        intervals.push_back({newSt, newEnd});
        return intervals;
    }

    vector<vector<int>> ans;
    for(int i = 0; i < n; i++)
    {
        int currSt = intervals[i][0], currEnd = intervals[i][1];

        if(doesOverlap(currSt, currEnd, newSt, newEnd))
            merge(i, n, intervals, newSt, newEnd, ans);
        else ans.push_back({currSt, currEnd});
        if(liesAfter(i, n, intervals, newSt, newEnd))
            ans.push_back({newSt, newEnd});
    }

    return ans;
}

// METHOD 2 (More OPTIMIZED)

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) 
{
    int n = intervals.size();
    int newSt = newInterval[0], newEnd = newInterval[1];
    vector<vector<int>> ans;

    sort(intervals.begin(), intervals.end());

    int i = 0;
    while(i < n && intervals[i][1] < newSt)
        ans.push_back(intervals[i++]);

    while(i < n && intervals[i][0] <= newEnd)
    {
        newSt = min(newSt, intervals[i][0]);
        newEnd = max(newEnd, intervals[i++][1]);
    }
    ans.push_back({newSt, newEnd});

    while(i < n)
        ans.push_back(intervals[i++]);

    return ans;
}

// DAY 17 (926. Flip String to Monotone Increasing)==============================================================================

// APPROACH 1 (Storing count) --> time = O(2*N)

int minFlipsMonoIncr(string s) 
{
    int n = s.size();
    int flip0 = 0, flip1 = 0;
    for(int c : s)
        flip0 += c == '0';

    int minFlips = n;
    minFlips = min(minFlips, flip0 + flip1);
    for(char &c : s)
    {
        flip1 += c == '1';
        flip0 -= c == '0';
        minFlips = min(minFlips, flip0 + flip1);
    }

    return minFlips;
}

// APPROACH 2 (Without storing count) --> time = O(N)

int minFlipsMonoIncr(string s) 
{
    int n = s.size();
    int flip0 = 0, flip1 = 0;

    for(char &c : s)
    {
        int x = c-'0';
        flip1 = min(flip0, flip1) + !x;
        flip0 += x;
    }

    return min(flip0, flip1);
}
