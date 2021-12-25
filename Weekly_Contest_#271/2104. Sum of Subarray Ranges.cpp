
// APPROACH 1 (Brute Force) --> O(n^2)

long long subArrayRanges(vector<int> &nums)
{
    int n = nums.size();
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        int mx = nums[i], mn = nums[i];
        for (int j = i + 1; j < n; j++)
        {
            mx = max(mx, nums[j]);
            mn = min(mn, nums[j]);

            ans += (mx - mn);
        }
    }

    return ans;
}

// APPROACH 2 (By Finding next greater on left, right and next smaller on left and right) --> O(n)

class Pair
{
public:
    int cgl, csl, cgr, csr;
    Pair()
    {
        this->cgl = 0;
        this->csl = 0;
        this->cgr = 0;
        this->csr = 0;
    }
};

void fill_cgl_cgr(int n, vector<int> &arr, vector<Pair> &conf)
{
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[i] >= arr[st.top()])
        {
            conf[st.top()].cgr = i - st.top();
            st.pop();
        }
        if (!st.empty())
            conf[i].cgl = i - st.top();
        st.push(i);
    }
}

void fill_csl_csr(int n, vector<int> &arr, vector<Pair> &conf)
{
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[i] <= arr[st.top()])
        {
            conf[st.top()].csr = i - st.top();
            st.pop();
        }
        if (!st.empty())
            conf[i].csl = i - st.top();
        st.push(i);
    }
}

long long subArrayRanges(vector<int> &nums)
{
    int n = nums.size();
    long long ans = 0;

    vector<Pair> conf(n);

    for (int i = 0; i < n; i++)
    {
        conf[i].cgl = i + 1;
        conf[i].csl = i + 1;
        conf[i].cgr = n - i;
        conf[i].csr = n - i;
    }

    fill_cgl_cgr(n, nums, conf);
    fill_csl_csr(n, nums, conf);

    for (int i = 0; i < n; i++)
        ans += nums[i] * (((long long)conf[i].cgl * conf[i].cgr) - ((long long)conf[i].csl * conf[i].csr));

    return ans;
}