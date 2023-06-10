// APPROACH 1 (Using string and set)

class Solution {
public:
    
    unordered_set<char> st;
    bool has0(string s)
    {
        for(char c : s)
        {
            if(c == '0')
                return true;
            if(st.count(c))
                return true;
            st.insert(c);
        }
        return false;
    }
    
    bool isFascinating(int n) 
    {
        string n2 = to_string(n*2), n3 = to_string(n*3);
        string n1 = to_string(n);
        return !has0(n1) && !has0(n2) && !has0(n3);
    }
};

// APPROACH 2 (Without string and set) [OPTIMIZED]

class Solution {
public:
    bool isFascinating(int n) 
    {
        vector<int> cnt(10);
        for(int i = 1; i <= 3; i++)
        {
            int x = n*i;
            while(x)
            {
                if(cnt[x%10]++) return false;
                x /= 10;
            }
        }
        
        return cnt[0] == 0;
    }
};
