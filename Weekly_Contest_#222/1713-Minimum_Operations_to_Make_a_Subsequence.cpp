
int minOperations(vector<int> &target, vector<int> &arr)
{
    map<int, int> m;
    for (int i = 0; i < target.size(); i++)
        m[target[i]] = i;

    vector<int> tarr;
    for (int x : arr)
        if (m.count(x))
            tarr.push_back(m[x]);

    vector<int> lis;
    for (int x : tarr)
    {
        vector<int>::iterator itr = lower_bound(lis.begin(), lis.end(), x);
        if (itr == lis.end())
            lis.push_back(x);
        else
            *itr = x;
    }
    return (target.size() - lis.size());
}