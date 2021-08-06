
string removeKdigits(string num, int k)
{
    stack<int> st;
    string ans = "";
    for (char c : num)
    {
        while (k && !st.empty() && c - '0' < st.top())
        {
            st.pop();
            k--;
        }
        if (c == '0' && st.empty())
            continue;
        st.push(c - '0');
    }
    while (k-- && !st.empty())
        st.pop();
    while (!st.empty())
    {
        ans += char(st.top() + '0');
        st.pop();
    }
    reverse(ans.begin(), ans.end());

    return ans.empty() ? "0" : ans;
}