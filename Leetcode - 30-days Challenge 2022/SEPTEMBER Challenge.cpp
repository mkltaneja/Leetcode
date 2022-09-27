// DAY 1 (1448. Count Good Nodes in Binary Tree)===========================================================================

int dfs(TreeNode* node, int mx)
{
    if(!node) return 0;

    mx = max(mx, node->val);
    return dfs(node->left, mx) + dfs(node->right, mx) + (node->val >= mx);
}

int goodNodes(TreeNode* root) 
{
    return dfs(root, INT_MIN);
}

// DAY 2 (637. Average of Levels in Binary Tree)=======================================================================

vector<double> averageOfLevels(TreeNode* root) 
{
    vector<double> ans;
    queue<TreeNode*> que;
    que.push(root);

    while(!que.empty())
    {
        int sz = que.size();
        double sum = 0, tot = 0;
        while(sz--)
        {
            TreeNode* node = que.front();
            que.pop();
            sum += node->val;
            tot++;
            if(node->left)
                que.push(node->left);
            if(node->right)
                que.push(node->right);
        }
        ans.push_back(sum/tot);
    }

    return ans;
}

// DAY 3 (967. Numbers With Same Consecutive Differences)============================================================================

vector<int> ans;
void dfs(int x, int n, int k)
{
    if(n == 0)
    {
        ans.push_back(x);
        return;
    }

    if(x%10 - k >= 0)
        dfs(x*10 + (x%10 - k), n-1, k);
    if(k && x%10 + k <= 9)
        dfs(x*10 + (x%10 + k), n-1, k);
}

vector<int> numsSameConsecDiff(int n, int k) 
{
    for(int x = 1; x <= 9; x++)
        dfs(x, n-1, k);
    return ans;
}

// DAY 4 (987. Vertical Order Traversal of a Binary Tree)=======================================================================

vector<vector<int>> verticalTraversal(TreeNode* root) 
{
    queue<pair<TreeNode*, int>> que;
    que.push({root, 0});
    map<int,vector<int>> mp;
    mp[0].push_back(root->val);
    while(!que.empty())
    {
        int sz = que.size();
        map<int,vector<int>> tmp;
        while(sz--)
        {
            TreeNode* node = que.front().first;
            int vlvl = que.front().second;
            que.pop();

            if(node->left)
            {
                tmp[vlvl-1].push_back(node->left->val);
                que.push({node->left, vlvl-1});
            }
            if(node->right)
            {
                tmp[vlvl+1].push_back(node->right->val);
                que.push({node->right, vlvl+1});
            }
        }

        for(auto &p : tmp)
        {
            sort(p.second.begin(), p.second.end());
            for(int x : p.second)
                mp[p.first].push_back(x);
        }
    }

    vector<vector<int>> ans;
    for(auto p : mp)
        ans.push_back(p.second);

    return ans;
}

// DAY 5 (429. N-ary Tree Level Order Traversal)===================================================================================

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) 
    {
        if(!root) return {};
        vector<vector<int>> ans;
        queue<Node*> que;
        que.push(root);
        
        while(!que.empty())
        {
            int sz = que.size();
            vector<int> curr;
            while(sz--)
            {
                Node* node = que.front();
                que.pop();
                curr.push_back(node->val);
                for(Node* child : node->children)
                    que.push(child);
            }
            
            ans.push_back(curr);
        }
        
        return ans;
    }
};

// DAY 6 (814. Binary Tree Pruning)==========================================================================================

TreeNode* pruneTree(TreeNode* root) 
{
    if(!root) return nullptr;

    root->left = pruneTree(root->left);
    root->right = pruneTree(root->right);

    return (!root->val && !root->left && !root->right)? nullptr : root;
}

// DAY 7 (606. Construct String from Binary Tree)============================================================================

string ans = "";
void dfs(TreeNode* node)
{
    if(!node) return;
    if(!node->left && !node->right)
    {
        ans += to_string(node->val);
        return;
    }

    ans += to_string(node->val);
    ans += "(";
    dfs(node->left);
    ans += ")";
    if(node->right)
    {
        ans += "(";
        dfs(node->right);
        ans += ")";
    }
}

