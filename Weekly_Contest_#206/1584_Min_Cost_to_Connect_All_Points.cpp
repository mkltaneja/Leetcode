

#define f first
#define s second

int findpar(int child, vector<int> &par)
{
    if(par[child] == child)
        return child;
    return par[child] = findpar(par[child], par);
}
void merge_points(int i, int j, vector<int> &par)
{
    int p1 = findpar(i,par);
    int p2 = findpar(j,par);
    par[p2] = p1;
}

int minCostConnectPoints(vector<vector<int>>& points) 
{
    int n = points.size();
    vector<pair<int,pair<int,int>>> dist;
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            dist.push_back({(abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1])), {i,j}});
    sort(dist.begin(), dist.end());
    
    vector<int> par(n,0);
    for(int i=0; i<n; i++)
        par[i] = i;
    
    int mindist = 0;
    int merged = 0;
    for(auto itr : dist)
    {
        int i = itr.s.f;
        int j = itr.s.s;
        int p1 = findpar(i, par);
        int p2 = findpar(j, par);
        if(p1 != p2)
        {
            merge_points(i,j, par);
            mindist += itr.f;
            if(++merged == n)
                break;
        }
    }
    return mindist;
}