
// Time Complexity = O(q * log(k))
// Space Complexity = O(q + k)

class Solution {
public:
    vector<int> resultsArray(vector<vector<int>>& queries, int k)
    {
        priority_queue<int> pq;
        vector<int> ans;
        for(vector<int> &q : queries)
        {
            int d = abs(q[0]) + abs(q[1]);
            pq.push(d);
            if(pq.size() > k)
                pq.pop();
            if(pq.size() >= k)
                ans.push_back(pq.top());
            else ans.push_back(-1);
        }
        return ans;
    }
};
