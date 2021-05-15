
string sortSentence(string s)
{
    vector<string> ans(9);
    int cnt = 0;
    string a = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
            continue;
        if (s[i] >= '1' && s[i] <= '9')
        {
            ans[s[i] - '1'] = a;
            cnt++;
            a = "";
        }
        else
            a += s[i];
    }
    string res = "";
    for (int i = 0; i < cnt; i++)
    {
        res += ans[i] + " ";
    }
    res.pop_back();
    return res;
}