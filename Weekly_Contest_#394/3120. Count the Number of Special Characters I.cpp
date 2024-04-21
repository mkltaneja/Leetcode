
// Time Complexity  O(n)
// Space Complexity  O(26)

class Solution {
public:
    int numberOfSpecialChars(string word) 
    {
        unordered_set<char> st;
        vector<int> done(26,0);
        int ans = 0;
        for(char c : word)
        {
            if(islower(c) && st.count(toupper(c)))
            {
                ans += 1 - done[tolower(c)-'a'];
                done[tolower(c)-'a'] = 1;
            }
            else if(isupper(c) && st.count(tolower(c)))
            {
                ans += 1 - done[tolower(c)-'a'];
                done[tolower(c)-'a'] = 1;
            }
            st.insert(c);
        }
        
        return ans;
    }
};
