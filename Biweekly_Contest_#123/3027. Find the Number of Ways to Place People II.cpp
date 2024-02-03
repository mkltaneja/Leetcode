
// APPROACH 1 (Using Fenwick tree to find smaller y coordinates)

// Time = O(n*logn + n^2*log(maxYPoint))
// Space = O(n)

class Solution {
public:
    
    int offset = 1e9 + 1;
    class ftree
    {
        public:
        unordered_map<int, int> ft;
        int sz;
        ftree(int sz)
        {
            this->sz = sz;
        }
        
        int get(int x)
        {
            int ans = 0;
            while(x)
            {
                ans += ft[x];
                x -= x & -x;
            }
            return ans;
        }
        
        void add(long x)
        {
            while(x < sz)
            {
                ft[x]++;
                x += x & -x;
            }
        }
    };
    
    int numberOfPairs(vector<vector<int>>& points) 
    {
        sort(points.begin(), points.end(), [](auto const &a, auto const &b){
            return a[0] == b[0]? a[1] > b[1] : a[0] < b[0];
        });
        
        int ans = 0;
        int n = points.size();
        for(int i = 0; i < n; i++)
        {
            ftree ft(2e9+5);
            for(int j = i+1; j < n; j++)
            {
                if(points[j][1] > points[i][1]) continue;
                
                int cnt1 = ft.get(points[i][1]+offset);
                int cnt2 = ft.get(points[j][1]+offset-1);
                int cnt = cnt2 - cnt1;
                ft.add(points[j][1]+offset);
                if(!cnt) ans++;
            }
        }

        return ans;
    }
};


// APPROACH 2 (Greedy)

// Time = O(n*logn + n^2)
// Space = O(1)

class Solution {
public:
    
    int numberOfPairs(vector<vector<int>>& points) 
    {
        sort(points.begin(), points.end(), [](auto const &a, auto const &b){
            return a[0] == b[0]? a[1] > b[1] : a[0] < b[0];
        });
        
        int n = points.size();
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            int topY = -2e9;
            int y1 = points[i][1];
            for(int j = i+1; j < n; j++)
            {
                int y2 = points[j][1];
                if(y2 > y1) continue;
                if(y2 > topY)
                    topY = y2, ans++;
            }
        }

        return ans;
    }
};
