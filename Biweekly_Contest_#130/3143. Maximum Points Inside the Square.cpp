
// Time Complexity = O(n * log(1e9))
// Space Complexity = O(n)

class Solution {
public:
    
    int checkIfValid(int mid, vector<vector<int>> &points, string &s)
    {
        unordered_set<char> tags;
        int idx = 0, cnt = 0;
        for(vector<int> &pt : points)
        {
            if(abs(pt[0]) <= mid && abs(pt[1]) <= mid)
            {
                if(tags.count(s[idx]))
                    return -1;
                cnt++;
                tags.insert(s[idx]);
            }
            idx++;
        }
        return cnt;
    }
    
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) 
    {
        int lo = 0, hi = 1e9 + 5;
        int len = 0, maxCnt = 0;
        while(lo <= hi)
        {
            int mid = lo + ((hi - lo) >> 1);
            int cnt = checkIfValid(mid, points, s);
            if(cnt != -1)
            {
                len = mid;
                maxCnt = max(maxCnt, cnt);
                lo = mid + 1;
            }
            else hi = mid - 1;
        }
        
        return maxCnt;
    }
};
