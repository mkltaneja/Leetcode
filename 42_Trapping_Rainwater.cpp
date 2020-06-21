// Approach 1 --> By using stack
// O(n^2)
int trap(vector<int> &height)
{
    stack<int> st;
    st.push(-1);
    int wl = 0;
    for (int i = 0; i < height.size(); i++)
    {
        while (st.top() != -1 && height[i] > height[st.top()])
        {
            int h = height[st.top()];
            st.pop();
            if (st.top() == -1)
                break;
            int width = i - st.top() - 1;
            int heightt = min(height[i], height[st.top()]) - h;
            wl += width * heightt;
        }
        st.push(i);
    }
    return wl;
}

// Approach 1 --> 2 pointer approach
// O(n^2)
int trap(vector<int> &height)
{
    int n = height.size();
    if (n == 0)
        return 0;
    int li = 0, ri = n - 1;
    int lmaxh = height[0], rmaxh = height[n - 1];

    int water = 0;
    while (li < ri)
    {
        lmaxh = max(lmaxh, height[li]);
        rmaxh = max(rmaxh, height[ri]);

        if (lmaxh <= rmaxh)
            water += lmaxh - height[li++];
        else
            water += rmaxh - height[ri--];
    }
    return water;
}

// Approach 3 --> no stack (related to pointer approach) 
// O(n)
int trap(vector<int> &height)
{
    int n = height.size();
    if (n == 0)
        return 0;
    int li = 0, ri = n - 1;
    int lmaxh = height[0], rmaxh = height[n - 1];

    int water = 0;
    while (li < ri)
    {
        lmaxh = max(lmaxh, height[li]);
        rmaxh = max(rmaxh, height[ri]);

        if (lmaxh <= rmaxh)
            water += lmaxh - height[li++];
        else
            water += rmaxh - height[ri--];
    }
    return water;
}