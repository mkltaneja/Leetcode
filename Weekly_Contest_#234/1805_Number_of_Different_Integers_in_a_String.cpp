
int numDifferentIntegers(string word)
{
    set<string> st;
    string s = "";
    bool f = false;
    for (char c : word)
    {
        if (c - 'a' >= 0 && c - 'a' < 26)
        {
            if (f)
            {
                int i = 0;
                while (i < s.size() - 1 && s[i] == '0')
                    i++;
                s = s.substr(i);
                st.insert(s);
                s = "";
                f = false;
            }
            continue;
        }
        s += c;
        f = true;
    }
    if (f)
    {
        int i = 0;
        while (i < s.size() - 1 && s[i] == '0')
            i++;
        s = s.substr(i);
        st.insert(s);
    }
    return st.size();
}