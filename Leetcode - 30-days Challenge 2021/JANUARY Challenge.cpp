
// DAY 1 (Check Array Formation Through Concatenation)==============================================================

bool canFormArray(vector<int> &arr, vector<vector<int>> &pieces)
{
    vector<int> indices(101, -1);
    for (int i = 0; i < arr.size(); i++)
        indices[arr[i]] = i;

    for (int i = 0; i < pieces.size(); i++)
        for (int j = 0; j < pieces[i].size(); j++)
            if (indices[pieces[i][j]] == -1)
                return false;

    for (vector<int> v : pieces)
    {
        int i = indices[v[0]];
        for (int x : v)
        {
            if (i != indices[x])
                return false;
            i++;
        }
    }
    return true;
}

// DAY 2 (Find a Corresponding Node of a Binary Tree in a Clone of That Tree)===========================================================

TreeNode *getTargetCopy(TreeNode *original, TreeNode *cloned, TreeNode *target)
{
    if (!cloned)
        return nullptr;
    if (cloned->val == target->val)
        return cloned;
    TreeNode *left = getTargetCopy(original, cloned->left, target);
    if (left)
        return left;
    TreeNode *right = getTargetCopy(original, cloned->right, target);
    if (right)
        return right;

    return nullptr;
}

// DAY 3 (Beautiful Arrangement)==============================================================================

// METHOD 1 (Recursion from start of array -- Takes more time)
int permutations(int idx, vector<int> &arr)
{
    if (idx == arr.size())
        return 1;

    int count = 0;
    for (int i = idx; i < arr.size(); i++)
    {
        swap(arr[i], arr[idx]);
        if (max(arr[idx], idx + 1) % min(arr[idx], idx + 1) == 0)
            count += permutations(idx + 1, arr);
        swap(arr[i], arr[idx]);
    }
    return count;
}

int countArrangement(int n)
{
    vector<int> arr(n);
    for (int i = 1; i <= n; i++)
        arr[i - 1] = i;
    return permutations(0, arr);
}

// METHOD 2 (Recursion from end of array -- MUCH faster than METHOD 1)
// OPTIMIZED

int permutations(int n, vector<int> &arr)
{
    if (n <= 0)
        return 1;

    int count = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[i], arr[n - 1]);
        if (n % arr[n - 1] == 0 || arr[n - 1] % n == 0)
            count += permutations(n - 1, arr);
        swap(arr[i], arr[n - 1]);
    }
    return count;
}

int countArrangement(int n)
{
    vector<int> arr(n);
    for (int i = 1; i <= n; i++)
        arr[i - 1] = i;
    return permutations(n, arr);
}