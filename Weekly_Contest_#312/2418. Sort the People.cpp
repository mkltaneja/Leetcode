
vector<string> sortPeople(vector<string>& names, vector<int>& heights) 
{
    int n = heights.size();
    vector<pair<int,string>> v(n);
    for(int i = 0; i < n; i++)
        v[i] = {heights[i], names[i]};
    sort(v.rbegin(), v.rend());

    vector<string> ans;
    for(auto p : v)
        ans.push_back(p.second);

    return ans;
}
