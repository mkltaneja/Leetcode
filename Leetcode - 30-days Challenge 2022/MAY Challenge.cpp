// DAY 1 (844. Backspace String Compare)=========================================================================================================================

bool backspaceCompare(string s, string t) 
{
    int i = s.size() - 1, j = t.size() - 1;
    while(i >= 0 || j >= 0)
    {
        int bs = 0, bt = 0;
        while(i >= 0 && s[i] == '#') bs++, i--;
        while(j >= 0 && t[j] == '#') bt++, j--;

        while(i >= 0 && bs)
        {
            if(s[i] == '#') bs++;
            else bs--;
            i--;
        }
        while(j >= 0 && bt)
        {
            if(t[j] == '#') bt++;
            else bt--;
            j--;
        }

        if(i >= 0 && j >= 0 && s[i] != '#' && t[j] != '#')
            if(s[i] != t[j])
                return false;
            else i--, j--;
        else if(((i >= 0 && j < 0 && s[i] != '#') || (j >= 0 && i < 0 && t[j] != '#')))
            return false;
    }

    return true;
}

// DAY 2 (905. Sort Array By Parity)=========================================================================================================================

vector<int> sortArrayByParity(vector<int>& nums) 
{
    int i = 0, j = 0;
    while(i < nums.size())
    {
        if(nums[i] & 1 ^ 1) 
            swap(nums[i], nums[j++]);
        i++;
    }
    return nums;
}

// DAY 5 (225. Implement Stack using Queues)=========================================================================================================================

// APPROACH 1 (Using 2 queues)
class MyStack {
public:
    
    queue<int> q1, q2;
    MyStack() {
        
    }
    
    void push(int x) 
    {
        q2.push(x);
        while(!q1.empty())
        {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }
    
    int pop() 
    {
        int x = q1.front();
        q1.pop();
        return x;
    }
    
    int top() 
    {
        return q1.front();
    }
    
    bool empty() 
    {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

// APPROACH 2 (Using 1 queue)
class MyStack {
public:
    
    queue<int> q;
    int size;
    MyStack() 
    {
        this->size = 0;
    }
    
    void push(int x) 
    {
        q.push(x);
        int tmp = size;
        while(tmp--)
        {
            q.push(q.front());
            q.pop();
        }
        size++;
    }
    
    int pop() 
    {
        int x = q.front();
        q.pop();
        size--;
        return x;
    }
    
    int top() 
    {
        return q.front();
    }
    
    bool empty() 
    {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

// DAY 6 (1209. Remove All Adjacent Duplicates in String II)=========================================================================================================================

string removeDuplicates(string s, int k) 
{
    stack<pair<char, int>> st;
    for(char c : s)
    {
        st.push((!st.empty() && st.top().first==c)? make_pair(c, st.top().second+1) : make_pair(c,1));
        if(st.top().second == k)
            while(!st.empty() && st.top().first == c)
                st.pop();
    }
    string ans = "";
    while(!st.empty())
    {
        ans += st.top().first;
        st.pop();
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

// DAY 7 (456. 132 Pattern)=========================================================================================================================

bool find132pattern(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> mn(n);
    mn[0] = nums[0];
    for(int i = 1; i < n; i++)
        mn[i] = min(mn[i-1], nums[i]);

    stack<int> st;
    for(int i = n-1; i >= 0; i--)
    {
        while(!st.empty() && st.top() < nums[i])
        {
            if(st.top() > mn[i])
                return true;
            st.pop();
        }
        st.push(nums[i]);
    }

    return false;
}

// DAY 8 (341. Flatten Nested List Iterator)=========================================================================================================================

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
public:
    
    int itr = 0;
    vector<int> list;
    void flatten(vector<NestedInteger> &nlist)
    {
        for(int i = 0; i < nlist.size(); i++)
        {
            if(!nlist[i].isInteger())
                flatten(nlist[i].getList());
            else list.push_back(nlist[i].getInteger());
        }
    }
    
    NestedIterator(vector<NestedInteger> &nestedList) 
    {
        flatten(nestedList);
    }
    
    int next()
    {
        return list[itr++];
    }
    
    bool hasNext() 
    {
        return itr < list.size();
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

// DAY 9 (17. Letter Combinations of a Phone Number)=========================================================================================================================

vector<string> map = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

vector<string> ans;
void dfs(int i, string tmp, string &dig)
{
    if(i == dig.size()) 
    {
        if(!tmp.empty()) ans.push_back(tmp);
        return;
    }        
    for(int j = 0; j < map[dig[i]-'0'].size(); j++)
        dfs(i+1, tmp+map[dig[i]-'0'][j], dig);
}

vector<string> letterCombinations(string digits) 
{
    dfs(0, "", digits);
    return ans;
}

// DAY 10 (216. Combination Sum III)=========================================================================================================================

vector<vector<int>> ans;
void dfs(vector<int> &curr, int last, int k, int n)
{
    if(k == 0 && n == 0)
    {
        ans.push_back(curr);
        return;
    }

    for(int x = last; x <= 9 && n-x >= 0; x++)
    {
        curr.push_back(x);
        dfs(curr, x+1, k-1, n-x);
        curr.pop_back();
    }
}

vector<vector<int>> combinationSum3(int k, int n) 
{
    vector<int> curr;
    dfs(curr, 1, k, n);
    return ans;
}
