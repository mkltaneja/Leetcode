class Solution {
public:
    int findMinimumOperations(string s1, string s2, string s3) 
    {
        int i = 0;
        int p = s1.size(), q = s2.size(), r = s3.size();
        while(i < s1.size() && i < s2.size() && i < s3.size() && s1[i] == s2[i] && s2[i] == s3[i])
            i++;
        return i? (p - i) + (q - i) + (r - i) : -1;
    }
};
