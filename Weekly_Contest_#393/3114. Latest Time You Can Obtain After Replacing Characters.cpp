
// Time Complexity = O(1)
// Space Complexity = O(1)

class Solution {
public:
    string findLatestTime(string s) 
    {
        if(s[0] == '?')
            s[0] = (s[1] == '0' || s[1] == '1' || s[1] == '?')? '1' : '0';
        if(s[1] == '?')
            s[1] = s[0] == '0'? '9' : '1';
        if(s[3] == '?')
            s[3] = '5';
        if(s[4] == '?')
            s[4] = '9';
        return s;
    }
};