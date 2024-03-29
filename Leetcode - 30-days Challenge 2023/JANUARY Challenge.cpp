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

// DAY 18 (918. Maximum Sum Circular Subarray)=====================================================================================

int maxSumSubarray(vector<int> &nums, int sign)
{
    int currSum = 0, maxSum = -1e9;
    for(int x : nums)
    {
        currSum = sign*x + max(currSum, 0);
        maxSum = max(maxSum, currSum);
    }

    return maxSum;
}

int maxSubarraySumCircular(vector<int>& nums) 
{
    int totSum = 0;
    for(int x : nums)
        totSum += x;

    int maxSS = maxSumSubarray(nums, 1);
    int minSS = maxSumSubarray(nums, -1);
    return maxSS < 0? maxSS : max(maxSS, totSum + minSS);
}

// DAY 19 (974. Subarray Sums Divisible by K)==================================================================================

int subarraysDivByK(vector<int>& nums, int k) 
{
    unordered_map<int,int> remCount;
    int sum = 0;
    remCount[0] = 1;
    int ans = 0;
    for(int x : nums)
    {
        sum += x;
        ans += remCount[(sum % k + k) % k]++;
    }

    return ans;
}

// DAY 20 (491. Non-decreasing Subsequences)=====================================================================================

vector<vector<int>> ans;
set<vector<int>> uni;

void subseq(int i, int prev, vector<int> &nums, vector<int> &curr)
{
    if(curr.size() > 1) uni.insert(curr);
    if(i == nums.size()) return;

    if(nums[i] >= prev)
    {
        curr.push_back(nums[i]);
        subseq(i+1, nums[i], nums, curr);
        curr.pop_back();
    }
    subseq(i+1, prev, nums, curr);
}

vector<vector<int>> findSubsequences(vector<int>& nums) 
{
    vector<int> tmp;
    subseq(0, -101, nums, tmp);

    for(vector<int> v : uni)
        ans.push_back(v);

    return ans;
}

// DAY 21 (93. Restore IP Addresses)=========================================================================================

vector<string> ans;
void dfs(int i, int curr, int dots, string &fin, string &s)
{
    if((((s.size() - i) + dots) / (dots + 1)) > 3) return;
    if(i == s.size() && dots == 0)
    {
        ans.push_back(fin);
        return;
    }

    fin += s[i];
    curr = curr*10 + (s[i]-'0');
    if(curr <= 255)
    {
        if(dots && i < s.size()-1)
        {
            fin += ".";
            dfs(i+1, 0, dots-1, fin, s);
            fin.pop_back();
        }
        if(curr || i == s.size()-1) dfs(i+1, curr, dots, fin, s);
    }
    fin.pop_back();
}

vector<string> restoreIpAddresses(string s) 
{
    string tmp = "";
    dfs(0, 0, 3, tmp, s);

    return ans;
}

// DAY 22 (131. Palindrome Partitioning)================================================================================

vector<vector<string>> ans;

bool isPal(string &x)
{
    int i = 0, j = x.size()-1;
    while(i < j && x[i] == x[j])
        i++, j--;
    return i >= j;
}

void dfs(int i, string &curr, string &s, vector<string> &part)
{
    if(i == s.size())
    {
        ans.push_back(part);
        return;
    }

    curr += s[i];
    if(isPal(curr))
    {
        part.push_back(curr);
        string ncurr = "";
        dfs(i+1, ncurr, s, part);
        part.pop_back();
    }
    if(i != s.size()-1)
        dfs(i+1, curr, s, part);
    curr.pop_back();
}

vector<vector<string>> partition(string s) 
{
    string tmp = "";
    vector<string> part;
    dfs(0, tmp, s, part);
    return ans;
}

// DAY 23 (997. Find the Town Judge)=====================================================================================

int findJudge(int n, vector<vector<int>>& trust) 
{
    vector<int> trustCount(n+1,0);
    for(vector<int> &t : trust)
    {
        trustCount[t[0]]--;
        trustCount[t[1]]++;
    }

    int ans = -1;
    for(int i = 1; i <= n; i++)
    {
        if(trustCount[i] == n-1)
        {
            if(ans != -1) return -1;
            ans = i;
        }
    }

    return ans;
}

// DAY 24 (909. Snakes and Ladders)=====================================================================================

