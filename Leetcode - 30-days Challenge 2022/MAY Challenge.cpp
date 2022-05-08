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
