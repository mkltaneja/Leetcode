
unordered_map<string, string> par;
unordered_map<string, int> rank;
string findPar(string u)
{
    if (par[u] == u)
        return u;
    return par[u] = findPar(par[u]);
}
void merge(string u, string v)
{
    string pu = findPar(u);
    string pv = findPar(v);

    if (pu != pv)
    {
        if (rank[pu] > rank[pv])
            par[pv] = pu;
        else if (rank[pv] > rank[pu])
            par[pu] = pv;
        else
        {
            par[pv] = pu;
            rank[pu]++;
        }
    }
}

bool areSentencesSimilarTwo(vector<string> &words1, vector<string> &words2, vector<vector<string>> &pairs)
{
    if (words1.size() != words2.size())
        return false;

    int n = words1.size();
    for (int i = 0; i < n; i++)
    {
        par[words1[i]] = words1[i];
        rank[words1[i]] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        par[words2[i]] = words2[i];
        rank[words2[i]] = 1;
    }

    for (auto pair : pairs)
    {
        if (par.count(pair[0]) == 0)
            par[pair[0]] = pair[0];
        if (par.count(pair[1]) == 0)
            par[pair[1]] = pair[1];

        merge(pair[0], pair[1]);
    }

    for (int i = 0; i < words1.size(); i++)
        if (findPar(words1[i]) != findPar(words2[i]))
            return false;

    return true;
}