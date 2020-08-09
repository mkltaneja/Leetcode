
int findKthPositive(vector<int>& arr, int k)
{
    vector<int>miss;
    set<int> s;
    for (int i : arr)
        s.insert(i);
    for (int i=1;i<=10000;i++)
    {
        if (s.find(i) == s.end())
            miss.push_back(i);
    }
    // cout<<miss.size()<<endl;
    return miss[k-1];
}