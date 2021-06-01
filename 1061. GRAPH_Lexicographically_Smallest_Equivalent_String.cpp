#include <iostream>
#include <vector>
using namespace std;

vector<int> par(26, 0);
vector<int> setSize(26, 1);

int findPar(int child)
{
    if (par[child] == child)
        return child;
    return par[child] = findPar(par[child]);
}

void mergeSet(int p1, int p2)
{
    if (setSize[p1] < setSize[p2])
    {
        par[p1] = p2;
        setSize[p2]++;
    }
    else
    {
        par[p1] = p2;
        setSize[p2]++;
    }
}

string smallestEquivalentString(string A, string B, string S)
{
    for (int i = 0; i < 26; i++)
        par[i] = i;
    for (int i = 0; i < A.length(); i++)
    {
        int p1 = findPar(A[i] - 'a');
        int p2 = findPar(B[i] - 'a');
        par[p1] = min(p1, p2);
        par[p2] = min(p1, p2);
    }

    string ans = "";
    for (int i = 0; i < S.length(); i++)
        ans += (char)(findPar(S[i] - 'a') + 'a');

    return ans;
}

int main()
{
    string A, B, S;
    cin >> A >> B >> S;
    // cout<<smallestEquivalentString(A,B,S);
    for (int i = 0; i < 26; i++)
        par[i] = i;

    for (int i = 0; i < A.size(); i++)
    {
        int p1 = findPar(A[i] - 'a');
        int p2 = findPar(B[i] - 'a');

        // if(p1 != p2)
        {
            par[p1] = min(p1, p2);
            par[p2] = min(p1, p2);
        }
    }
    // for (int i = 0; i < 26; i++)
    //     cout << char(par[i] + 'a') << " ";

    for (int i = 0; i < S.size(); i++)
        S[i] = (findPar(S[i] - 'a') + 'a');
    cout << S;

    return 0;
}