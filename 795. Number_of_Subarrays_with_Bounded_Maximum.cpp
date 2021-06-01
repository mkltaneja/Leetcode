
int numSubarrayBoundedMax(vector<int> &A, int L, int R)
{
    int ans = 0;
    int pcount = 0;
    int pi = -1;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] >= L && A[i] <= R)
        {
            pcount = i - pi;
            ans += i - pi;
        }
        else if (A[i] < L)
            ans += pcount;
        else if (A[i] > R)
        {
            pcount = 0;
            pi = i;
        }
    }
    return ans;
}