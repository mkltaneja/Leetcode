#include <iostream>
#include <vector>
using namespace std;

vector<int> par;
vector<int> setSize;
int findPar(int child)
{
    if (par[child] == child)
        return child;
    return par[child] = findPar(par[child]);
}
void mergeSet(int p1, int p2)
{
    if (setSize[p1] > setSize[p2])
    {
        par[p2] = p1;
        setSize[p1]++;
    }
    else
    {
        par[p1] = p2;
        setSize[p2]++;
    }
}

vector<int> findRedundantConnection(vector<vector<int>> &edges)
{
    int n = edges.size();
    for (int i = 0; i <= n; i++)
    {
        par.push_back(i);
        setSize.push_back(1);
    }

    for (vector<int> arr : edges)
    {
        int u = arr[0];
        int v = arr[1];
        int p1 = findPar(u);
        int p2 = findPar(v);

        if (p1 != p2)
            mergeSet(p1, p2);
        else
            return arr;
    }
    return {};
}
