// Method 1 using map
// TLE

bool canConvertString(string s, string t, int k)
{
    int n = s.size();
    int m = t.size();
    if (n != m)
        return false;
    // cout<<n<<" "<<m<<endl;
    set<int> st;
    // cout<<endl;
    for (int i = 0;i<n;i++)
    {
        if (s[i] - t[i] != 0)
        {
            int gap = (t[i] - s[i]);
            if (gap < 0)
                gap += 26;
            // cout<<s[i]<<" "<<t[i]<<" --> "<<gap<<endl;
            if (k < gap)
                return false;
            if (st.find(gap) == st.end())
                st.insert(gap);
            else
            {
                int r = 0;
                while (26*r + gap <= k && st.find(26*r + gap) != st.end())
                {
                    r++;
                }
                if (26*r + gap <= k)
                    st.insert(26*r + gap);
                else
                    return false;
            }
        }
    }
    return true;
}

// Method 2 using character array
// TLE

bool canConvertString(string s, string t, int k)
{
    int n = s.size();
    int m = t.size();
    if (n != m)
        return false;
    // cout<<n<<" "<<m<<endl;
    set<int> st;
    vector<bool> vis(k, false);
    // cout<<endl;
    for (int i = 0;i<n;i++)
    {
        if (s[i] - t[i] != 0)
        {
            int gap = (t[i] - s[i]);
            if (gap < 0)
                gap += 26;
            // cout<<s[i]<<" "<<t[i]<<" --> "<<gap<<endl;
            if (k < gap)
                return false;
            if (!vis[gap])
                vis[gap] = true;
            else
            {
                int r = 0;
                while (26*r + gap <= k && vis[26*r + gap] == true)
                {
                    r++;
                }
                if (26*r + gap <= k)
                    vis[26*r + gap] = true;
                else
                    return false;
            }
        }
    }
    return true;
}

// Method 3 --> using gap array of characters
// AC

bool canConvertString(string s, string t, int k)
{
    int n = s.size();
    int m = t.size();
    if (n != m)
        return false;
    vector<int> gapar(26, 0);
    for (int i = 0;i<n;i++)
    {
        if (s[i] - t[i] != 0)
        {
            int gap = (t[i] - s[i]);
            if (gap < 0)
                gap += 26;
            // cout<<s[i]<<" "<<t[i]<<" --> "<<gap<<endl;
            if (gapar[gap]*26 + gap > k)
                return false;
            gapar[gap]++;
        }
    }
    return true;
}