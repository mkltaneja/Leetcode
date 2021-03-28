
string evaluate(string ss, vector<vector<string>> &knowledge)
{
    string ans = "";
    unordered_map<string, string> m;
    for (auto v : knowledge)
        m[v[0]] = v[1];

    bool open = false;
    string s = "";
    for (char c : ss)
    {
        if (c == '(')
            open = true;
        else if (c == ')')
        {
            open = false;
            ans += (m.count(s) > 0) ? m[s] : "?";
            s = "";
        }
        else if (open)
            s += c;
        else
            ans += c;
    }
    return ans;
}