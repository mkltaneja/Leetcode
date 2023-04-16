class Solution {
public:
    int addMinimum(string word) 
    {
        char p = 'c';
        int ans = 0;
        for(char c : word)
        {
            if(c == 'a')
                ans += ('c' - p);
            else if(c == 'b')
                ans += p == 'b'? 2 : (p == 'c'? 1 : 0);
            else 
                ans += p == 'c'? 2 : (p == 'a'? 1 : 0);
            p = c;
        }
        ans += ('c' - p);
        
        return ans;
    }
};
