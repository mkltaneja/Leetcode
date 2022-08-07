
int arithmeticTriplets(vector<int> &nums, int diff)
{
    unordered_set<int> st;
    for (int x : nums)
        st.insert(x);

    int ans = 0;
    for (int x : nums)
        ans += st.count(x + diff) && st.count(x + 2 * diff);

    return ans;
}