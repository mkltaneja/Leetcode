
vector<int> asteroidCollision(vector<int> &asteroids)
{
    stack<int> st;
    for (int x : asteroids)
    {
        if (x > 0 || st.empty() || st.top() < 0)
            st.push(x);
        else
        {
            while (!st.empty() && st.top() > 0 && -x > st.top())
                st.pop();
            if (st.empty() || st.top() < 0)
                st.push(x);
            else if (st.top() == -x)
                st.pop();
        }
    }
    vector<int> ans;
    while (!st.empty())
    {
        ans.push_back(st.top());
        st.pop();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}