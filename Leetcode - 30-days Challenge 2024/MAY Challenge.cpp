
// DAY 1 (2000. Reverse Prefix of Word)=======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string reversePrefix(string word, char ch) 
{
    int size = word.size();
    string ans = "";
    bool found = false;
    for(int partIdx = 0; partIdx < size; partIdx++)
    {
        ans += word[partIdx];
        if(word[partIdx] == ch && !found)
        {
            reverse(ans.begin(), ans.end());
            found = true;
        }
    }

    return ans;
}
