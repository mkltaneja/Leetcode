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

// DAY 13 (20. Valid Parentheses)=========================================================================================================================

bool isValid(string s) 
{
    stack<char> st;
    for(char c : s)
    {
        if(c == '(' || c == '{' || c == '[')
            st.push(c);
        else 
        {
            if(c == ')' && (st.empty() || st.top() != '('))
                return false;
            if(c == '}' && (st.empty() || st.top() != '{'))
                return false;
            if(c == ']' && (st.empty() || st.top() != '['))
                return false;
            st.pop();
        }
    }
    return st.empty();
}

// DAY 14 (71. Simplify Path)=========================================================================================================================

string simplifyPath(string path) 
{
    int i = 0, n = path.size();
    string ans = "";
    stack<string> st;
    while(i < n)
    {
        string tmp = "";
        while(i < n && path[i] == '/') i++;

        while(i < n && path[i] != '/')
            tmp += path[i++];
        if(tmp.empty() || tmp == ".") continue;

        if(tmp == "..")
        {
            if(!st.empty())
                st.pop();
        }
        else st.push(tmp);
    }

    vector<string> tmp;
    while(!st.empty())
    {
        tmp.push_back(st.top());
        st.pop();
    }
    reverse(tmp.begin(), tmp.end());

    for(string s : tmp)
        ans += "/" + s;

    return ans.empty()? "/" : ans;
}

// DAY 15 (1249. Minimum Remove to Make Valid Parentheses)=========================================================================================================================

string minRemoveToMakeValid(string s) 
{
    vector<int> st;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == '(') st.push_back(i);
        else if(s[i] == ')') 
        {
            if(st.empty() || s[st.back()] == ')') st.push_back(i);
            else if(s[st.back()] == '(') st.pop_back();
        }
    }
    string ans = "";
    for(int i = 0, j = 0; i < s.size(); i++)
    {
        if(j < st.size() && i == st[j]) 
        {
            j++;
            continue;
        }
        ans += s[i];
    }
    return ans;
}

// DAY 16 (946. Validate Stack Sequences)=========================================================================================================================

bool validateStackSequences(vector<int>& pushed, vector<int>& popped) 
{
    stack<int> st;
    for(int i = 0, j = 0; i < pushed.size() && j < popped.size(); i++)
    {
        st.push(pushed[i]);
        while(!st.empty() && j < popped.size() && popped[j] == st.top())
        {
            st.pop();
            j++;
        }
    }

    return st.empty();
}

// DAY 17 (856. Score of Parentheses)=========================================================================================================================

int scoreOfParentheses(string s) 
{
    stack<int> st;
    st.push(0);
    for(char c : s)
    {
        if(c == '(') st.push(0);
        else 
        {
            int tp = st.top();
            st.pop();
            int x = 0;
            if(tp == 0) x = 1;
            else x = tp*2;

            st.top() += x;
        }
    }

    return st.top();
}

// DAY 18 (316. Remove Duplicate Letters)=========================================================================================================================

string removeDuplicateLetters(string s) 
{
    string ans = "";
    vector<int> cnt(26);
    vector<bool> vis(s.size(), false);
    for(char c : s)
        cnt[c-'a']++;

    for(char c : s)
    {
        cnt[c-'a']--;
        if(vis[c-'a']) continue;

        while(!ans.empty() && c < ans.back() && cnt[ans.back()-'a'])
        {
            vis[ans.back()-'a'] = false;
            ans.pop_back();
        }
        ans += c;
        vis[c-'a'] = true;
    }

    return ans;
}

// DAY 19 (895. Maximum Frequency Stack)=========================================================================================================================

unordered_map<int,int> mp;
vector<vector<int>> st;
FreqStack() 
{

}

void push(int val) 
{
    int x = mp[val]++;
    if(x == st.size()) st.push_back({val});
    else st[x].push_back(val);
}

int pop() 
{
    int ans = st.back().back();
    st.back().pop_back();
    if(st[st.size()-1].empty()) st.pop_back();
    mp[ans]--;
    return ans;
}

// DAY 20 (1007. Minimum Domino Rotations For Equal Row)=========================================================================================================================

int check(int x, vector<int> &tops, vector<int> &bottoms)
{
    int topx = 0, bottomx = 0;
    for(int i = 0; i < tops.size(); i++)
    {
        if(tops[i] != x && bottoms[i] != x)
            return -1;
        else 
        {
            topx += tops[i] == x;
            bottomx += bottoms[i] == x;
        }
    }
    return max(topx, bottomx);
}

int minDominoRotations(vector<int>& tops, vector<int>& bottoms) 
{
    int ans = INT_MAX;
    for(int x : {tops[0], bottoms[0]})
    {
        int xx = check(x, tops, bottoms);
        if(xx == -1) continue;
        ans = min(ans, (int)tops.size() - xx);
    }
    return ans == INT_MAX? -1 : ans;
}

// DAY 21 (1663. Smallest String With A Given Numeric Value)=========================================================================================================================

string getSmallestString(int n, int k) 
{
    int val = n;
    string ans(n, 'a');
    for(int i = n-1; i >= 0 && val != k; i--)
    {
        int x = min(k - val, 25);
        val += x;
        ans[i] = x + 'a';
    }
    return ans;
}
