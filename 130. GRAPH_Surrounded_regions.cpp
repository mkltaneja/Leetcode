#include<iostream>
#include<vector>
#define vvc vector<vector<char>>

using namespace std;

void Surrounded_regions_DFS(int r, int c, int n, int m, vvc &board)
{
    if(board[r][c] != 'O')
        return;

    board[r][c] = '#';

    if(r-1 >= 0)
        Surrounded_regions_DFS(r-1,c,n,m,board);
    if(r+1 <= n-1)
        Surrounded_regions_DFS(r+1,c,n,m,board);
    if(c-1 >= 0)
        Surrounded_regions_DFS(r,c-1,n,m,board);
    if(c+1 <= m-1)
        Surrounded_regions_DFS(r,c+1,n,m,board);
}

void Surrounded_regions(vvc &board)
{
    int n = board.size();
    int m = board[0].size();

    for(int i=0;i<n;i++)
    {
        if(board[i][0] == 'O')
            Surrounded_regions_DFS(i,0,n,m,board);
        if(board[i][m-1] == 'O')
            Surrounded_regions_DFS(i,m-1,n,m,board);
    }
    for(int i=0;i<m;i++)
    {
        if(board[0][i] == 'O')
            Surrounded_regions_DFS(0,i,n,m,board);
        if(board[n-1][i] == 'O')
            Surrounded_regions_DFS(m-1,i,n,m,board);
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(board[i][j] == '#')     //Not a surrounded region
                board[i][j] = 'O';
            else if(board[i][j] == 'O')  // Surrounded region
                board[i][j] = 'X';
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    vvc board = {{'X','O','X','O'},{'O','X','O','X'},{'X','O','X','O'},{'O','X','O','X'}};
    Surrounded_regions(board);
}
