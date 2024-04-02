
// DAY 1 (58. Length of Last Word)=============================================================================================================

// Time Complexity = <O(n)
// Space Complexity = O(1)

int lengthOfLastWord(string s) 
{
    int len = 0;
    for(int idx = s.size()-1; idx >= 0; idx--)
    {
        if(s[idx] == ' ')
        {
            if(len) return len;
            continue;
        }
        len++;
    }
    return len;
}

// DAY 2 (205. Isomorphic Strings)====================================================================================

// Time Complexity = O(n)
// Space Complexity = O(256)

bool isIsomorphic(string s, string t) 
{
    unordered_map<char,char> sCharMap, tCharMap;
    for(int idx = 0; idx < s.size(); idx++)
    {
        char a = s[idx], b = t[idx];
        if(sCharMap[a] && sCharMap[a] != b)
            return false;
        if(!sCharMap[a] && tCharMap[b] && tCharMap[b] != a)
            return false;
        sCharMap[a] = b;
        tCharMap[b] = a;
    }
    return true;
}
