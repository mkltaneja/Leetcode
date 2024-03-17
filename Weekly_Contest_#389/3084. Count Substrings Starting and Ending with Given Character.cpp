
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    
    #define ll long long
    long long countSubstrings(string s, char c) 
    {
        ll ans = 0, cnt = 0;
        for(char x : s)
            if(x == c)
                ans += cnt++ + 1;
        return ans;
    }
};
