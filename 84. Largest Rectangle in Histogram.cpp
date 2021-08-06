
int largestRectangleArea(vector<int> &heights)
{
    int n = heights.size();
    stack<int> st;
    int maxarea = 0;
    for (int i = 0; i <= n; i++)
    {
        int x = (i == n) ? 0 : heights[i];
        while (!st.empty() && x < heights[st.top()])
        {
            int ht = heights[st.top()];
            st.pop();
            maxarea = max(maxarea, ht * (st.empty() ? i : (i - st.top() - 1)));
        }
        st.push(i);
    }
    return maxarea;
}