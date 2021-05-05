
vector<int> sortArrayByParity(vector<int> &A)
{
    int i = 0, j = 0;
    while (i < A.size())
    {
        if (A[i] % 2 == 0)
            swap(A[i], A[j++]);
        i++;
    }
    return A;
}