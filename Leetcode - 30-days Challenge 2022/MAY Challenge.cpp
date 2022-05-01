// DAY 1 (844. Backspace String Compare)=========================================================================================================================

bool backspaceCompare(string s, string t) 
{
    int i = s.size() - 1, j = t.size() - 1;
    while(i >= 0 || j >= 0)
    {
        int bs = 0, bt = 0;
        while(i >= 0 && s[i] == '#') bs++, i--;
        while(j >= 0 && t[j] == '#') bt++, j--;

        while(i >= 0 && bs)
        {
            if(s[i] == '#') bs++;
            else bs--;
            i--;
        }
        while(j >= 0 && bt)
        {
            if(t[j] == '#') bt++;
            else bt--;
            j--;
        }

        if(i >= 0 && j >= 0 && s[i] != '#' && t[j] != '#')
            if(s[i] != t[j])
                return false;
            else i--, j--;
        else if(((i >= 0 && j < 0 && s[i] != '#') || (j >= 0 && i < 0 && t[j] != '#')))
            return false;
    }

    return true;
}
