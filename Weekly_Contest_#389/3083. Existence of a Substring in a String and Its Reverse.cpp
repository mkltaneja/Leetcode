
// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    bool isSubstringPresent(string s) 
    {
        int n = s.size();
        unordered_set<string> st;
        for(int i = 0; i < n-1; i++)
            st.insert(s.substr(i, 2));
        reverse(s.begin(), s.end());
        for(int i = 0; i < n-1; i++)
            if(st.count(s.substr(i, 2)))
                return true;
        return false;
    }
};
