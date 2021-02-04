// DAY 1 (Number of 1 Bits)================================================================

// in C++
int hammingWeight(uint32_t n)
{
    int cnt = 0;
    while (n)
    {
        cnt++;
        n &= (n - 1);
    }
    return cnt;
}

// in Java
// you need to treat n as an unsigned value
public
int hammingWeight(int n)
{
    int cnt = 0;
    if ((n & (1 << 31)) != 0)
    {
        n ^= (1 << 31);
        cnt++;
    }
    System.out.println(n);
    while (n > 0)
    {
        cnt++;
        n &= (n - 1);
    }
    return cnt;
}
// OR
public
int hammingWeight(int n)
{
    return Integer.bitCount(n);
}

// DAY 2 (Trim a Binary Search Tree)=====================================================

TreeNode *trimBST(TreeNode *root, int low, int high)
{
    if (!root)
        return nullptr;
    if (root->val < low)
        return trimBST(root->right, low, high);
    if (root->val > high)
        return trimBST(root->left, low, high);
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}

// DAY 3 (Linked List Cycle)===================================================================

bool hasCycle(ListNode *head)
{
    ListNode *slow = head, *fast = head;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (slow == fast)
            return true;
    }
    return false;
}

// DAY 4 (Longest Harmonious Subsequence)===============================================================

// APPROACH 1 (taking record of maximum and minimum) --> O(n^2)
int findLHS(vector<int> &nums)
{
    int n = nums.size();
    int maxlen = 0;
    for (int i = 0; i < n; i++)
    {
        int a = nums[i], b = nums[i] - 1, c = nums[i] + 1;
        int ca = 1, cb = 0, cc = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (nums[j] == a)
                ca++;
            else if (nums[j] == b)
                cb++;
            else if (nums[j] == c)
                cc++;

            if (cb != 0)
                maxlen = max(maxlen, ca + cb);
            if (cc != 0)
                maxlen = max(maxlen, ca + cc);
        }
    }
    return maxlen;
}