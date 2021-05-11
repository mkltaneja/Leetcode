
string multiply(string num1, string num2)
{
    int n = num1.size(), m = num2.size();
    vector<int> prod(n + m, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            int idx1 = i + j, idx2 = i + j + 1; // Impact Indices
            int sum = (num1[i] - '0') * (num2[j] - '0') + prod[idx2];
            prod[idx2] = sum % 10;
            prod[idx1] += sum / 10;
        }
    }
    string ans = "";
    for (int i = 0; i < n + m; i++)
        if (!ans.empty() || prod[i] > 0)
            ans += prod[i] + '0';

    return ans.empty() ? "0" : ans;
}