
// APPROACH 1 (Using Next Greater Element) --> Time = O(n + q*n), Space = O(n + q)

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

// APPROACH 2 (Using NGE and Segment Tree) --> Time = O(logn + n + q*logn*logn), Space = O(5*n + q)  [OPTIMIZED]

class Solution {
public:

    class SegmentTree
    {
        public:
        int n;
        vector<int> nodes;
        SegmentTree(int n, vector<int> &arr)
        {
            this->n = n;
            this->nodes.resize(4*n);
            this->initialize(0, n-1, arr);
        }

        void initialize(int l, int r, vector<int> &arr, int i = 0)
        {
            if(l == r) 
            {
                nodes[i] = arr[l];
                return;
            }

            int m = l + ((r - l) >> 1);

            initialize(l, m, arr, 2*i+1);
            initialize(m+1, r, arr, 2*i+2);

            nodes[i] = max(nodes[2*i+1], nodes[2*i+2]);
        }

        int query(int x, int y, int l = 0, int r = -1, int i = 0)
        {
            if(r == -1) r += n;

            if(l > y || r < x) return -1;
            if(l >= x && r <= y) return nodes[i];

            int m = l + ((r - l) >> 1);

            return max(query(x, y, l, m, 2*i+1), query(x, y, m+1, r, 2*i+2));
        }
    };

    int findIdx(int lo, int hi, int x, SegmentTree &sTree)
    {
        while(lo < hi)
        {
            int mid = lo + ((hi - lo) >> 1);
            int max = sTree.query(lo, mid);

            if(max > x)
                hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) 
    {
        int n = heights.size();
        SegmentTree sTree(n, heights);
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
                    int idx = findIdx(r+1, n, heights[l], sTree);

                    if(idx == n) ans.push_back(-1);
                    else ans.push_back(idx);
                }
            }
        }
        
        return ans;
    }
};
