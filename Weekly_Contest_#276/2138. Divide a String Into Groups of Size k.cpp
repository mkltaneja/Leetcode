
vector<string> divideString(string s, int k, char fill)
{
    vector<string> ans;
    int i = 0;
    for (; i + k <= s.size(); i += k)
        ans.push_back(s.substr(i, k));
    if (i < s.size())
    {
        string x = s.substr(i);
        while (x.size() < k)
            x += fill;
        ans.push_back(x);
    }
    return ans;
}