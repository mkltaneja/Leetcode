
vector<int> minOperations(string boxes)
{
    int n = boxes.size();
    vector<int> ans(n, 0);
    unordered_set<int> st;
    for (int i = 0; i < n; i++)
        if (boxes[i] - '0')
            st.insert(i);
    // cout<<st.size();
    for (int i = 0; i < n; i++)
        for (int x : st)
            // cout<<x-i<<" ";
            ans[i] += abs(x - i);
    return ans;
}