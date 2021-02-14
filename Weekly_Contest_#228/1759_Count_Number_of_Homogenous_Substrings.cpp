
// METHOD 1 (Using 2 pointer apporach (2 loops)) --> O(n)

int mod = 1e9 + 7;
int countHomogenous(string s)
{
    long long i = 0, j = 0;
    long long cnt = 0;
    string tmp = "";
    while (i < s.size())
    {
        char c = s[i];
        while (i < s.size() && s[i] == c)
            i++;
        long long n = i - j;
        cnt += (n * (n + 1)) % mod / 2;
        j = i;
    }

    return cnt;
}

// METHOD 2 (Single loop) --> O(n)

int mod = 1e9 + 7;
int countHomogenous(string s)
{
    long long cnt = 0, ans = 0;
    char prev = NULL;
    for (char c : s)
    {
        if (c == prev)
            cnt++;
        else
        {
            ans += (cnt * (cnt + 1)) / 2;
            cnt = 1;
            prev = c;
        }
    }
    ans += (cnt * (cnt + 1)) / 2;

    return ans % mod;
}