
// Time Complexity = O(q * (log(q) + log(MX)))
// Space Complexity = O(q * 4*MX)

class Solution {
public:
    
    int MX = 1e5;
    
    class SegmentTree
    {
        int size;
        vector<int> res;
        public:
        SegmentTree(int size)
        {
            this->size = size;
            this->res.assign(size, 0);
        }
        
        void update(int idx, int low, int high, int node, int val)
        {
            if(low == high)
            {
                res[idx] = val;
                return;
            }
            
            int mid = (low + high) >> 1;
            if(node >= low && node <= mid)
                update(2*idx+1, low, mid, node, val);
            else update(2*idx+2, mid+1, high, node, val);
            
            res[idx] = max(res[2*idx+1], res[2*idx+2]);
        }
        
        int query(int idx, int low, int high, int left, int right)
        {
            if(low >= left && high <= right)
                return res[idx];
            if(low > right || high < left)
                return 0;
            
            int mid = (low + high) >> 1;
            int leftAns = query(2*idx+1, low, mid, left, right);
            int rightAns = query(2*idx+2, mid+1, high, left, right);
            
            return max(leftAns, rightAns);
        }
    };
    
    vector<bool> getResults(vector<vector<int>>& queries) 
    {
        vector<bool> ans;
        set<int> obs;
        SegmentTree segTree(4*MX);
        
        obs.insert(0);
        obs.insert(MX);
        segTree.update(0, 0, MX, MX, MX);
        
        for(vector<int> &q : queries)
        {
            if(q[0] == 1)
            {
                int x = q[1];
                auto ubItr = obs.upper_bound(x);
                int diff1 = *ubItr - x;
                segTree.update(0, 0, MX, *ubItr, diff1);
                ubItr--;
                int diff2 = x - *ubItr;
                segTree.update(0, 0, MX, x, diff2);
                obs.insert(x);
            }
            else
            {
                int x = q[1], sz = q[2];
                int left = sz;
                int right = x;
                auto ubItr = obs.upper_bound(x);
                ubItr--;
                if(x - *ubItr >= sz)
                {
                    ans.push_back(true);
                    continue;
                }
                int maxSize = segTree.query(0, 0, MX, left, right);
                if(maxSize >= sz)
                    ans.push_back(true);
                else ans.push_back(false);
            }
        }
        
        return ans;
    }
};
