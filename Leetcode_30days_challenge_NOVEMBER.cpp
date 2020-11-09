
// $ DAY 1 (Convert Binary Number in a Linked List to Integer)========================================================

int getDecimalValue(ListNode *head)
{
    int ans = 0;
    ListNode *temp = head;
    while (temp)
    {
        ans = 2 * ans + temp->val;
        temp = temp->next;
    }
    return ans;
}

// $ DAY 2 (Insertion Sort List)========================================================================

ListNode *insertionSortList(ListNode *head)
{
    ListNode *ans = new ListNode(INT_MIN);

    while (head)
    {
        ListNode *tmp = ans;
        while (tmp->next && tmp->next->val < head->val)
            tmp = tmp->next;

        ListNode *nextnode = head->next;
        head->next = tmp->next;
        tmp->next = head;
        head = nextnode;
    }

    return ans->next;
}

// $ DAY 4 (Consecutive Characters)============================================================

// METHOD 1 (Using Hashmap)
int maxPower(string s)
{
    unordered_map<char, int> m;
    int maxlen = 0, j = 0;

    for (int i = 0; i < s.size(); i++)
    {
        m[s[i]]++;
        while (m.size() > 1)
        {
            if (--m[s[j]] == 0)
                m.erase(s[j]);
            j++;
        }
        maxlen = max(maxlen, i - j + 1);
    }
    return maxlen;
}

// METHOD 2 (OPTIMIZED)
int maxPower(string s)
{
    int maxlen = 1, len = 1;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == s[i + 1])
            maxlen = max(maxlen, ++len);
        else
            len = 1;
    }
    return maxlen;
}

// $ DAY 4(Minimum Height Trees)============================================================

void getleaves(vector<int> &leaves, unordered_map<int, unordered_set<int>> &gp)
{
    leaves = vector<int>();
    for (auto &e : gp)
        if (e.second.size() <= 1)
            leaves.push_back(e.first);
}

void removeleaves(vector<int> &leaves, unordered_map<int, unordered_set<int>> &gp)
{
    for (int &leaf : leaves)
    {
        for (auto &e : gp[leaf])
            gp[e].erase(leaf);
        gp.erase(leaf);
    }
}

vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
{
    unordered_map<int, unordered_set<int>> gp;
    for (vector<int> &v : edges)
    {
        gp[v[0]].insert(v[1]);
        gp[v[1]].insert(v[0]);
    }

    vector<int> leaves;
    while (gp.size() > 2)
    {
        getleaves(leaves, gp);
        for (int i : leaves)
            cout << i << " ";
        cout << endl;
        removeleaves(leaves, gp);
        // cout<<leaves.size()<<endl;
        // leaves.clear();
    }
    getleaves(leaves, gp);

    return leaves.empty() ? vector<int>{0} : leaves;
}

// $ DAY 5 (Minimum Cost to Move Chips to The Same Position)===================================================================

int minCostToMoveChips(vector<int> &position)
{
    int oddcount = 0, evencount = 0;

    for (int pos : position)
    {
        oddcount += (pos & 1);
        evencount += !(pos & 1);
    }
    return min(oddcount, evencount);
}

// DAY 6()===========================================================================

// METHOD 1 (Linearly) --> O(n)
// TLE
int issmaller(vector<int> &nums, int div, int threshold)
{
    int sum = 0;
    // cout<<div<<": \n";
    for(int i : nums)
    {
        sum += (ceil)( 1.0 * i / div);
        // cout<<(ceil)( 1.0 * i / div)<<" ";
    }
    // cout<<endl;
    return sum <= threshold;
}

int smallestDivisor(vector<int>& nums, int threshold) 
{
    int mini = 1;
    int maxi = 0;
    for(int i : nums)
        maxi = max(maxi, i);
    int ans = maxi;
    
    while(ans >= mini)
    {
        if(!issmaller(nums, ans, threshold))
            break;
        ans--;
    }
    return ++ans;
}

// METHOD 2 (Binary Search) --> O(logn)
// AC
int issmaller(vector<int> &nums, int div, int threshold)
{
    int sum = 0;
    // cout<<div<<": \n";
    for(int i : nums)
    {
        sum += (ceil)( 1.0 * i / div);
        // cout<<(ceil)( 1.0 * i / div)<<" ";
    }
    // cout<<endl;
    return sum <= threshold;
}

int smallestDivisor(vector<int>& nums, int threshold) 
{
    int mini = 1;
    int maxi = 0;
    for(int i : nums)
        maxi = max(maxi, i);
    
    while(maxi > mini)
    {
        int mid = (maxi + mini) / 2;
        if(!issmaller(nums, mid, threshold))
            mini = mid + 1;
        else
            maxi = mid;
    }
    return maxi;
}

// DAY 7 (Add Two Numbers II)=========================================================================

ListNode* reverse(ListNode* l)
{
    ListNode* curr = l, *prev = nullptr, *forw = l;
    while(curr)
    {
        forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    return prev;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
    l1 = reverse(l1);
    l2 = reverse(l2);
    
    ListNode* ans = new ListNode(-1), *temp = ans;
    int carry = 0;
    while(l1 && l2)
    {
        int sum = (l1->val + l2->val + carry) % 10;
        temp->next = new ListNode(sum);
        temp = temp->next;
        carry = (l1->val + l2->val + carry) / 10;
        l1 = l1->next;
        l2 = l2->next;
    }
    while(l1)
    {
        int sum = (l1->val + carry) % 10;
        temp->next = new ListNode(sum);
        temp = temp->next;
        carry = (l1->val + carry) / 10;
        l1 = l1->next;
    }
    while(l2)
    {
        int sum = (l2->val + carry) % 10;
        temp->next = new ListNode(sum);
        temp = temp->next;
        carry = (l2->val + carry) / 10;
        l2 = l2->next;
    }
    if(carry > 0)
    {
        temp->next = new ListNode(carry);
        temp = temp->next;
    }
    
    ans = reverse(ans->next);
    
    return ans;
}

// DAY 8 (Binary Tree Tilt)========================================================

int findtilt(TreeNode* node, int &tilt)
{
    if(node == nullptr)
        return 0;
    int lval = findtilt(node->left, tilt);
    int rval = findtilt(node->right, tilt);
    tilt += abs(lval - rval);
    return node->val + lval + rval;
}

int findTilt(TreeNode* root) 
{
    int tilt = 0;
    findtilt(root, tilt);
    return tilt;
}