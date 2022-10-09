// DAY 1 (91. Decode Ways)=======================================================================================

int numDecodings(string s) 
{
    int n = s.size();
    vector<int> dp(n+2,0);
    dp[n] = 1;
    for(int i = n-1; i >= 0; i--)
    {
        if(s[i] == '0') continue;
        dp[i] = dp[i+1] + (((s[i]-'0')*10 + (s[i+1]-'0') <= 26)? dp[i+2] : 0);
    }
    return dp[0];
}

// DAY 2 (1155. Number of Dice Rolls With Target Sum)====================================================================

#define ll long long
int mod = 1e9 + 7;
int dfs(ll n, ll k, ll tar, vector<vector<ll>> &dp)
{
    if(tar == 0) return 0;
    if(n == 1) return tar && tar <= k;
    if(dp[n][tar] != -1) return dp[n][tar] % mod;

    ll ans = 0;
    for(ll i = 1; i <= k; i++)
        if(i <= tar)
            ans = (ans % mod + dfs(n-1, k, tar-i, dp) % mod) % mod;

    return dp[n][tar] = ans % mod;
}

int numRollsToTarget(int n, int k, int target) 
{
    vector<vector<ll>> dp(n+1, vector<ll>(target+1, -1));
    return dfs(n, k, target, dp) % mod;
}

// DAY 3 (1578. Minimum Time to Make Rope Colorful)=============================================================================

int minCost(string colors, vector<int>& neededTime) 
{
    int n = colors.size();
    int ans = 0;
    for(int i = 0; i < n; )
    {
        int j = i+1;
        int mxt = neededTime[i];
        int sumt = neededTime[i];
        bool same = false;
        while(j < n && colors[j] == colors[i])
        {
            sumt += neededTime[j];
            mxt = max(mxt, neededTime[j++]);
            same = true;
        }
        ans += same? sumt - mxt : 0;
        i = j;
    }

    return ans;
}

// DAY 4 (112. Path Sum)===============================================================================================

bool hasPathSum(TreeNode* root, int targetSum) 
{
    if(!root) return false;
    if(!root->left && !root->right) 
        return (targetSum - root->val) == 0;
    return hasPathSum(root->left, targetSum - root->val) || 
            hasPathSum(root->right, targetSum - root->val);
}

// DAY 5 (623. Add One Row to Tree)=========================================================================================

TreeNode* dfs(int p, TreeNode* root, int val, int depth, int left)
{
    if(depth == 1)
    {
        TreeNode* nroot = new TreeNode(val);
        if(left)
            nroot->left = root;
        else nroot->right = root;
        return nroot;
    }
    if(!root) return root;

    root->left = dfs(root->val, root->left, val, depth-1, 1);
    root->right = dfs(root->val, root->right, val, depth-1, 0);

    return root;
}

TreeNode* addOneRow(TreeNode* root, int val, int depth) 
{
    return dfs(-1, root, val, depth, 1);
}

// DAY 6 (981. Time Based Key-Value Store)=====================================================================================

class TimeMap {
public:

    unordered_map<string,vector<pair<int,string>>> mp;
    TimeMap() 
    {
        
    }
    
    void set(string key, string value, int timestamp) 
    {
        mp[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) 
    {
        if(!mp.count(key)) return "";

        vector<pair<int,string>> &vals = mp[key];
        
        int lo = 0, hi = vals.size();
        
        if(timestamp < vals[lo].first) return "";
        if(timestamp >= vals[hi-1].first) return vals[hi-1].second;

        while(lo < hi)
        {
            int mid = lo + ((hi - lo)>>1);
            if(vals[mid].first == timestamp) return vals[mid].second;
            if(vals[mid].first > timestamp)
                hi = mid;
            else lo = mid + 1;
        }
        int ub = lo - 1;

        if(ub != -1) return vals[ub].second;
        return "";
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */

// DAY 7 (732. My Calendar III)===================================================================================================

class MyCalendarThree {
public:

    map<int,int> mp;
    MyCalendarThree() 
    {
        
    }
    
    int book(int start, int end) 
    {
        int ans = 0;
        mp[start]++;
        mp[end]--;
        int cnt = 0;
        for(auto &p : mp)
        {
            cnt += p.second;
            ans = max(ans, cnt);
        }

        return ans;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */

// DAY 8 (16. 3Sum Closest)===========================================================================================

int threeSumClosest(vector<int>& nums, int target) 
{
    int n = nums.size();
    int ans = 50000;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < n-2; i++)
    {
        int sum1 = nums[i] + nums[n-2] + nums[n-1];
        if(sum1 < target)
        {
            if(abs(target - sum1) < abs(target - ans))
                ans = sum1;
            continue;
        }
        int sum2 = nums[i] + nums[i+1] + nums[i+2];
        if(sum2 > target)
        {
            if(abs(target - sum2) < abs(target - ans))
                ans = sum2;
            continue;
        }
        if(i && nums[i] == nums[i-1]) continue;

        int l = i+1, r = n-1;
        while(l < r)
        {
            int curr = nums[i] + nums[l] + nums[r];
            if(abs(target - curr) < abs(target - ans))
                ans = curr;

            if(curr < target) l++;
            else r--;
        }
    }

    return ans;
}

// DAY 9 (653. Two Sum IV - Input is a BST)===========================================================================================

void inorder(TreeNode* node, vector<int> &sor)
{
    if(!node) return;
    inorder(node->left, sor);
    sor.push_back(node->val);
    inorder(node->right, sor);
}

bool findTarget(TreeNode* root, int k) 
{
    vector<int> sor;
    inorder(root, sor);
    int l = 0, r = sor.size()-1;
    while(l < r)
    {
        int sum = sor[l] + sor[r];
        if(sum == k) return true;
        if(sum < k) l++;
        else r--;
    }

    return false;
}
