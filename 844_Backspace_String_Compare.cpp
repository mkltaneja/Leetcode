
bool backspaceCompare(string S, string T)
{
    stack<char> st1, st2;
    for (char c : S)
    {
        if (c == '#')
        {
            if (st1.empty())
                continue;
            st1.pop();
        }
        else
            st1.push(c);
    }
    for (char c : T)
    {
        if (c == '#')
        {
            if (st2.empty())
                continue;
            st2.pop();
        }
        else
            st2.push(c);
    }
    string s = "", t = "";
    while (!st1.empty())
    {
        s += st1.top();
        st1.pop();
    }
    while (!st2.empty())
    {
        t += st2.top();
        st2.pop();
    }
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());

    return s == t;
}