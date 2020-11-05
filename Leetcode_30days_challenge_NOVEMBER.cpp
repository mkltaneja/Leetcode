
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