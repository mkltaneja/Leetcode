
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
