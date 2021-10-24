
string p = "";
int hc = 0, dc = 0, pc = 0, hp = -1;
bool check()
{
    bool fl = true;
    if (p.empty() || pc > 1 || hc > 1 || dc)
        fl = false;
    else
    {
        if (pc && (p.back() != '!' && p.back() != '.' && p.back() != ','))
            fl = false;
        if (hc && ((hp == 0 || hp == p.size() - 1) || !(p[hp - 1] >= 'a' && p[hp - 1] <= 'z') || !(p[hp + 1] >= 'a' && p[hp + 1] <= 'z')))
            fl = false;
    }
    return fl;
}

int countValidWords(string s)
{
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            bool fl = check();
            if (fl)
                ans++;
            p = "";
            hc = 0, dc = 0, pc = 0, hp = -1;
            continue;
        }
        if (s[i] >= '0' && s[i] <= '9')
            dc++;
        else if (s[i] == '-')
        {
            hc++;
            hp = p.size();
        }
        else if (s[i] == '!' || s[i] == '.' || s[i] == ',')
            pc++;
        p += s[i];
    }
    bool fl = check();
    if (fl)
        ans++;

    return ans;
}