string tree2str(TreeNode* root) 
{
    dfs(root);
    return ans;
}

// DAY 8 (94. Binary Tree Inorder Traversal)==========================================================================

vector<int> inorderTraversal(TreeNode* root) 
{
    vector<int> ans;
    while(root)
    {
        if(!root->left)
        {
            ans.push_back(root->val);
            root = root->right;
        }
        else 
        {
            TreeNode* lr = root->left;
            while(lr->right && lr->right != root)
                lr = lr->right;

            if(!lr->right)
            {
                lr->right = root;
                root = root->left;
            }
            else 
            {
                ans.push_back(root->val);
                root = root->right;
                lr->right = nullptr;
            }
        }
    }

    return ans;
}

// DAY 9 (1996. The Number of Weak Characters in the Game)======================================================================================

// APPROACH 1 (Sorting) --> time = O(n*logn), space = O(1)

int numberOfWeakCharacters(vector<vector<int>>& properties) 
{
    int n = properties.size();
    sort(properties.begin(), properties.end(), [](auto const &a, auto const &b){
        return a[0] == b[0]? a[0] > b[0] : a[1] < b[1];
    });

    int maxdef = 0;
    int ans = 0;
    for(vector<int> v : properties)
    {
        if(maxdef > v[1]) ans++;
        else maxdef = v[1];
    }

    return ans;
}

// APPROACH 2 (Using extra space) -> time = O(maxAttack), space = O(n) [OPTIMIZED]

int numberOfWeakCharacters(vector<vector<int>>& properties) 
{
    int maxatk = 0;
    for(vector<int> prop : properties)
        maxatk = max(maxatk, prop[0]);

    vector<int> maxdef(maxatk+2);
    for(vector<int> prop : properties)
        maxdef[prop[0]] = max(maxdef[prop[0]], prop[1]);

    for(int i = maxatk-1; i >= 0; i--)
        maxdef[i] = max(maxdef[i], maxdef[i+1]);

    int ans = 0;
    for(vector<int> prop : properties)
        ans += prop[1] < maxdef[prop[0]+1];

    return ans;
}

// DAY 10 (188. Best Time to Buy and Sell Stock IV)===================================================================================

int maxProfit(int k, vector<int>& prices) 
{
    vector<int> dp0(k+1, 0), dp1(k+1, INT_MIN);
    for(int x : prices)
    {
        for(int i = k; i > 0; i--)
        {
            dp0[i] = max(dp0[i], dp1[i] + x);
            dp1[i] = max(dp1[i], dp0[i-1] - x);
        }
    }

    return dp0[k];
}

// DAY 11 (1383. Maximum Performance of a Team)==========================================================================================

int m = 1e9 + 7;
#define ull unsigned long long
int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) 
{
    vector<pair<int,int>> effspeed(n);
    for(int i = 0; i < n; i++)
        effspeed[i] = {efficiency[i], speed[i]};
    sort(effspeed.begin(), effspeed.end());

    ull ans = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    ull sum = 0;
    for(int i = n-1; i >= 0; i--)
    {
        pq.push(effspeed[i].second);
        sum += effspeed[i].second;
        if(pq.size() > k) 
        {
            sum -= pq.top();
            pq.pop();
        }
        ans = max(ans, sum * effspeed[i].first);
    }

    return ans % m;
}

// DAY 12 (948. Bag of Tokens)====================================================================================================

int bagOfTokensScore(vector<int>& tokens, int power) 
{
    sort(tokens.begin(), tokens.end());
    int i = 0, j = tokens.size() - 1;
    int score = 0;
    int neg = 0;
    while(i <= j)
    {
        if(power >= tokens[i])
            power -= tokens[i++], score += 1-neg, neg = 0;
        else if(score)
            power += tokens[j--], neg++;
        else return score;
    }

    return score;
}

// DAY 13 (393. UTF-8 Validation)=========================================================================================

