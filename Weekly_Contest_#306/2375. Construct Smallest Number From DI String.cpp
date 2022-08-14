
string smallestNumber(string pattern) 
{
    int n = pattern.size();
    vector<int> ds(n);
    for(int i = n-1; i >= 0; i--)
        ds[i] = (pattern[i] == 'D') + ((i < n-1 && pattern[i+1] == 'D')? ds[i+1] : 0);

    string ans = "";
    int x = pattern[0] == 'I'? 1 : ds[0] + 1;

    ans += to_string(x);

    for(int i = 0; i < n; i++)
    {
        if(pattern[i] == 'I') 
        {
            x += ds[i] + 1;
            ans += to_string(x);
        }
        else ans += to_string(ans.back() - '0' - 1);
    }

    return ans;
}
