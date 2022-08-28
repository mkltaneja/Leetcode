vector<int> kahns(int k, vector<vector<int>>& conds)
{
    vector<int> pos(k+1);
    vector<vector<int>> gp(k+1);
    vector<int> indeg(k+1,0);
    set<pair<int,int>> vis;
    for(auto v : conds)
    {
        if(vis.count({v[0], v[1]})) continue;
        if(vis.count({v[1], v[0]})) return {};
        indeg[v[1]]++;
        gp[v[0]].push_back(v[1]);
        vis.insert({v[0], v[1]});
    }

    queue<int> que;
    for(int i = 1; i <= k; i++)
        if(indeg[i] == 0)
            que.push(i);

    int tot = 0;
    while(!que.empty())
    {
        int sz = que.size();
        vector<int> curr;
        while(sz--)
        {
            int u = que.front();
            que.pop();
            pos[u] = tot++;
            for(int v : gp[u])
                if(--indeg[v] == 0)
                    que.push(v);
        }
    }


    return tot == k? pos : vector<int>();
}

vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) 
{
    vector<int> rpos = kahns(k, rowConditions);
    if(rpos.empty()) return {};
    vector<int> cpos = kahns(k, colConditions);
    if(cpos.empty()) return {};

    vector<vector<int>> ans(k, vector<int> (k, 0));

    for(int i = 1; i <= k; i++)
        ans[rpos[i]][cpos[i]] = i;

    return ans;
}
