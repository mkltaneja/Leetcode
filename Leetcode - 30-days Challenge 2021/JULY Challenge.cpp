// DAY 1 (Gray Code)=====================================================================================

// METHOD 1 (Using binary string array then converted to decimal) --> >O(2^n * n)

vector<string> grayCode_(int n)
{
    if (n == 1)
        return {"0", "1"};

    vector<string> code = grayCode_(n - 1);
    vector<string> curr;

    for (int i = 0; i < code.size(); i++)
        curr.push_back('0' + code[i]);
    for (int i = code.size() - 1; i >= 0; i--)
        curr.push_back('1' + code[i]);

    return curr;
}

vector<int> grayCode(int n)
{
    vector<string> code = grayCode_(n);
    vector<int> ans;
    for (string s : code)
    {
        int x = 0;
        for (int i = 0; i < s.size(); i++)
            x = x * 2 + (s[i] - '0');
        ans.push_back(x);
    }
    return ans;
}

// METHOD 2 (Directly converted to decimal) --> O(2^n * n)

vector<int> grayCode(int n)
{
    if (n == 1)
        return {0, 1};
    vector<int> code = grayCode(n - 1);
    for (int i = code.size() - 1; i >= 0; i--)
        code.push_back(code[i] | (1 << (n - 1)));

    return code;
}

// DAY 2 (Find K Closest Elements)=====================================================================

// APPROACH 1 (Linear Search) --> O(k + klogk)

vector<int> findClosestElements(vector<int> &arr, int k, int x)
{
    auto pos = lower_bound(arr.begin(), arr.end(), x) - arr.begin();

    int i = pos - 1, j = pos;
    vector<int> ans(k);
    int idx = 0;
    while (i >= 0 && j < arr.size() && idx < k)
    {
        if ((abs(x - arr[i]) <= abs(x - arr[j])) || (abs(x - arr[i]) == abs(x - arr[j]) && arr[i] < arr[j]))
            ans[idx++] = arr[i--];
        else if (abs(x - arr[i]) > abs(x - arr[j]))
            ans[idx++] = arr[j++];
    }
    while (i >= 0 && idx < k)
        ans[idx++] = arr[i--];
    while (j < arr.size() && idx < k)
        ans[idx++] = arr[j++];

    sort(ans.begin(), ans.end());
    return ans;
}

// APPROACH 2 (Binary Search) --> O(logn)

vector<int> findClosestElements(vector<int> &arr, int k, int x)
{
    int l = 0, r = arr.size() - k;
    while (l < r)
    {
        int m = (l + r) >> 1;
        if (x - arr[m] > arr[m + k] - x)
            l = m + 1;
        else
            r = m;
    }
    vector<int> ans(arr.begin() + l, arr.begin() + l + k);
    return ans;
}

// DAY 3 (Max Sum of Rectangle No Larger than K)=============================================================================

// O(m*m*n*logn)

int maxSumSubmatrix(vector<vector<int>> &matrix, int k)
{
    int n = matrix.size(), m = matrix[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 1; j < m; j++)
            matrix[i][j] += matrix[i][j - 1];

    int ans = INT_MIN;
    for (int st = 0; st < m; st++)
    {
        for (int end = st; end < m; end++)
        {
            int psum = 0;
            set<int> psums = {0};
            for (int i = 0; i < n; i++)
            {
                int sum = matrix[i][end];
                if (st)
                    sum -= matrix[i][st - 1];

                psum += sum;
                auto itr = psums.lower_bound(psum - k);
                if (itr != psums.end())
                    ans = max(ans, psum - *itr);
                psums.insert(psum);
            }
        }
    }
    return ans;
}

// DAY 4 (Count Vowel Permutation)======================================================================

int mod = 1000000007;
int solution(int n, char c, unordered_map<char, vector<char>> &m, map<pair<char, int>, int> &dp)
{
    if (n == 0)
        return dp[{c, n}] = 1;
    if (dp.count({c, n}))
        return dp[{c, n}];

    int ans = 0;
    for (char x : m[c])
        ans = ((ans % mod) + (solution(n - 1, x, m, dp) % mod) % mod);

    return dp[{c, n}] = ans % mod;
}

int countVowelPermutation(int n)
{
    unordered_map<char, vector<char>> m;
    m['#'] = {'a', 'e', 'i', 'o', 'u'};
    m['a'] = {'e'};
    m['e'] = {'a', 'i'};
    m['i'] = {'a', 'e', 'o', 'u'};
    m['o'] = {'i', 'u'};
    m['u'] = {'a'};

    map<pair<char, int>, int> dp;
    return solution(n, '#', m, dp) % mod;
}

// DAY 5 (Reshape The Matrix)============================================================================

