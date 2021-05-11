
string pushDominoes(string dominoes)
{
    int n = dominoes.size();
    for (int i = 0; i < n; i++)
    {
        if (dominoes[i] == 'R')
        {
            int j = i + 1;
            while (j < n && dominoes[j] == '.')
                dominoes[j++] = 'R';
            if (j != n && dominoes[j] == 'L')
            {
                int x = (j - i - 1) / 2, k = j - 1;
                while (x--)
                    dominoes[k--] = 'L';
                if ((j - i - 1) & 1)
                    dominoes[k] = '.';
            }
            i = j - 1;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (dominoes[i] == 'L')
        {
            if ((i - 1 >= 0 && dominoes[i - 1] == '.') &&
                (i - 2 < 0 || dominoes[i - 2] != 'R'))
            {
                int j = i - 1;
                while (j >= 0 && dominoes[j] == '.')
                    dominoes[j] = 'L';
                i = j + 1;
            }
        }
    }

    return dominoes;
}