bool validUtf8(vector<int>& data) 
{
    int cnt = 0;
    for(int x : data)
    {
        if(cnt)
        {
            if((x >> 6) != 0b10) return false;
            cnt--;
        }
        else 
        {
            if((x >> 3) == 0b11110) cnt = 3;
            else if((x >> 4) == 0b1110) cnt = 2;
            else if((x >> 5) == 0b110) cnt = 1;
            else if(x >> 7) return false;
        }
    }

    return !cnt;
}

// DAY 14 (1457. Pseudo-Palindromic Paths in a Binary Tree)====================================================================================

int dfs(int x, TreeNode* node)
{
    if(!node) return 0;

    x ^= (1 << node->val);
    if(!node->left && !node->right)
    {
        return !(x & (x-1));
    }
    return dfs(x, node->left) + dfs(x, node->right);
}

int pseudoPalindromicPaths (TreeNode* root) 
{
    return dfs(0, root);
}

// DAY 15 (2007. Find Original Array From Doubled Array)=======================================================================================

// APPROACH 1 (Traversing in increasing order) time = O(n*logn), space = O(n)

vector<int> findOriginalArray(vector<int>& changed) 
{
    sort(changed.begin(), changed.end());
    unordered_map<int,int> mp;
    vector<int> ans;
    for(int x : changed)
        mp[x]++;
    for(int x : changed)
    {
        if(mp.count(x) && mp.count(2*x))
        {
            ans.push_back(x);
            if(--mp[x] == 0)
                mp.erase(x);
            if(--mp[2*x] == 0)
                mp.erase(2*x);
        }
    }
    return mp.empty()? ans : vector<int>();
}

// APPROACH 2 (traversing from max element to 0) time = O(max(changed[i]) + n), space = O(n)

vector<int> findOriginalArray(vector<int>& changed) 
{
    unordered_map<int,int> mp;
    vector<int> ans;
    int mx = 0;
    for(int x : changed)
        mp[x]++, mx = max(mx, x);

    if(mp[0] & 1) return {};
    for(int i = 0; i < mp[0]/2; i++)
        ans.push_back(0);

    for(int x = mx; x; x--)
    {
        if(!mp[x]) continue;

        if((x & 1) || (mp[x/2] < mp[x])) return {};

        mp[x/2] -= mp[x];
        for(int i = 0; i < mp[x]; i++)
            ans.push_back(x/2);
    }

    return ans;
}

// DAY 16 (1770. Maximum Score from Performing Multiplication Operations)==================================================================================

int maximumScore(vector<int>& nums, vector<int>& multipliers) 
{
    int n = nums.size(), m = multipliers.size();
    vector<vector<int>> dp(m+1, vector<int>(m+1, 0));
    for(int k = m-1; k >= 0; k--)
    {
        for(int i = k; i >= 0; i--)
        {
            int j = (n - k - 1) + i;
            dp[k][i] = max(dp[k+1][i+1] + (nums[i] * multipliers[k]), 
                           dp[k+1][i] + (nums[j] * multipliers[k]));
        }
    }
    return dp[0][0];
}

// DAY 17 (336. Palindrome Pairs)=================================================================================================

#define f first
#define s second

bool ispal(int l, int r, string &s)
{
    while(l < r && s[l] == s[r])
        l++, r--;
    return l >= r;
}

vector<vector<int>> palindromePairs(vector<string>& words) 
{
    int n = words.size();
    map<int,unordered_map<string,int>> mp;
    for(int i = 0; i < n; i++)
    {
        string s = string(words[i].rbegin(), words[i].rend());
        mp[words[i].size()][s] = i;
    }

    vector<vector<int>> ans;
    for(int i = 0; i < n; i++)
    {
        int m = words[i].size();
        for(auto &p : mp)
        {
            if(p.f > m) break;

            if(p.f == m)
            {
                auto itr = p.s.find(words[i]);
                if(itr != p.s.end() && (*itr).s != i)
                    ans.push_back({i, (*itr).s});
                continue;
            }

            if(ispal(0, m - p.f - 1, words[i]))
            {
                auto itr = p.s.find(words[i].substr(m - p.f));
                if(itr != p.s.end())
                    ans.push_back({(*itr).s, i});
            }
            if(ispal(p.f, m-1, words[i]))
            {
                auto itr = p.s.find(words[i].substr(0, p.f));
                if(itr != p.s.end())
                    ans.push_back({i, (*itr).s});
            }
        }
    }
    return ans;
}

