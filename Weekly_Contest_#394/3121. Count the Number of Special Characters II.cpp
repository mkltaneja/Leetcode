
// Time Complexity = O(n)
// Space Complexity = O(26)

class Solution {
public:
    int numberOfSpecialChars(string word) 
    {
        unordered_set<char> st;
        vector<int> done(26,0);
        vector<int> cnt(26, 0);
        int ans = 0;
        for(char c : word)
        {
            if(islower(c))
            {
                if(cnt[toupper(c)-'A'])
                    cnt[toupper(c)-'A']--, ans--;
            }
            else
            {
                if(st.count(tolower(c)) && !done[c-'A'])
                {
                    ans++;
                    cnt[c-'A'] = 1;
                }
                done[c-'A'] = 1;
            }
            st.insert(c);
        }
        
        return ans;
    }
};
