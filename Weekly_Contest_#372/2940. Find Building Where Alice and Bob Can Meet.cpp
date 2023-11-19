class Solution {
public:

    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) 
    {
        int n = heights.size();
        vector<int> nge(n, n);
        stack<int> st;
        for(int i = 0; i < n; i++)
        {
            while(!st.empty() && heights[i] > heights[st.top()])
            {
                nge[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        
        vector<int> ans;
        for(vector<int> &q : queries)
        {
            int l = min(q[0], q[1]), r = max(q[0], q[1]);
            if(l == r)
            {
                ans.push_back(l);
                continue;
            }
            if(heights[r] > heights[l])
                ans.push_back(r);
            else 
            {
                if(nge[l] == n) ans.push_back(-1);
                else if(nge[l] >= nge[r])
                    ans.push_back(nge[l]);
                else
                {
                    int i = nge[r];
                    for(; i < n; i++)
                        if(heights[i] > heights[l])
                            break;
                    if(i == n) ans.push_back(-1);
                    else ans.push_back(i);
                }
            }
        }
        
        return ans;
    }
};
