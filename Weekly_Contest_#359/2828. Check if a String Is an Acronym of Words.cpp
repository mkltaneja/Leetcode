class Solution {
public:
    bool isAcronym(vector<string>& words, string s) 
    {
        string s1 = "";
        for(auto x : words)
            s1 += x[0];
        return s1 == s;
    }
};
