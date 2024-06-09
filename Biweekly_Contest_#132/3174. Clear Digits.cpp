
// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    string clearDigits(string s) 
    {
        string ans = "";
        for(char c : s)
        {
            if(c >= '0' && c <= '9')
            {
                if(!ans.empty())
                    ans.pop_back();
            }
            else ans += c;
        }
        return ans;
    }
};
