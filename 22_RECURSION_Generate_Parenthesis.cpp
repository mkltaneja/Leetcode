void form_parenthesis(int n, int ob, int cb, string b, vector<string> &parenthesis)
{
    if (cb > ob)
        return;
    if (ob == n + 1 && cb == n + 1)
        parenthesis.push_back(b);
    if (ob <= n)
        form_parenthesis(n, ob + 1, cb, b + "(", parenthesis);
    if (cb <= n)
        form_parenthesis(n, ob, cb + 1, b + ")", parenthesis);
}

vector<string> generateParenthesis(int n)
{
    vector<string> parenthesis;
    form_parenthesis(n, 1, 1, "", parenthesis);
    return parenthesis;
}