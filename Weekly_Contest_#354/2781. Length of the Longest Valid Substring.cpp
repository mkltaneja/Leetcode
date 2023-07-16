class Solution {
public:
    int longestValidSubstring(string word, vector<string>& forbidden) 
    {
        int n = word.size(), m = forbidden.size();
        unordered_set<string> st;
        for(string &s : forbidden)
            st.insert(s);
        
        int ans = 0, end = n-1;
        for(int i = n-1; i >= 0; i--)
        {
            string x = "";
            for(int j = i; j < i + 10 && j <= end; j++)
            {
                x += word[j];
                if(st.count(x))
                {
                    end = j - 1;
                    break;
                }
            }
            ans = max(ans, end - i + 1);
        }
        
        return ans;
    }
};