int snakesAndLadders(vector<vector<int>>& board) 
{
    int n = board.size();
    vector<int> board2(n*n);
    int right = 1;
    for(int i = n-1, x = 0; i >= 0; i--)
    {
        for(int j = right? 0 : n-1; right? (j < n) : (j >= 0); j += right? 1 : -1)
            board2[x++] = board[i][j];
        right ^= 1;
    }

    queue<int> que;
    que.push(0);
    vector<bool> vis(n*n, false);
    vis[0] = true;
    int moves = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int curr = que.front();
            que.pop();
            if(curr == n*n-1) 
                return moves;

            for(int x = 1; x <= 6 && curr + x < n*n; x++)
            {
                int nxt = curr + x;
                if(vis[nxt]) continue;
                    vis[nxt] = true;
                if(board2[nxt] == -1)
                    que.push(nxt);
                else que.push(board2[nxt]-1);
            }
        }
        moves++;
    }


    return -1;
}

// DAY 25 (2359. Find Closest Node to Given Two Nodes)==========================================================================

void dfs(int u, vector<int> &dist, vector<int>& edges)
{
    if(edges[u] == -1) return;

    if(dist[edges[u]] == -1)
    {
        dist[edges[u]] = dist[u] + 1;
        dfs(edges[u], dist, edges);
    }
}

int closestMeetingNode(vector<int>& edges, int node1, int node2) 
{
    int n = edges.size();
    vector<int> dist1(n,-1), dist2(n,-1);
    dist1[node1] = 0;
    dist2[node2] = 0;
    dfs(node1, dist1, edges);
    dfs(node2, dist2, edges);

    int ans = -1, minDist = INT_MAX;
    for(int i = 0; i < n; i++)
    {
        if(dist1[i] == -1 || dist2[i] == -1) continue;
        int maxDist = max(dist1[i], dist2[i]);
        if(maxDist < minDist)
        {
            minDist = maxDist;
            ans = i;
        }
    }

    return ans;
}

// DAY 26 (787. Cheapest Flights Within K Stops)===============================================================================

#define pii pair<int,int>
#define f first
#define s second

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) 
{
    vector<vector<pii>> gp(n);
    for(vector<int> &flight : flights)
        gp[flight[0]].push_back({flight[1], flight[2]});

    vector<int> minDist(n, INT_MAX);
    minDist[src] = 0;

    queue<pii> que;
    que.push({src, 0});
    int stops = 0;

    while(!que.empty() && stops <= k)
    {
        int sz = que.size();
        while(sz--)
        {
            pii u = que.front();
            que.pop();

            for(pii v : gp[u.f])
            {
                if(u.s + v.s < minDist[v.f])
                {
                    minDist[v.f] = u.s + v.s;
                    que.push({v.f, u.s + v.s});
                }
            }
        }
        stops++;
    }

    return minDist[dst] == INT_MAX? -1 : minDist[dst];
}

// DAY 27 (472. Concatenated Words)==========================================================================================

// APPROACH 1 (Naive) --> time = O(m*2^n) [m = words.size(), n = words[i].size()]

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
};
Trie* head = new Trie();

void insert(string &word)
{
    Trie* itr = head;
    for(int i = 0; i < word.size(); i++)
    {
        if(!itr->child[word[i]-'a'])
            itr->child[word[i]-'a'] = new Trie();
        itr = itr->child[word[i]-'a'];
    }
    itr->wordEnd = true;
}

bool concatExist(int i, int words, Trie* itr, string &word)
{
    if(i == word.size()) return (itr == head && words > 1);
    if(!itr->child[word[i]-'a']) return false;

    if(itr->child[word[i]-'a']->wordEnd)
        if(concatExist(i+1, words+1, head, word))
            return true;
    if(concatExist(i+1, words, itr->child[word[i]-'a'], word))
        return true;

    return false;
}

vector<string> findAllConcatenatedWordsInADict(vector<string>& words) 
{
    for(string &word : words)
        insert(word);
    vector<string> ans;
    for(string &word : words)
    {
        Trie* itr = head;
        if(concatExist(0, 0, itr, word))
            ans.push_back(word);
    }

    return ans;
}

// APPROACH 2 (Using DP) --> time = O(m*n) [m = words.size(), n = words[i].size()]

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
};
Trie* head = new Trie();

void insert(string &word)
{
    Trie* itr = head;
    for(int i = 0; i < word.size(); i++)
    {
        if(!itr->child[word[i]-'a'])
            itr->child[word[i]-'a'] = new Trie();
        itr = itr->child[word[i]-'a'];
    }
    itr->wordEnd = true;
}

