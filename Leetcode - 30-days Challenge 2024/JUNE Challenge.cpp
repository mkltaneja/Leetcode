
// DAY 1 (3110. Score of a String)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int scoreOfString(string s) 
{
    int score = 0;
    for(int idx = 1; idx < s.size(); idx++)
        score += abss[idx] - s[idx-1];
    return score;
}

// DAY 2 (344. Reverse String)===============================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

void reverseString(vector<char>& s) 
{
    int start = 0, end = s.size()-1;
    while(start < end)
        swap(s[start++], s[end--]);
}

// DAY 3 (2486. Append Characters to String to Make Subsequence)====================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int appendCharacters(string s, string t)
{
    int sSize = s.size(), tSize = t.size();
    int idx1 = 0, idx2 = 0;
    while(idx1 < sSize && idx2 < tSize)
    {
        if(s[idx1] == t[idx2])
            idx2++;
        idx1++;
    }
    return tSize - idx2;
}
