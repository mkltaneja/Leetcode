
bool isSumEqual(string firstWord, string secondWord, string targetWord)
{
    int a = 0, b = 0, x = 0;
    for (char c : firstWord)
        a = a * 10 + (c - 'a');
    for (char c : secondWord)
        b = b * 10 + (c - 'a');
    for (char c : targetWord)
        x = x * 10 + (c - 'a');
    // cout<<a<<", "<<b<<", "<<x<<endl;
    return a + b == x;
}