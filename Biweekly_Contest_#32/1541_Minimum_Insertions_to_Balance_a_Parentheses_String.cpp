
int minInsertions(string s)
{
    int counto = 0, ins = 0;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '(')
            counto++;
        else
        {
            if (counto == 0)
                ins++, counto++;
            if (i + 1 < s.size() && s[i+1] == ')')
                i++;
            else
                ins++;
            counto--;
        }
    }
    return ins + 2*counto;
}