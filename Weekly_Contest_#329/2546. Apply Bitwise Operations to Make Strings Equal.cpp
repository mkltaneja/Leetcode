
// METOHD 1 (Naive - counted 1s, checked for 0s, checked for 1s) --> time = O(3*n)

class Solution {
public:
    bool makeStringsEqual(string s, string target) 
    {
        int n = s.size();
        int one = 0;
        for(int i = 0; i < n; i++)
            one += s[i] == '1';
        
        for(int i = 0; i < n; i++)
        {
            if(s[i] == '0' && target[i] == '1')
            {
                if(!one) return false;
                one++;
                s[i] = '1';
            }
        }

        for(int i = 0; i < n; i++)
        {
            if(s[i] == '1' && target[i] == '0')
            {
                if(one < 2) return false;
                one--;
            }
        }
        
        return true;
    }
};

// METOHD 2 (OPTIMIZED) --> time = O(n)

class Solution {
public:
    bool makeStringsEqual(string s, string target) 
    {
        if(s == target) return true;
        
        string zero = string(s.size(), '0');
        return (s != zero) && (target != zero);
    }
};
