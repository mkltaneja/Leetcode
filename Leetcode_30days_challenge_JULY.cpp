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

///////////////OR////////////////

int nthUglyNumber(int n)
{
    int ugly[n];
    ugly[0] = 1;
    int i = 1, i2 = 0, i3 = 0, i5 = 0;

    while (i < n)
    {
        int next2 = ugly[i2] * 2;
        int next3 = ugly[i3] * 3;
        int next5 = ugly[i5] * 5;
        int next = min(next2, min(next3, next5));
        if (next == next2)
            i2++;
        if (next == next3)
            i3++;
        if (next == next5)
            i5++;
        ugly[i++] = next;
    }
    // for(int i=0;i<n;i++)
    //     cout<<ugly[i]<<" ";
    return ugly[n - 1];
}

// DAY 5 (Hamming Distance)=====================================================================================

int hammingDistance(int x, int y)
{
    int ham_dist = 0;
    while (x || y)
    {
        if ((x & 1) ^ (y & 1))
            ham_dist++;
        x >>= 1;
        y >>= 1;
    }
    return ham_dist;
}

// DAY 6 (Plus One)===============================================================

vector<int> plusOne(vector<int> &digits)
{
    int n = digits.size();
    if (n == 0)
        return {1};

    int i = n - 1;
    while (i >= 0 && digits[i] == 9)
        digits[i--] = 0;
    if (i >= 0)
        digits[i]++;
    else
        digits.insert(digits.begin(), 1);
    return digits;
}

// DAY 7 (Island Perimeter)======================================================================

// O(4*n^2)
int islandPerimeter(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    int ones = 0, commreg = 0;
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                ones++;
                for (int d = 0; d < 4; d++)
                {
                    int r = i + dir[d][0];
                    int c = j + dir[d][1];
                    if (r >= 0 && c >= 0 && r < n && c < m && grid[r][c] == 1)
                        commreg++;
                }
            }
        }
    }
    return 4 * ones - commreg;
}

///////////////////OR///////////////////

// O(2*n^2)
int islandPerimeter(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    int ones = 0, commreg = 0;
    int dir[4][2] = {{1, 0}, {0, 1}};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                ones++;
                for (int d = 0; d < 2; d++)
                {
                    int r = i + dir[d][0];
                    int c = j + dir[d][1];
                    if (r < n && c < m && grid[r][c] == 1)
                        commreg++;
                }
            }
        }
    }
    return 4 * ones - 2 * commreg;
}

// DAY 8 (3Sum)=============================================================================

// O(n^3)
// TLE
vector<vector<int>> threeSum(vector<int> &nums)
{
    int n = nums.size();
    set<vector<int>> s;

    for (int i = 0; i < n - 2; i++)
    {
        int a = nums[i];
        for (int j = i + 1; j < n - 1; j++)
        {
            int b = nums[j];
            for (int k = j + 1; k < n; k++)
            {
                int c = nums[k];
                if (a + b + c == 0)
                {
                    vector<int> ar{a, b, c};
                    sort(ar.begin(), ar.end());
                    s.insert(ar);
                }
            }
        }
    }
    vector<vector<int>> ans;
    for (auto itr : s)
        ans.push_back(itr);

    return ans;
}

//////////////////OR//////////////////////

// O(N^3)  recursively
// TLE
void rec_sol(vector<int> &nums, int n, int count, int idx, int sum, vector<int> res, set<vector<int>> &ans)
{
    if (count == 3 || idx == n)
    {
        if (sum == 0)
        {
            ans.insert(res);
        }
        return;
    }
    int m;
    if (count == 0)
        m = n - 2;
    else if (count == 1)
        m = n - 1;
    else if (count == 2)
        m = n;

    for (int i = idx; i < m; i++)
    {
        res.push_back(nums[i]);
        rec_sol(nums, n, count + 1, i + 1, sum + nums[i], res, ans);
        res.pop_back();
    }
}

vector<vector<int>> threeSum(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return {};
    sort(nums.begin(), nums.end());

    vector<vector<int>> ans;
    set<vector<int>> s;
    vector<int> a;
    rec_sol(nums, n, 0, 0, 0, a, s);

    for (auto itr : s)
        ans.push_back(itr);

    return ans;
}
