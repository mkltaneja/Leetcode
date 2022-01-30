
vector<int> par, psize;
int ans1, ans2;

int findpar(int u)
{
    return par[u] = par[u] == u ? u : findpar(par[u]);
}
void merge(int a, int b)
{
    int pa = findpar(a);
    int pb = findpar(b);

    if (pa == pb)
        return;

    if (psize[pa] >= psize[pb])
    {
        par[pb] = pa;
        psize[pa] += psize[pb];
        ans1--;
        ans2 = max(ans2, psize[pa]);
    }
    else
    {
        par[pa] = pb;
        psize[pb] += psize[pa];
        ans1--;
        ans2 = max(ans2, psize[pb]);
    }
}

vector<int> groupStrings(vector<string> &words)
{
    int n = words.size();
    par.resize(n);
    psize.resize(n, 1);
    ans1 = n, ans2 = 1;

    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++)
        par[i] = i;
    for (int i = 0; i < n; i++)
    {
        int x = 0;
        for (char c : words[i])
            x |= (1 << (c - 'a'));
        if (mp.count(x))
            merge(i, mp[x]);
        else
            mp[x] = i;
    }

    for (auto p : mp)
    {
        int x = p.first, idx = p.second;
        for (int i = 25; i >= 0; i--)
        {
            int y = x | (1 << i);
            if ((x >> i & 1 ^ 1) && mp.count(y))
                merge(idx, mp[y]);
        }
    }
    for (auto p : mp)
    {
        int x = p.first, idx = p.second;
        for (int i = 25; i >= 0; i--)
        {
            int y = x & ~(1 << i);
            if ((x >> i & 1) && mp.count(y))
                merge(idx, mp[y]);
        }
    }
    for (auto p : mp)
    {
        int x = p.first, idx = p.second;
        for (int i = 25; i >= 0; i--)
        {
            if (x >> i & 1)
            {
                for (int j = 0; j <= 25; j++)
                {
                    int y = ((x | (1 << j)) & ~(1 << i));
                    if ((x >> j & 1 ^ 1) && mp.count(y))
                        merge(idx, mp[y]);
                }
            }
        }
    }

    return {ans1, ans2};
}