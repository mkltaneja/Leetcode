
bool areNumbersAscending(string s)
{
    int l = -1;
    for (int i = 0; i < s.size(); i++)
    {
        int x = 0, f = 0;
        while (i < s.size() && s[i] >= '0' && s[i] <= '9')
        {
            x = x * 10 + (s[i++] - '0');
            f = 1;
        }
        if (f)
        {
            i--;
            if (x <= l)
                return false;
            l = x;
        }
    }
    return true;
}