vector<vector<int>> matrixReshape(vector<vector<int>> &mat, int r, int c)
{
    int n = mat.size(), m = mat[0].size();
    if (n * m != r * c)
        return mat;
    vector<int> data(n * m);
    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            data[k++] = mat[i][j];

    vector<vector<int>> ans(r, vector<int>(c));
    k = 0;
    for (int i = 0; i < ans.size(); i++)
        for (int j = 0; j < ans[0].size(); j++)
            ans[i][j] = data[k++];

    return ans;
}

// DAY 6 (Reduce Array Size to Half)=====================================================================================

int minSetSize(vector<int> &arr)
{
    int n = arr.size();
    unordered_map<int, int> m;
    for (int x : arr)
        m[x]++;
    vector<int> freq;
    for (auto p : m)
        freq.push_back(p.second);
    sort(freq.begin(), freq.end(), greater<int>());

    int x = 0, i = 0;
    while (x < n / 2 && i < freq.size())
        x += freq[i++];

    return i;
}

// DAY 7 (Kth Smallest Element in a Sorted Matrix)=================================================================================

int kthSmallest(vector<vector<int>> &matrix, int k)
{
    int n = matrix.size(), m = matrix[0].size();
    vector<int> lin(n * m);
    int x = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            lin[x++] = matrix[i][j];
    sort(lin.begin(), lin.end());
    return lin[k - 1];
}

// DAY 8 (Maximum Length of Repeated Subarray)=========================================================================

// APPROACH 1 (Maximum common substring -- DP) -> O(n*m)

int findLength(vector<int> &nums1, vector<int> &nums2)
{
    int n = nums1.size(), m = nums2.size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (nums1[i] != nums2[j])
                dp[i][j] = 0;
            else
            {
                dp[i][j] = 1;
                if (i && j)
                    dp[i][j] += dp[i - 1][j - 1];
            }
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}

// DAY 9 (Longest Common Subsequence)============================================================================

// APPROACH 1 (DP) --> O(n^2)

int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();
    vector<int> maxlen(n, 1);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            if (nums[j] < nums[i] && maxlen[j] + 1 > maxlen[i])
                maxlen[i] = maxlen[j] + 1;
        ans = max(ans, maxlen[i]);
    }
    return ans;
}

// APPROACH 2 (Optimized DP -- Greedy - [By updating the lis array and running binary search in it to choose the numbers optimally]) --> O(n*logn)

int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();

    vector<int> lis;
    for (int i = 0; i < n; i++)
    {
        if (lis.empty() || lis.back() < nums[i])
        {
            lis.push_back(nums[i]);
            continue;
        }
        int si = 0, ei = lis.size() - 1, idx = -1;
        while (si <= ei)
        {
            int mid = (si + ei) >> 1;
            if (lis[mid] < nums[i])
                si = mid + 1;
            else
                idx = mid, ei = mid - 1;
        }
        lis[idx] = nums[i];
    }
    return lis.size();
}

// DAY 11 (Find Median From Data Stream)===============================================================

class MedianFinder
{
public:
    priority_queue<int> max;
    priority_queue<int, vector<int>, greater<int>> min;
    /** initialize your data structure here. */
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (max.empty() || num < max.top())
            max.push(num);
        else
            min.push(num);
        if (max.size() > min.size() + 1)
        {
            min.push(max.top());
            max.pop();
        }
        else if (min.size() > max.size() + 1)
        {
            max.push(min.top());
            min.pop();
        }
    }

    double findMedian()
    {
        double ans = (max.size() == min.size()) ? ((max.top() + min.top()) / 2.0) : ((min.size() > max.size()) ? min.top() : max.top());
        return ans;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

// DAY 12 (Isomorphic Strings)==================================================================================================

bool isIsomorphic(string s, string t)
{
    if (s.size() != t.size())
        return false;
    unordered_map<char, char> map, mapped;
    for (int i = 0; i < s.size(); i++)
    {
        if (map[s[i]] == NULL && mapped[t[i]] == NULL)
            map[s[i]] = t[i], mapped[t[i]] = s[i];
        else if (map[s[i]] && map[s[i]] != t[i] || mapped[t[i]] && mapped[t[i]] != s[i])
            return false;
    }
    return true;
}

// DAY 13 (Find Peak Element)=================================================================================================

// APPROACH 1 (Linearly) --> O(n)

int findPeakElement(vector<int> &nums)
{
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
        long l = i ? nums[i - 1] : LONG_MIN;
        long r = (i != n - 1) ? nums[i + 1] : LONG_MIN;
        if (nums[i] > l && nums[i] > r)
            return i;
    }
    return -1;
}

// APPROACH 2 (Binary Search)