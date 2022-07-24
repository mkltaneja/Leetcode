
int shortestSequence(vector<int> &rolls, int k)
{
    int n = rolls.size();
    int ans = 0;
    for (int i = 0; i < n;)
    {
        unordered_set<int> st;
        while (i < n && st.size() < k)
            st.insert(rolls[i++]);
        if (st.size() == k)
            ans++;
    }
    return ans + 1;
}