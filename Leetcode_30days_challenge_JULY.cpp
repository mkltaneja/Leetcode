// DAY 1 (Arranging coins)=======================================

// Brute force
// O(sqrt(n))
int arrangeCoins(int n)
{
    int i = 1, count = 0;
    while ((n - i) >= 0)
    {
        count++;
        n -= i;
        i++;
    }
    return count;
}

// O(logn)
int arrangeCoins(int n)
{
    int si = 0, ei = n;
    while (si <= ei)
    {
        long int mid = si + (ei - si) / 2;
        if ((mid * (mid + 1)) / 2 == n)
            return mid;
        else if ((mid * (mid + 1)) / 2 < n)
            si = mid + 1;
        else
            ei = mid - 1;
    }
    return ei;
}

///////////////////OR////////////////////\

// O(1)
int arrangeCoins(int n)
{
    return (int)(-0.5 + sqrt(0.25 + (long int)2 * n));
}

// DAY 2 (Binary Tree Level Order Traversal 2)====================================================================

// BFS
vector<vector<int>> levelOrderBottom(TreeNode *root)
{
    if (root == nullptr)
        return {};
    queue<TreeNode *> que;
    que.push(root);
    vector<vector<int>> ans;
    ans.push_back({root->val});
    while (!que.empty())
    {
        vector<int> level;
        int size = que.size();
        while (size--)
        {
            TreeNode *top = que.front();
            que.pop();
            TreeNode *l = top->left;
            TreeNode *r = top->right;
            if (l)
            {
                que.push(l);
                level.push_back(l->val);
            }
            if (r)
            {
                que.push(r);
                level.push_back(r->val);
            }
        }
        if (level.size())
            ans.push_back(level);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

///////////////////////////OR//////////////////////

// recursion
int height(TreeNode *node)
{
    if (!node)
        return 0;
    return max(height(node->left), height(node->right)) + 1;
}

void level_rec(TreeNode *node, int level, int h, vector<vector<int>> &ans)
{
    if (!node)
        return;
    ans[level].push_back(node->val);
    if (node->left)
        level_rec(node->left, level + 1, h, ans);
    if (node->right)
        level_rec(node->right, level + 1, h, ans);
}

vector<vector<int>> levelOrderBottom(TreeNode *root)
{
    int h = height(root);
    // cout<<h<<endl;
    vector<vector<int>> ans(h, vector<int>());
    level_rec(root, 0, h, ans);
    reverse(ans.begin(), ans.end());
    return ans;
}

// DAY 3 (Prison Cells After N Days)============================================================
// O(8*N)
// TLE
vector<int> prisonAfterNDays(vector<int> &cells, int N)
{
    while (N--)
    {
        int prev, curr = cells[0];
        for (int i = 0; i < 6; i++)
        {
            prev = curr;
            curr = cells[i + 1];
            cells[i + 1] = !(prev ^ cells[i + 2]);
            // cout<<prev<<" "<<cells[i+1]<<" "<<cells[i+2]<<endl;
        }
        cells[0] = 0;
        cells[7] = 0;
    }
    return cells;
}

////////////////////////////////OR//////////////////////////////

// O(index of repetetion)
vector<int> prisonAfterNDays(vector<int> &cells, int N)
{
    unordered_map<string, int> m;
    for (int n = 0; n < N; n++)
    {
        string s(cells.begin(), cells.end());
        if (m.find(s) == m.end())
        {
            m.insert({s, n});
            int prev, curr = cells[0];
            for (int i = 0; i < 6; i++)
            {
                prev = curr;
                curr = cells[i + 1];
                cells[i + 1] = !(prev ^ cells[i + 2]);
                // cout<<prev<<" "<<cells[i+1]<<" "<<cells[i+2]<<endl;
            }
            cells[0] = 0;
            cells[7] = 0;
            for (int i = 0; i < 8; i++)
                cout << cells[i] << " ";
            cout << endl;
        }
        else
        {
            int len_of_repetetion = n - m[s];
            int rem_days = (N - n) % len_of_repetetion;
            return prisonAfterNDays(cells, rem_days);
        }
    }
    return cells;
}

// DAY 4 (Ugly number 2)===============================================================

// TLE
int nthUglyNumber(int n)
{
    long int i = 1;
    while (n)
    {
        int num = i;
        bool flag = true;
        while (num != 1)
        {
            if (num % 2 == 0)
                num /= 2;
            else if (num % 3 == 0)
                num /= 3;
            else if (num % 5 == 0)
                num /= 5;
            else
            {
                flag = false;
                break;
            }
        }
        if (flag)
            n--;
        i++;
    }
    return i - 1;
}