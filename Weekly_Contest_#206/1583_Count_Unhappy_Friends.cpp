
int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) 
{
    vector<int> p(n,0);
    for(vector<int> v : pairs)
    {
        p[v[0]] = v[1];
        p[v[1]] = v[0];
    }
    int count = 0;
    for(int i=0; i<n; i++)
    {
        int k = 0;
        while(k < preferences[i].size() && preferences[i][k] != p[i])
        {
            int pref = preferences[i][k];
            int prefpair = p[pref];
            int j=0;
            bool f = false;
            while(j < preferences[pref].size() && preferences[pref][j] != prefpair)
            {
                if(preferences[pref][j] == i)
                {
                    count++;
                    f = true;
                    break;
                }
                j++;
            }
            if(f)
                break;
            k++;
        }
    }
    return count;
}