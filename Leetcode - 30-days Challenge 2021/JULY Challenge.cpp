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