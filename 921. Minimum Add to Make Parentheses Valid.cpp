
int minAddToMakeValid(string s)
{
    int oc = 0, cc = 0;
    for (char c : s)
    {
        if (c == '(')
            oc++;
        else
            oc ? oc-- : cc++;
    }
    return oc + cc;
}