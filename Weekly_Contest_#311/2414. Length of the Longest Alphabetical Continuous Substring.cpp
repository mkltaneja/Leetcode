
int longestContinuousSubstring(string s) 
{
    int i = 0;
    int ans = 0;
    int n = s.size();
    while(i < n)
    {
        int j = i+1;
        while(j < n && s[j]-s[j-1] == 1) j++;
        ans = max(ans, j-i);
        i = j;
    }
    return ans;
}
