// DAY 1 (Distribute Candies)=============================================================

// METHOD 1 (Using Set) --> O(n*logn)
int distributeCandies(vector<int> &candyType)
{
    int n = candyType.size();
    unordered_set<int> s;
    for (int x : candyType)
        s.insert(x);
    return (s.size() < n / 2) ? s.size() : n / 2;
}

// METHOD 2 (Using Bitset) --> O(n)

int distributeCandies(vector<int> &candyType)
{
    int n = candyType.size();
    bitset<200005> f;
    for (int x : candyType)
        f.set(x + 100000);
    int count = f.count();
    // cout<<count<<endl;
    return (count < n / 2) ? count : n / 2;
}

// DAY 2 (Set Mismatch)===============================================================

vector<int> findErrorNums(vector<int> &nums)
{
    vector<int> cnt(nums.size(), 0);
    for (int x : nums)
        cnt[x - 1]++;
    vector<int> ans(2);
    for (int i = 0; i < cnt.size(); i++)
        if (cnt[i] == 2)
            ans[0] = i + 1;
        else if (cnt[i] == 0)
            ans[1] = i + 1;
    return ans;
}

// DAY 3 (Missing Number)===========================================================

// METHOD 1 (Using Array)
int missingNumber(vector<int> &nums)
{
    int n = nums.size();
    vector<int> a(n + 1, 0);
    for (int x : nums)
        a[x] = 1;
    for (int i = 0; i <= n; i++)
        if (!a[i])
            return i;
    return -1;
}

// METHOD 2 (Without Extra space)

int missingNumber(vector<int> &nums)
{
    int n = nums.size();
    int sum = 0;
    for (int x : nums)
        sum += x;
    return (n * (n + 1)) / 2 - sum;
}

// DAY 4 (Intersection of 2 Linked Lists)=============================================================================

// APPROACH 1 (Using Cycle property of Linked list) --> O(n)
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    ListNode *t1 = headA;
    if (!headA || !headB)
        return nullptr;

    while (t1->next)
        t1 = t1->next;
    t1->next = headB;
    ListNode *s = headA, *f = headA;
    while (f->next && f->next->next)
    {
        s = s->next;
        f = f->next->next;
        if (s == f)
            break;
    }
    if (!f->next || !f->next->next)
    {
        t1->next = nullptr;
        return nullptr;
    }
    s = headA;
    while (f != s)
    {
        f = f->next;
        s = s->next;
    }
    // cout<<s->val<<" "<<f->val<<endl;
    t1->next = nullptr;
    return f;
}

// APPROACH 2 (Using 2 pointer approach) --> >O(n)

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    ListNode *t1 = headA, *t2 = headB;
    while (t1 != t2)
    {
        t1 = t1 ? t1->next : headB;
        t2 = t2 ? t2->next : headA;
    }
    return t1;
}

// DAY 5 (Average of Levles in Binary Tree)===========================================================

vector<double> averageOfLevels(TreeNode *root)
{
    queue<TreeNode *> que;
    que.push(root);
    vector<double> ans;
    while (!que.empty())
    {
        int sz = que.size();
        int count = sz;
        long long int sum = 0;
        while (sz--)
        {
            TreeNode *node = que.front();
            que.pop();
            sum += node->val;
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
        ans.push_back(1.0 * sum / count);
    }
    return ans;
}