
bool checkZeroOnes(string s)
{
    int mo = 0, mz = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int j = i;
        while (j < s.size() && s[j] == s[i])
            j++;
        if (s[i] == '0')
            mz = max(mz, j - i);
        else
            mo = max(mo, j - i);
    }
    return mo > mz;
}