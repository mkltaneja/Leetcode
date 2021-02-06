
int minimumLength(string s)
{
    int n = s.size();
    int i = 0, j = n - 1;
    while (i < j)
    {
        if (i == j)
            return 1;
        if (s[i] != s[j])
            break;
        char a = s[i];
        int pi = i;
        while (i <= j && s[i] == a)
            i++;
        while (j >= i && s[j] == a)
            j--;
    }
    return (j - i + 1);
}