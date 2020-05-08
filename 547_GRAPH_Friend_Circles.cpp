#include <iostream>
#include <vector>
using namespace std;

//1st Method - Union Find=========================================================================

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
    if (setSize[p1] < setSize[p2])
    {
        par[p1] = p2;
        setSize[p2]++;
    }
    else
    {
        par[p2] = p1;
        setSize[p1]++;
    }
}

int findCircleNum(vector<vector<int>> &M)
{
    int n = M.size();
    for (int i = 0; i < n; i++)
    {
        par.push_back(i);
        setSize.push_back(1);
    }
    int friend_circles = n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (M[i][j] == 1)
            {
                int p1 = findPar(i);
                int p2 = findPar(j);

                if (p1 != p2)
                {
                    mergeSet(p1, p2);
                    friend_circles--;
                }
            }
        }
    }
    return friend_circles;
}

// 2nd method - DFS================================================================================================

void GCC(vector<vector<int>> &M, int i, int n, vector<bool> &vis)
{
    for (int j = 0; j < n; j++)
    {
        if (M[i][j] == 1 && !vis[j])
        {
            vis[j] = true;
            GCC(M, j, n, vis);
        }
    }
}

int findCircleNum(vector<vector<int>> &M)
{
    int n = M.size();
    vector<bool> vis(n, 0);
    int friend_circles = 0;

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            vis[i] = true;
            friend_circles++;
            GCC(M, i, n, vis);
        }
    }
    return friend_circles;
}
