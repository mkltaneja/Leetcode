
bool checkDistances(string s, vector<int>& distance) 
{
    vector<int> oc(26,-1);
    for(int i = 0; i < s.size(); i++)
    {
        if(oc[s[i]-'a'] != -1)
        {
            if(i-oc[s[i]-'a']-1 != distance[s[i]-'a'])
                return false;
        }
        oc[s[i]-'a'] = i;
    }

    return true;
}
