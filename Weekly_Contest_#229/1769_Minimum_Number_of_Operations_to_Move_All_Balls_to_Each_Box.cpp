
// APPROACH 1 (Using Map) --> O(n^2)
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

// APPROACH 2 (by storing total jumps before and after ith position) --> O(n)
vector<int> minOperations(string boxes)
{
    int n = boxes.size();
    vector<int> ans(n, 0);
    for (int i = 0, ones = 0, jumps = 0; i < n; i++)
    {
        jumps += ones;
        ans[i] = jumps;
        ones += boxes[i] - '0';
    }
    for (int i = n - 1, ones = 0, jumps = 0; i >= 0; i--)
    {
        jumps += ones;
        ans[i] += jumps;
        ones += boxes[i] - '0';
    }
    return ans;
}