int concatExist(int i, int words, string &word, vector<int> &dp)
{
    if(dp[i] != -1) return dp[i];
    if(i == word.size() && words > 1) return dp[i] = 1;

    Trie* itr = head;
    for(int j = i; j < word.size(); j++)
    {
        if(!itr->child[word[j]-'a']) 
            return dp[i] = 0;

        itr = itr->child[word[j]-'a'];
        if(itr->wordEnd && concatExist(j+1, words+1, word, dp))
            return dp[i] = 1;
    }

    return dp[i] = 0;
}

vector<string> findAllConcatenatedWordsInADict(vector<string>& words) 
{
    for(string &word : words)
        insert(word);
    vector<string> ans;
    for(string &word : words)
    {
        vector<int> dp(word.size()+1, -1);
        if(concatExist(0, 0, word, dp))
            ans.push_back(word);
    }

    return ans;
}

// DAY 28 (352. Data Stream as Disjoint Intervals)=================================================================================

class SummaryRanges {
public:

    set<int> vals;
    SummaryRanges() 
    {
        
    }
    
    void addNum(int value) 
    {
        vals.insert(value);
    }
    
    vector<vector<int>> getIntervals() 
    {
        vector<vector<int>> intervals;
        int left = *vals.begin();
        int right = *vals.begin();
        for(auto itr = ++vals.begin(); itr != vals.end(); itr++)
        {
            int val = *itr;
            if(val - right == 1)
                right = val;
            else 
            {
                intervals.push_back({left, right});
                left = right = val;
            }
        }
        intervals.push_back({left, right});

        return intervals;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */

// DAY 29 (460. LFU Cache)=================================================================================================================

class LFUCache {
private:

    class Node
    {
        public:
        int key, val, freq;
        Node* next, *prev;
        Node(int key, int val)
        {
            this->key = key;
            this->val = val;
            this->freq = 1;
            this->next = nullptr;
            this->prev = nullptr;
        }
    };

    void addInList(int freq, Node* node)
    {
        Node* head = nullptr, *tail = nullptr;
        if(!fList.count(freq))
        {
            head = node;
            tail = node;
        }
        else
        {
            head = fList[freq];
            tail = head->prev;
            node->prev = tail;
            node->next = head;
        }
        head->prev = node;
        tail->next = node;
        fList[freq] = node;
    }

    void removeFromList(int freq, Node* node)
    {
        if(node->next == node) // when there is just one node in fList[freq]
        {
            fList[freq] = nullptr;
            fList.erase(freq);
            if(freq == minFreq) 
                minFreq++;
            return;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
        if(fList[freq] == node) // if node is the list head
            fList[freq] = node->next;
        node->next = nullptr;
        node->prev = nullptr;
    }


public:

    int cap, minFreq;
    unordered_map<int,Node*> mp; // pointer to the key node
    unordered_map<int,Node*> fList; // pointer to head of circular doubly ll with freq f

    LFUCache(int capacity) 
    {
        this->cap = capacity;
        this->minFreq = 0;
    }
    
    int get(int key) 
    {
        if(!mp.count(key)) return -1;

        Node* node = mp[key];
        removeFromList(node->freq, node);
        addInList(++node->freq, node);

        return node->val;
    }
    
    void put(int key, int value) 
    {
        if(!cap) return;

        if(!mp.count(key))
        {
            Node* node = new Node(key, value);
            mp[key] = node;

            if(mp.size() > cap)
            {
                mp.erase(fList[minFreq]->prev->key);
                removeFromList(minFreq, fList[minFreq]->prev);
            }

            addInList(1, node);
            minFreq = 1;
        }
        else 
        {
            Node* node = mp[key];
            node->key = key;
            node->val = value;

            removeFromList(node->freq, node);
            
            addInList(++node->freq, node);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// DAY 31 (1626. Best Team With No Conflicts)======================================================================================

#define f first
#define s second

int subseq(int i, int mxi, int mx, vector<pair<int,int>> &as)
{
    if(i == -1) return 0;

    int inc = 0;
    if(as[i].s <= mx || as[i].f == as[mxi].f)
        inc = subseq(i-1, i, as[i].s, as) + as[i].s;
    int exc = subseq(i-1, mxi, mx, as);

    return max(inc, exc);
}

int bestTeamScore(vector<int>& scores, vector<int>& ages) 
{
    int n = ages.size();
    vector<pair<int,int>> age_score(n);
    for(int i = 0; i < n; i++)
        age_score[i] = {ages[i], scores[i]};

    sort(age_score.begin(), age_score.end());

    vector<int> dp(n);
    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = i; j >= 0; j--)
        {
            if(age_score[j].s > age_score[i].s) continue;
            dp[i] = max(dp[i], dp[j] + age_score[i].s);
        }
        ans = max(ans, dp[i]);
    }

    return ans;
}