// DAY 18 (42. Trapping Rain Water)====================================================================================================

// APPROACH 1 (Using Stack) -> time = O(2*n), space = O(n)

int trap(vector<int>& height) 
{
    stack<int> st;
    int water = 0;
    for(int i = 0; i < height.size(); i++)
    {
        while(!st.empty() && height[i] >= height[st.top()])
        {
            int x = height[st.top()];
            st.pop();
            if(st.empty()) break;
            int h = min(height[i], height[st.top()]) - x;
            water += h * (i - st.top() - 1);
        }
        st.push(i);
    }

    return water;
}

// APPROACH 2 (Taking maximum from left and right) -> time = O(n), space = O(1) [OPTIMIZED]

int trap(vector<int>& height) 
{
    int n = height.size();
    int lmax = height[0], rmax = height[n-1];
    int l = 1, r = n-2;
    int water = 0;
    while(l <= r)
    {
        if(lmax < rmax)
        {
            lmax = max(lmax, height[l]);
            water += lmax - height[l++];
        }
        else 
        {
            rmax = max(rmax, height[r]);
            water += rmax - height[r--];
        }
    }

    return water;
}

// DAY 19 (609. Find Duplicate File in System)======================================================================================

vector<vector<string>> findDuplicate(vector<string>& paths) 
{
    unordered_map<string,vector<string>> mp;
    for(string &s : paths)
    {
        string path = "";
        int i = 0;
        while(s[i] != ' ')
            path += s[i++];
        i++;
        while(i < s.size())
        {
            string fname = "", content = "";
            while(s[i] != '(')
                fname += s[i++];
            i++;
            while(s[i] != ')')
                content += s[i++];
            i += 2;

            mp[content].push_back(path + "/" + fname);
        }
    }

    vector<vector<string>> ans;
    for(auto p : mp)
        if(p.second.size() > 1)
            ans.push_back(p.second);

    return ans;
}

// DAY 20 (718. Maximum Length of Repeated Subarray)===============================================================================

int findLength(vector<int>& nums1, vector<int>& nums2) 
{
    int n = nums1.size(), m = nums2.size();
    vector<vector<int>> dp(n, vector<int>(m,0));

    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            dp[i][j] = nums1[i] == nums2[j]? ((i&&j)? dp[i-1][j-1] : 0) + 1 : 0;
            ans = max(ans, dp[i][j]);
        }
    }

    return ans;
}

// DAY 21 (985. Sum of Even Numbers After Queries)=====================================================================================

vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) 
{
    int esum = 0;
    for(int x : nums)
        esum += (x&1^1)? x : 0;
    vector<int> ans(queries.size());
    int i = 0;
    for(vector<int> q : queries)
    {
        if(nums[q[1]]&1)
        {
            if(q[0] & 1)
                esum += q[0] + nums[q[1]];
        }
        else 
        {
            if(q[0] & 1)
                esum -= nums[q[1]];
            else esum += q[0];
        }
        nums[q[1]] += q[0];
        ans[i++] = esum;
    }

    return ans;
}

// DAY 22 (557. Reverse Words in a String III)==================================================================================

string reverseWords(string s) 
{
    int n = s.size();
    string ans = "";
    for(int i = 0; i < n; i++)
    {
        int j = i;
        string tmp = "";
        while(j < n && s[j] != ' ')
            tmp += s[j++];
        reverse(tmp.begin(), tmp.end());
        ans += tmp;
        ans += j == n? "" : " ";
        i = j;
    }

    return ans;
}

// DAY 23 (1680. Concatenation of Consecutive Binary Numbers)=============================================================================

int mod = 1e9 + 7;
int concatenatedBinary(int n) 
{
    long ans = 0;
    long nxt = 1;
    for(int i = 1; i <= n; i++)
    {
        if(i == nxt) nxt *= 2;
        ans = (ans * nxt + i) % mod;
    }

    return ans;
}

