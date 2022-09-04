
int garbageCollection(vector<string>& garbage, vector<int>& travel) 
{
    unordered_map<char,int> maxt;
    int ans = 0, time = 0;
    for(int i = 0; i < garbage.size(); i++)
    {
        for(char c : garbage[i])
            maxt[c] = time;
        time += i == garbage.size()-1? 0 : travel[i];
        ans += garbage[i].size();
    }

    for(auto p : maxt)
        ans += p.second;

    return ans;
}
