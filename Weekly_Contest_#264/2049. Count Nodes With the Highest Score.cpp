
int tot = 0;
int count(int u, vector<vector<int>> &tree)
{
    int cnt = 0;
    for (int v : tree[u])
        cnt += count(v, tree);
    return cnt + 1;
}

long mx = 0, mxcnt = 0;
long dfs(int u, vector<vector<int>> &tree)
{
    long l = 0, r = 0, rem = 1;
    if (tree[u].size() >= 1)
        l = dfs(tree[u][0], tree);
    if (tree[u].size() == 2)
        r = dfs(tree[u][1], tree);

    rem = max(rem, tot - (l + r + 1));
    long nl = l ? l : 1;
    long nr = r ? r : 1;

    long curr = nl * nr * rem;
    if (curr > mx)
    {
        mx = curr;
        mxcnt = 1;
    }
    else if (curr == mx)
        mxcnt++;

    return l + r + 1;
}

int countHighestScoreNodes(vector<int> &parents)
{
    int n = parents.size();
    vector<vector<int>> tree(n);
    for (int i = 1; i < n; i++)
        tree[parents[i]].push_back(i);

    tot = count(0, tree);

    dfs(0, tree);

    return mxcnt;
}