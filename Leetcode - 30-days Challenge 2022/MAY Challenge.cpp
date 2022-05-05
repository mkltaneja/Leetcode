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