// DAY 24 (113. Path Sum II)=====================================================================================================

vector<vector<int>> ans;
void dfs(TreeNode* node, int tar, vector<int> &curr)
{
    if(!node) return;
    if(!node->left && !node->right)
    {
        if(tar - node->val) return;
        curr.push_back(node->val);
        ans.push_back(curr);
        curr.pop_back();
        return;
    }

    curr.push_back(node->val);
    dfs(node->left, tar - node->val, curr);
    dfs(node->right, tar - node->val, curr);
    curr.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) 
{
    vector<int> curr;
    dfs(root, targetSum, curr);
    return ans;
}

// DAY 25 (622. Design Circular Queue)=============================================================================================

class MyCircularQueue {
public:
    
    int st, end, avail;
    int n;
    vector<int> que;
    MyCircularQueue(int k) 
    {
        this->n = k;
        this->avail = k;
        this->que.resize(k);
        this->st = 0;
        this->end = -1;
    }
    
    bool enQueue(int value) 
    {
        if(avail == 0) return false;
        end = (end + 1) % n;
        que[end] = value;
        avail--;
        return true;
    }
    
    bool deQueue() 
    {
        if(avail == n) return false;
        st = (st + 1) % n;
        avail++;
        return true;
    }
    
    int Front() 
    {
        return avail == n? -1 : que[st];
    }
    
    int Rear() 
    {
        return avail == n? -1 : que[end];
    }
    
    bool isEmpty() 
    {
        return avail == n; 
    }
    
    bool isFull() 
    {
        return avail == 0;
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

// DAY 26 (990. Satisfiability of Equality Equations)===============================================================================

vector<int> par;
int findpar(int u)
{
    return par[u] = par[u] == u? u : findpar(par[u]);
}

bool equationsPossible(vector<string>& equations) 
{
    par.resize(26);
    for(int i = 0; i < 26; i++)
        par[i] = i;

    for(string s : equations)
    {
        if(s[1] == '=')
        {
            int p1 = findpar(s[0]-'a');
            int p2 = findpar(s[3]-'a');
            par[p1] = p2;
        }
    }
    for(string s : equations)
        if(s[1] == '!' && findpar(s[0]-'a') == findpar(s[3]-'a'))
            return false;

    return true;
}

// DAY 27 (838. Push Dominoes)=======================================================================================

// APPROACH 1 (Naive)

string pushDominoes(string dominoes) 
{
    int n = dominoes.size();
    int r = n-1, l = -1;
    for(int i = 0; i <= n; i++)
    {
        if(i < n && dominoes[i] == '.') continue;

        if(i < n && dominoes[i] == 'R')
        {
            if(r != n-1)
                for(int j = r+1; j < i; j++)
                    dominoes[j] = 'R';
            r = i;
        }
        else 
        {
            int tl = 0, tr = 0;
            if(i == n) 
                tr = i-r-1;
            else if(r == n-1) 
                tl = i-l-1;
            else 
                tl = tr = (i-r-1)/2;

            for(int j = r+1; tr--;) dominoes[j++] = 'R';
            for(int j = i-1; tl--;) dominoes[j--] = 'L';

            l = i;
            r = n-1;
        }
    }

    return dominoes;
}

// APPROACH 2 (Calculating Net-Force)

string pushDominoes(string dominoes) 
{
    int n = dominoes.size();
    vector<int> nforce(n,0);
    int f = 0;
    for(int i = 0; i < n; i++)
    {
        if(dominoes[i] == 'L')
            f = 0;
        else if(dominoes[i] == 'R')
            f = n;
        else f = max(f-1, 0);
        nforce[i] = f;
    }
    for(int i = n-1; i >= 0; i--)
    {
        if(dominoes[i] == 'L')
            f = n;
        else if(dominoes[i] == 'R')
            f = 0;
        else f = max(f-1, 0);
        nforce[i] -= f;
    }

    for(int i = 0; i < n; i++)
        dominoes[i] = nforce[i]? (nforce[i] > 0? 'R' : 'L') : '.';

    return dominoes;
}
