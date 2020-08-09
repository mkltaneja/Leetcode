// Method 1

string makeGood(string s)
{
    while (true)
    {
        bool f = false;
        for (int i = 0;i<s.size();i++)
        {
            if ((s[i+1] == toupper(s[i]) && s[i] == tolower(s[i])) || (s[i+1] == tolower(s[i]) && s[i] == toupper(s[i])))
            {
                f = true;
                s.erase(i, 2);
                i--;
            }
        }
        if (!f)
            break;
    }
    return s;
}

////////////////////////OR//////////////////

// Method 2 

string makeGood(string s)
{
    string t = "";
    for (char c : s)
    {
        if (!t.empty())
        {
            char a = t.back();
            if (tolower(a) == tolower(c) && a != c)
            {
                t.pop_back();
                continue;
            }
        }
        t.push_back(c);
    }
    return t;
}