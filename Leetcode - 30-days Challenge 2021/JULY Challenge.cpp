// DAY 1 (Gray Code)=====================================================================================

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