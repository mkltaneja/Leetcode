
// DAY 1 (557. Reverse Words in a String III)=========================================================================

string reverseWords(string s) 
{
    string ans = "", prev = "";
    for(int i = 0; i <= s.size(); i++)
    {
        if(i == s.size() || s[i] == ' ')
        {
            reverse(prev.begin(), prev.end());
            ans += prev + (i != s.size()? " " : "");
            prev = "";
        }
        else prev += s[i];
    }

    return ans;
}
