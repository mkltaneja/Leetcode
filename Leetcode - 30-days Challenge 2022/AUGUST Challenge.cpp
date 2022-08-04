// DAY 1 (62. Unique Paths)========================================================================================

int uniquePaths(int m, int n)
{
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = 1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0 && j == 0)
                continue;
            dp[i][j] = (i ? dp[i - 1][j] : 0) + (j ? dp[i][j - 1] : 0);
        }
    }
    return dp[m - 1][n - 1];
}

// DAY 2 (378. Kth Smallest Element in a Sorted Matrix)============================================================

int kthSmallest(vector<vector<int>> &matrix, int k)
{
    int n = matrix.size(), m = matrix[0].size();
    int lo = matrix[0][0], hi = matrix[n - 1][m - 1];

    while (lo < hi)
    {
        int x = lo + ((hi - lo) >> 1);
        int tot = 0;
        for (int i = 0; i < n; i++)
        {
            int st = 0, end = m;
            while (st < end)
            {
                int mid = st + ((end - st) >> 1);
                if (matrix[i][mid] <= x)
                    st = mid + 1;
                else
                    end = mid;
            }
            tot += st;
        }
        if (tot < k)
            lo = x + 1;
        else
            hi = x;
    }

    return lo;
}

// DAY 3 (729. My Calendar I)=======================================================================================

// APPROACH 1 (By finding just lower element)

class MyCalendar
{
public:
    set<pair<int, int>> st;
    MyCalendar()
    {
    }

    auto just_lower(int x)
    {
        int lo = 0, hi = st.size() - 1, ans = -1;
        while (lo <= hi)
        {
            int mid = lo + ((hi - lo) >> 1);
            auto itr = st.begin();
            advance(itr, mid);
            if (itr->first <= x)
                lo = mid + 1, ans = mid;
            else
                hi = mid - 1;
        }

        if (ans == -1)
            return st.end();
        auto ansitr = st.begin();
        advance(ansitr, ans);
        return ansitr;
    }

    bool book(int start, int end)
    {
        if (st.empty())
        {
            st.insert({start, end});
            return true;
        }
        auto x = just_lower(start);
        if (x == st.end()) // no just_lower element found, so compare with just above ony
        {
            if (st.begin()->first < end)
                return false;
        }
        else
        {
            if (x->second > start || (++x != st.end() && x->first < end))
                return false;
        }

        st.insert({start, end});
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */