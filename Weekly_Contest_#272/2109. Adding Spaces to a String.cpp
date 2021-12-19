
string addSpaces(string s, vector<int> &spaces)
{
    int i = 0, j = 0;
    string ans = "";
    while (i < s.size() && j < spaces.size())
    {
        if (i == spaces[j])
        {
            ans += " ";
            ans += s[i];
            j++;
        }
        else
            ans += s[i];
        i++;
    }
    ans += s.substr(i);
    return ans;
}