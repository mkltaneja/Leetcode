
// METHOD 1 -> O(2n)

int lh(string &s)
{
    int pol = 0;
    int cnt = 0;
    string tmp = "";
    for (int i = 0; i < s.size(); i++)
    {
        tmp += to_string(pol);
        pol = (++pol) % 2;
        if (s[i] != tmp[i])
            cnt++;
        // cout<<tmp[i]<<" "<<s[i]<<endl;
    }
    return cnt;
}
int hl(string &s)
{
    int pol = 1;
    int cnt = 0;
    string tmp = "";
    for (int i = 0; i < s.size(); i++)
    {
        tmp += to_string(pol);
        pol = (++pol) % 2;
        if (s[i] != tmp[i])
            cnt++;
        // cout<<tmp[i]<<" "<<s[i]<<endl;
    }
    return cnt;
}

int minOperations(string s)
{
    return min(lh(s), hl(s));
}