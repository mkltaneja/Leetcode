
#define ll long long
vector<int> par;
int findPar(int x)
{
    return par[x] = par[x] == x? x : findPar(par[x]);
}

vector<long long> maximumSegmentSum(vector<int>& nums, vector<int>& removeQueries) 
{
    int n = nums.size();
    vector<ll> sum(n);
    for(int i = 0; i < n; i++)
        sum[i] = nums[i];
    par.assign(n,-1);

    vector<ll> ans;
    ll mx = 0;

    reverse(removeQueries.begin(), removeQueries.end());
    for(int i : removeQueries)
    {
        ans.push_back(mx);
        par[i] = i;
        if(i && par[i-1] != -1)
        {
            int pa = findPar(i-1);
            int pb = findPar(i);
            par[pa] = pb;
            sum[pb] += sum[pa];
        }
        if(i+1 < n && par[i+1] != -1)
        {
            int pa = findPar(i+1);
            int pb = findPar(i);
            par[pa] = pb;
            sum[pb] += sum[pa];
        }
        mx = max(mx, sum[findPar(i)]);
    }

    reverse(ans.begin(), ans.end());

    return ans;
}
