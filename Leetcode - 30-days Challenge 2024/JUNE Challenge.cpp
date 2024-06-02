
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
