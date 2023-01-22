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
