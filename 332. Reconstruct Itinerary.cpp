
void dfs(string src, unordered_map<string, priority_queue<string, vector<string>, greater<string>>> &gp, vector<string> &ans)
{
    while (!gp[src].empty())
    {
        string dest = gp[src].top();
        gp[src].pop();
        dfs(dest, gp, ans);
    }
    ans.push_back(src);
}

vector<string> findItinerary(vector<vector<string>> &tickets)
{
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> gp;
    int n = tickets.size();
    for (int i = 0; i < n; i++)
        gp[tickets[i][0]].push(tickets[i][1]);

    vector<int> vis(n, false);

    vector<string> ans;
    dfs("JFK", gp, ans);

    reverse(ans.begin(), ans.end());
    return ans;
}