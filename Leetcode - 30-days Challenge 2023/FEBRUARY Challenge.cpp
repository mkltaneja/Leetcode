// DAY 1 (1071. Greatest Common Divisor of Strings)=============================================================================

// APPROACH 1 (Finding prime factors)

int gcd(int x, int y)
{
    while(x)
    {
        int z = y % x;
        y = x;
        x = z;
    }
    return y;
}

string gcdOfStrings(string str1, string str2) 
{
    vector<int> pFacs;
    int n = str1.size(), m = str2.size();
    int x = gcd(n, m);
    for(int i = 1; i*i <= x; i++)
    {
        if(x % i) continue;
        pFacs.push_back(i);
        if(i != x/i)
            pFacs.push_back(x/i);
    }

    sort(pFacs.rbegin(), pFacs.rend());
    for(int pf : pFacs)
    {
        bool isAns = true;
        string check = str1.substr(0,pf);
        for(int i = 0; i < n && isAns; i += pf)
        {
            if(str1.substr(i,pf) != check)
                isAns = false;
        }
        for(int i = 0; i < m && isAns; i += pf)
        {
            if(str2.substr(i,pf) != check)
                isAns = false;
        }

        if(isAns) return check;
    }

    return "";
}

// APPROACH 2 (GCD Approach)

string gcdOfStrings(string str1, string str2) 
{
    if(str1.size() < str2.size())
        return gcdOfStrings(str2, str1);
    if(str2.empty()) return str1;
    return str1.substr(0,str2.size()) == str2? gcdOfStrings(str1.substr(str2.size()), str2) : "";
}

// DAY 4 (567. Permutation in String)=================================================================================

bool checkInclusion(string s1, string s2) 
{
    int n = s1.size(), m = s2.size();
    vector<int> mp1(26,0);
    unordered_map<char,int> mp2;
    for(char &c : s1)
        mp1[c-'a']++;

    for(int i = 0; i < 26; i++)
        if(mp1[i])
            mp2[char(i+'a')] = -mp1[i];

    for(int i = 0; i < m; i++)
    {
        if(++mp2[s2[i]] == 0)
            mp2.erase(s2[i]);
        if(i >= n)
            if(--mp2[s2[i - n]] == 0)
                mp2.erase(s2[i - n]);
        if(mp2.empty()) return true;
    }

    return false;
}

// DAY 5 (438. Find All Anagrams in a String)===============================================================================

vector<int> findAnagrams(string s, string p) 
{
    int n = s.size(), m = p.size();
    unordered_map<char,int> mp;
    for(char c : p)
        mp[c]--;

    vector<int> ans;
    for(int i = 0; i < n; i++)
    {
        if(++mp[s[i]] == 0)
            mp.erase(s[i]);
        if(i >= m)
            if(--mp[s[i-m]] == 0)
                mp.erase(s[i-m]);
        if(mp.size() == 0)
            ans.push_back(i-m+1);
    }

    return ans;
}

// DAY 6 (1470. Shuffle the Array)===============================================================================

vector<int> shuffle(vector<int>& nums, int n) 
{
    vector<int> ans(2*n);
    for(int i = 0; i < n; i++)
    {
        ans[2*i] = nums[i];
        ans[2*i+1] = nums[n+i];
    }

    return ans;
}

// DAY 7 (904. Fruit Into Baskets)=================================================================================

int totalFruit(vector<int>& fruits) 
{
    int n = fruits.size();
    vector<int> typeCnt(n,0);
    int tot = 0, ans = 0;
    for(int i = 0, j = 0; i < n; i++)
    {
        if(typeCnt[fruits[i]]++ == 0)
            tot++;
        while(j < i && tot > 2)
        {
            if(--typeCnt[fruits[j++]] == 0)
                tot--;
        }
        ans = max(ans, i-j+1);
    }

    return ans;
}

// DAY 8 (45. Jump Game II)=====================================================================

// APPROACH 1 (Finding min jumps required for every position) --> time = O(n^2)

int jump(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> dp(n, 1e4+1);
    dp[n-1] = 0;
    for(int i = n-2; i >= 0; i--)
        for(int j = i+1; j < n && j <= i+nums[i]; j++)
            dp[i] = min(dp[i], dp[j]+1);

    return dp[0];
}

// APPROACH 2 (By taking maxJump position everytime) --> time = O(n)

int jump(vector<int>& nums) 
{
    int n = nums.size();
    int minJumps = 0, maxPos = 0, prevPos = 0;
    for(int i = 0; i < n-1; i++)
    {
        maxPos = max(maxPos, i + nums[i]);
        if(prevPos == i)
        {
            prevPos = maxPos;
            minJumps++;
        }
    }

    return minJumps;
}

