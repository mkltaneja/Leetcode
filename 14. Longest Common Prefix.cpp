
string longestCommonPrefix(vector<string> &strs)
{
    string ans = strs[0];
    for (int i = 0; i < strs.size() - 1; i++)
    {
        string com = "";
        int j = 0, k = 0;
        while (j < strs[i].size() && k < strs[i + 1].size() && strs[i][j] == strs[i + 1][k])
            j++, k++;
        com = strs[i].substr(0, j);
        if (com.size() < ans.size())
            ans = com;
    }

    return ans;
}