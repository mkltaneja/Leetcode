
int secondsToRemoveOccurrences(string s) 
{
    int ans = 0;
    int o = 0, z = 0;
    for(char c : s)
    {
        if(c == '0')
        {
            z++;
            if(o) o--;
        }
        else if(z) ans = max(ans, o++ + z);
    }

    return ans;
}