// DAY 9 (2306. Naming a Company)=======================================================================

long long distinctNames(vector<string>& ideas) 
{
    vector<unordered_set<string>> suffix(26);
    for(string &s : ideas)
        suffix[s[0]-'a'].insert(s.substr(1));

    long long ans = 0;
    for(int i = 0; i < 26; i++)
    {
        for(int j = i+1; j < 26; j++)
        {
            long long cnt = 0;
            for(string suf : suffix[i])
                if(suffix[j].count(suf))
                    cnt++;
            ans += 2 * (suffix[i].size() - cnt) * (suffix[j].size() - cnt);
        }
    }

    return ans;
}

// DAY 10 (1162. As Far from Land as Possible)===============================================================

#define f first
#define s second
int maxDistance(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();
    queue<pair<int,int>> que;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(grid[i][j])
                que.push({i, j});

    int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

    int dist = -1;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int i = que.front().f;
            int j = que.front().s;
            que.pop();

            for(int d = 0; d < 4; d++)
            {
                int x = i + dir[d][0];
                int y = j + dir[d][1];
                if(x == -1 || y == -1 || x == n || y == m || grid[x][y] != 0)
                    continue;

                grid[x][y] = -1;
                que.push({x, y});
            }
        }

        dist++;
    }

    return dist? dist : -1;
}

// DAY 11 (1129. Shortest Path with Alternating Colors)===========================================================================

#define f first
#define s second
vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) 
{
    vector<vector<int>> redGraph(n), blueGraph(n);
    for(vector<int> &v : redEdges)
        redGraph[v[0]].push_back(v[1]);
    for(vector<int> &v : blueEdges)
        blueGraph[v[0]].push_back(v[1]);

    queue<pair<int,int>> que;
    que.push({0, -1}); // -1 = no color, 0 = red, 1 = blue

    vector<int> minDist(n, -1);
    vector<bool> redVis(n, false), blueVis(n, false);
    minDist[0] = 0;
    redVis[0] = true;
    blueVis[0] = true;

    int dist = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int par = que.front().f;
            int color = que.front().s;
            que.pop();

            if(color == 0 || color == -1)
            {
                for(int child : blueGraph[par])
                {
                    if(blueVis[child] == false)
                    {
                        if(minDist[child] == -1)
                            minDist[child] = dist + 1;
                        blueVis[child] = true;
                        que.push({child, 1});
                    }
                }
            }

            if(color == 1 || color == -1)
            {
                for(int child : redGraph[par])
                {
                    if(redVis[child] == false)
                    {
                        if(minDist[child] == -1)
                            minDist[child] = dist + 1;
                        redVis[child] = true;
                        que.push({child, 0});
                    }
                }
            }
        }
        dist++;
    }

    return minDist;
}

// DAY 12 (2477. Minimum Fuel Cost to Report to the Capital)========================================================================

#define ll long long

ll fuel = 0;
ll totSeats, totCars = 0;
vector<vector<int>> graph;

int dfs(int p, int u)
{
    ll count = 1;
    for(int v : graph[u])
        if(v != p)
            count += dfs(u, v);

    fuel += (ll)totCars;
    ll newCars = (count + totSeats - 1) / totSeats;
    totCars = newCars;

    if(totCars == 0)
        return count;
    return count;
}

long long minimumFuelCost(vector<vector<int>>& roads, int seats) 
{
    int n = roads.size()+1;
    totSeats = seats;
    graph.resize(n);
    for(vector<int> &road : roads)
    {
        graph[road[0]].push_back(road[1]);
        graph[road[1]].push_back(road[0]);
    }

    dfs(-1, 0);
    return fuel;
}

// DAY 13 (1523. Count Odd Numbers in an Interval Range)=================================================================

int countOdds(int low, int high) 
{
    int n = high - low + 1;
    return (n + (low&1)) /2;
}

// DAY 14 (67. Add Binary)=================================================================================================

string addBinary(string a, string b) 
{
    int carry = 0;
    int i = a.size()-1, j = b.size()-1;
    string ans = "";
    while(i >= 0 || j >= 0)
    {
        int x = i >= 0? (a[i--]-'0') : 0;
        int y = j >= 0? (b[j--]-'0') : 0;
        int sum = x + y + carry;
        int curr = sum & 1;
        carry = sum >> 1;
        ans += char(curr + '0');
    }
    if(carry) ans += "1";

    reverse(ans.begin(), ans.end());

    return ans;
}
