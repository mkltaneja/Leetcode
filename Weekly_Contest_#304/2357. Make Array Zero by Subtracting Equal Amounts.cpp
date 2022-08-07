
int minimumOperations(vector<int> &nums)
{
    unordered_set<int> st;
    for (int x : nums)
        if (x)
            st.insert(x);
    return st.size();
}