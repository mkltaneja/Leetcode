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
