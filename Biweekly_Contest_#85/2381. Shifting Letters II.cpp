
string shiftingLetters(string s, vector<vector<int>>& shifts) 
{
    int n = s.size();
    vector<int> net(n+1,0);

    for(vector<int> v : shifts)
    {
        if(v[2])
        {
            net[v[1]+1]--;
            net[v[0]]++;
        }
        else 
        {
            net[v[1]+1]++;
            net[v[0]]--;
        }
    }

    int p = 0;
    for(int i = 0; i < n; i++)
    {
        net[i] += p;
        p = net[i];
        net[i] = (net[i] % 26 + 26) % 26;

        if(net[i] <= 'z' - s[i]) 
            s[i] += net[i];
        else 
            s[i] = 'a' + (net[i] - ('z' - s[i]) - 1);
    }

    return s;
}
