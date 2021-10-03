
int aquire_release(string &s, int k, char c)
{
    int j = 0, x = 0, ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        k -= (s[i] != c);
        while (j <= i && k == -1)
            k += (s[j++] != c);
        ans = max(ans, i - j + 1);
    }
    return ans;
}

int maxConsecutiveAnswers(string answerKey, int k)
{
    return max(aquire_release(answerKey, k, 'T'), aquire_release(answerKey, k, 'F'));
}