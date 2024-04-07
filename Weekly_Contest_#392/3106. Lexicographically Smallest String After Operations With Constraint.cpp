
// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    string getSmallestString(string s, int k) 
    {
        string ans = "";
        for(char c : s)
        {
            int d1 = c - 'a';
            int d2 = 26 - d1;
            if(d2 <= k && d2 <= d1)
            {
                ans += 'a';
                k -= d2;
            }
            else
            {
                d1 = min(d1, k);
                ans += char(c - 'a' - d1 + 'a');
                k -= d1;
            }
        }
        return ans;
    }
};
