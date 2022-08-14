
int edgeScore(vector<int>& edges) 
{
    int n = edges.size();
    vector<long> sum(n);
    for(int i = 0; i < n; i++)
        sum[edges[i]] += (long)i;

    long ans = 0, mx = 0;
    for(int i = 0; i < n; i++)
    {
        if(sum[i] > mx)
        {
            mx = sum[i];
            ans = i;
        }
    }

    return ans;
}
