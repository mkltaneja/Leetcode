
// APPROACH 1 (Memoized)

unordered_map<char, int> mpi;
unordered_map<char, vector<char>> mp;
int m = 1e9 + 7;
int dfs(char u, int n, vector<vector<int>> &dp)
{
    if (n == 1)
        return 1;
    if (dp[mpi[u]][n])
        return dp[mpi[u]][n];

    int ans = 0;
    for (char v : mp[u])
        ans = (ans % m + dfs(v, n - 1, dp) % m) % m;

    return dp[mpi[u]][n] = ans % m;
}

int countVowelPermutation(int n)
{
    mpi['a'] = 0;
    mpi['e'] = 1;
    mpi['i'] = 2;
    mpi['o'] = 3;
    mpi['u'] = 4;

    mp['a'] = {'e'};
    mp['e'] = {'a', 'i'};
    mp['i'] = {'a', 'e', 'o', 'u'};
    mp['o'] = {'i', 'u'};
    mp['u'] = {'a'};

    vector<vector<int>> dp(5, vector<int>(n + 1, 0));
    int ans = 0;
    for (auto p : mp)
        ans = (ans % m + dfs(p.first, n, dp) % m) % m;

    return ans % m;
}

// APPROACH 2 (Tabulated [Space OPTIMIZED])

int m = 1e9 + 7;
int countVowelPermutation(int n)
{
    long pa, pe, pi, po, pu;
    pa = pe = pi = po = pu = 1;
    for (int x = 1; x < n; x++)
    {
        long a = pe % m;
        long e = (pa + pi) % m;
        long i = (pa + pe + po + pu) % m;
        long o = (pi + pu) % m;
        long u = pa % m;

        pa = a;
        pe = e;
        pi = i;
        po = o;
        pu = u;
    }

    return (pa + pe + pi + po + pu) % m;
}