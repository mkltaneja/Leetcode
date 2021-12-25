#include <bits/stdc++.h>
using namespace std;

// // vector<vector<int>> peaks(vector<int> &arr, int k)
// // {
// //     int n = arr.size();
// //     vector<int> l(n), r(n);
// //     for (int i = 1; i < n; i++)
// //         l[i] = (arr[i] > arr[i - 1]) ? l[i - 1] + 1 : 0;
// //     for (int i = n - 2; i >= 0; i--)
// //         r[i] = (arr[i] > arr[i + 1]) ? r[i + 1] + 1 : 0;

// //     // for (int i = 0; i < n; i++)
// //     //     cout << l[i] << ", " << r[i] << endl;

// //     vector<vector<int>> ans;
// //     vector<pair<int, int>> pks;
// //     for (int i = 1; i < n - 1; i++)
// //         if (l[i] && r[i])
// //             pks.push_back({l[i] + r[i] - 1, i});

// //     sort(pks.rbegin(), pks.rend());

// //     vector<int> pks2;
// //     for (int i = 0; i < pks.size() && i < k; i++)
// //     {
// //         int idx = pks[i].second;
// //         pks2.push_back(idx);
// //     }

// //     sort(pks2.begin(), pks2.end());
// //     for (int x : pks2)
// //     {
// //         vector<int> curr;
// //         for (int j = x - l[x]; j < x; j++)
// //             curr.push_back(arr[j]);
// //         for (int j = x; j <= x + r[x]; j++)
// //             curr.push_back(arr[j]);

// //         ans.push_back(curr);
// //     }

// //     return ans;
// // }

// // int main()
// // {
// //     int n, k;
// //     cin >> n >> k;
// //     vector<int> arr(n);
// //     for (int i = 0; i < n; i++)
// //         cin >> arr[i];

// //     vector<vector<int>> ans = peaks(arr, k);

// //     for (int i = 0; i < ans.size(); i++)
// //     {
// //         for (int j = 0; j < ans[i].size(); j++)
// //             cout << ans[i][j] << ", ";
// //         cout << endl;
// //     }
// // }


// #define f first
// #define s second

// pair<int,string> dfs(int i, int j, string prev, int n, int m, vector<vector<string>> &arr)
// {
//     if (i == n || j == m || i == -1 || j == -1 || arr[i][j] <= prev)
//         return {0, ""};
    
//     auto d = dfs(i + 1, j, arr[i][j], n, m, arr);
//     auto r = dfs(i, j + 1, arr[i][j], n, m, arr);
//     auto u = dfs(i - 1, j, arr[i][j], n, m, arr);
//     auto l = dfs(i, j - 1, arr[i][j], n, m, arr);

//     int maxi = max({d.f, r.f, u.f, l.f});
//     if(maxi == d.f)
//         return {maxi+1, arr[i][j] + d.s};
//     if(maxi == r.f)
//         return {maxi+1, arr[i][j] + r.s};
//     if(maxi == u.f)
//         return {maxi+1, arr[i][j] + u.s};
//     if(maxi == l.f)
//         return {maxi+1, arr[i][j] + l.s};
// }

// vector<string> longestIncreasingPath(vector<vector<string>> &arr)
// {
//     int maxlen = 0;
//     int n = arr.size();
//     int m = arr[0].size();
//     vector<vector<int>> dp(n, vector<int>(m, -1));
//     string ans = "";
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < m; j++)
//         {
//             auto curr = dfs(i, j, " ", n, m, arr);
//             if(curr.f > maxlen)
//             {
//                 maxlen = curr.f;
//                 ans = curr.s;
//             }
//         }
//     }
//     vector<string> res;
//     for(int i = 0; i < ans.size(); i++)
//         res.push_back(string(1, ans[i]));
//     return res;
// }

int main()
{
    int n, m;
    cin>>n>>m;
    vector<vector<string>> arr(n, vector<string>(m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin>>arr[i][j];
    
    vector<string> ans = longestIncreasingPath(arr);
    for(string ss : ans)
        cout<<ss<<", ";
}