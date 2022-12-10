class Solution {
public:
    int maximumValue(vector<string>& strs) 
    {
        int mx = 0;
        for(string &s : strs)
        {
            bool num = true;
            int x = 0;
            for(char c : s)
            {
                if(!(c >= '0' && c <= '9'))
                {
                    num = false;
                    break;
                }
                else x = x*10 + (c-'0');
            }
            if(num) mx = max(mx, x);
            else mx = max(mx, (int)s.size());
        }
        
        return mx;
    }
};
