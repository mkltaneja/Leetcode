class Solution {
public:
    int minMovesToMakePalindrome(string s) 
    {
        int swaps = 0;
        while(!s.empty())
        {
            char last = s.back();
            int x = s.find(last);

            if(x == s.size()-1) swaps += s.size()/2;
            else 
            {
                swaps += x;
                s.erase(x,1);
            }
            s.pop_back();
        }

        return swaps;
    }
};
