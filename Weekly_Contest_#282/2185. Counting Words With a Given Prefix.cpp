int prefixCount(vector<string>& words, string pref) 
{
    int ans = 0;
    for(string s : words)
    {
        if(s.size() < pref.size()) continue;
        if(s.substr(0,pref.size()) == pref) ans++;
    }
    return ans;
}
