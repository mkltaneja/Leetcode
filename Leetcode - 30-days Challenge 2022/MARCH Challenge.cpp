// DAY 1 (338. Counting Bits)=========================================================================================================================

// APPROACH 1 (Naive)
vector<int> countBits(int n) 
{
    vector<int> ans(n+1);
    for(int i = 0; i <= n; i++)
    {
        int x = i, cnt = 0;
        while(x)
        {
            x &= x-1;
            cnt++;
        }
        ans[i] = cnt;
    }
    return ans;
}

// APPROACH 2 (DP)

vector<int> countBits(int n) 
{
    vector<int> ans(n+1);
    for(int i = 1; i <= n; i++)
        ans[i] = ans[i & (i-1)] + 1;
    return ans;
}

// DAY 2 (392. Is Subsequence)=========================================================================================================================

bool isSubsequence(string s, string t) 
{
    int i = 0, j = 0, n = s.size(), m = t.size();
    while(i < n && j < m)
    {
        if(s[i] == t[j]) i++;
        j++;
    }
    return i == n;
}

// DAY 3 (413. Arithmetic Slices)=========================================================================================================================

int numberOfArithmeticSlices(vector<int>& nums) 
{
    int i = 2, j = 0, n = nums.size();
    int ans = 0;
    while(i < n)
    {
        if(2*nums[i-1] == nums[i-2] + nums[i]) 
            ans += i-j-1;
        else j = i-1;
        i++;
    }
    return ans;
}

// DAY 4 (799. Champagne Tower)=========================================================================================================================

double champagneTower(int poured, int query_row, int query_glass) 
{
    vector<double> glasses(1);
    glasses[0] = poured;

    for(int i = 0; i < query_row; i++)
    {
        vector<double> nglasses(i+2);
        for(int j = 0; j <= i; j++)
        {
            double x = (glasses[j] - 1) / 2.0;
            if(x <= 0) continue;
            nglasses[j] += x;
            nglasses[j+1] += x;
        }

        glasses = nglasses;
    }
    return min(1.0, glasses[query_glass]);
}

// DAY 5 (740. Delete and Earn)=========================================================================================================================

int deleteAndEarn(vector<int>& nums) 
{
    map<int,int> mp;
    for(int x : nums)
        mp[x]++;

    int inc = 0, exc = 0;
    int prev = -1;
    for(auto p : mp)
    {
        int nexc = max(inc, exc);
        int ninc = p.first * p.second + (prev+1 == p.first? exc : nexc);

        inc = ninc;
        exc = nexc;
        prev = p.first;
    }

    return max(inc, exc);
}

// DAY 6 (1359. Count All Valid Pickup and Delivery Options)=========================================================================================================================

int countOrders(int n) 
{
    int mod = 1e9 + 7;
    long ans = 1;
    while(n)
    {
        ans = (ans * (long)(n * (2*n - 1)) % mod) % mod;
        n--;
    }
    return ans;
}

// DAY 7 (21. Merge Two Sorted Lists)=========================================================================================================================

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) 
{
    ListNode* ans = new ListNode(-101), *itr = ans;
    while(list1 || list2)
    {
        int x = list1? list1->val : INT_MAX;
        int y = list2? list2->val : INT_MAX;
        if(x < y)
        {
            itr->next = list1;
            list1 = list1->next;
        }
        else
        {
            itr->next = list2;
            list2 = list2->next;
        }
        itr = itr->next;
    }
    return ans->next;
}

// DAY 8 (141. Linked List Cycle)=========================================================================================================================

bool hasCycle(ListNode *head) 
{
    ListNode* fast = head, *slow = head;
    while(fast && fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
            return true;
    }
    return false;
}

// DAY 9 (82. Remove Duplicates from Sorted List II)=========================================================================================================================

ListNode* deleteDuplicates(ListNode* head) 
{
    ListNode* ans = new ListNode(-1), *itr = head, *tmp = ans;
    while(itr)
    {
        ListNode* itr2 = itr->next;
        while(itr2 && itr2->val == itr->val)
            itr2 = itr2->next;
        if(itr2 == itr->next)
        {
            tmp->next = new ListNode(itr->val);
            tmp = tmp->next;
        }
        itr = itr2;
    }
    return ans->next;
}

// DAY 10 (61. Rotate List)=========================================================================================================================

ListNode* rotateRight(ListNode* head, int k) 
{
    if(!head || !head->next) return head;

    int n = 0;
    ListNode* itr = head, *tail = nullptr;
    while(itr)
    {
        tail = itr;
        itr = itr->next;
        n++;
    }

    k = k % n;
    if(k == 0) return head;

    int x = n-k;
    ListNode* tmp = head;
    while(--x)
    {
        tmp = tmp->next;
    }
    ListNode* tmp2 = tmp->next;
    tmp->next = nullptr;
    tail->next = head;
    return tmp2;
}

// DAY 11 (138. Copy List with Random Pointer)=========================================================================================================================
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) 
    {
        unordered_map<Node*, Node*> mp;
        Node* ans = nullptr, *prev = nullptr, *itr = head;
        while(itr)
        {
            Node* nnode = new Node(itr->val);
            mp[itr] = nnode;
            if(!ans) ans = nnode;
            else prev->next = nnode;
            
            prev = nnode;
            itr = itr->next;
        }
        itr = head;
        Node* itr2 = ans;
        while(itr)
        {
            itr2->random = mp[itr->random];
            itr = itr->next;
            itr2 = itr2->next;
        }
        return ans;
    }
};
