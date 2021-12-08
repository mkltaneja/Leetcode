
int uniqueLetterString(string s)
{
    int n = s.size();
    vector<int> llo(26, -1), rlo(26, n), lcontr(n, 0), rcontr(n, 0);

    for (int i = 0; i < n; i++)
    {
        lcontr[i] = i - llo[s[i] - 'A'];
        llo[s[i] - 'A'] = i;

        rcontr[n - i - 1] = rlo[s[n - i - 1] - 'A'] - (n - i - 1);
        rlo[s[n - i - 1] - 'A'] = (n - i - 1);
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans += lcontr[i] * rcontr[i];

    return ans;
}