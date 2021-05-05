
vector<int> partitionLabels(string S)
{
    int n = S.size();
    vector<int> locc(26, -1);
    for (int i = 0; i < n; i++)
        locc[S[i] - 'a'] = i;

    vector<int> ans;
    int i = 0;
    while (i < n)
    {
        int x = locc[S[i] - 'a'];
        int j = i;
        while (j <= x)
            x = max(x, locc[S[j++] - 'a']);
        ans.push_back(j - i);
        i = j;
    }
    return ans;
}