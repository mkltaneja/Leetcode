
// APPROACH 1 (time OPTIMIZED)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    #define f first
    #define s second
    
    unordered_map<int,pair<int,int>> mxh;
    int dep[100005], ht[100005];
    
    int dfs(TreeNode* node, int d)
    {
        if(!node) return 0;
        
        dep[node->val] = d;
        
        int l = dfs(node->left, d+1);
        int r = dfs(node->right, d+1);
        int h = max(l, r) + 1;
        
        if(h > mxh[d].f)
            mxh[d].s = mxh[d].f, mxh[d].f = h;
        else if(h == mxh[d].f)
            mxh[d].s = mxh[d].f;
        else mxh[d].s = max(mxh[d].s, h);
        
        return ht[node->val] = h;
    }
    
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) 
    {
        dfs(root, 0);
        vector<int> ans;
        for(int x : queries)
        {
            if(ht[x] == mxh[dep[x]].f)
            {
                if(mxh[dep[x]].s)
                    ans.push_back(mxh[dep[x]].s + dep[x] - 1);
                else ans.push_back(dep[x]-1);
            }
            else ans.push_back(mxh[dep[x]].f + dep[x] - 1);
        }
        
        return ans;
    }
};

// APPROACH 2 (Space OPTIMIZED)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    #define f first
    #define s second
    
    int ht[100005][2];
    int res[100005];
    
    int dfs(TreeNode* node)
    {
        if(!node) return 0;
        int l = dfs(node->left);
        int r = dfs(node->right);
        
        ht[node->val][0] = l;
        ht[node->val][1] = r;
        
        return max(l, r) + 1;
    }
    
    void dfs(TreeNode* node, int mxh, int dep)
    {
        if(!node) return;
        
        res[node->val] = max(mxh, dep-1);
        
        dfs(node->left, max(mxh, ht[node->val][1] + dep), dep+1);
        dfs(node->right, max(mxh, ht[node->val][0] + dep), dep+1);
    }
    
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) 
    {
        dfs(root);
        dfs(root, 0, 0);
        
        vector<int> ans;
        for(int x : queries)
            ans.push_back(res[x]);
        
        return ans;
    }
};
