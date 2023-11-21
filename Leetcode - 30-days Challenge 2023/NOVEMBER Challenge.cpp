
// DAY 1 (501. Find Mode in Binary Search Tree)=======================================================================================

vector<int> ans;
int maxCnt = 0, cnt = 0, prev = INT_MIN;

void inorder(TreeNode* node)
{
    if(!node) return;

    inorder(node->left);

    if(node->val == prev) cnt++;
    else cnt = 1;
    if(cnt >= maxCnt)
    {
        if(cnt > maxCnt)
            ans.clear();
        ans.push_back(node->val);
        maxCnt = cnt;
    }
    prev = node->val;

    inorder(node->right);
}

vector<int> findMode(TreeNode* root)
{
    inorder(root);
    return ans;
}

// DAY 2 (2265. Count Nodes Equal to Average of Subtree)=================================================================================================================

int ans = 0;

pair<int,int> dfs(TreeNode* node)
{
    if(!node) return {0, 0};

    pair<int,int> lAns = dfs(node->left);
    pair<int,int> rAns = dfs(node->right);

    int sum = lAns.first + rAns.first + node->val;
    int tot = lAns.second + rAns.second + 1;
    
    ans += (sum / tot) == node->val;

    return {sum, tot};
}

int averageOfSubtree(TreeNode* root) 
{
    dfs(root);
    return ans;
}

// DAY 3 (1441. Build an Array With Stack Operations)===========================================================================

const string PUSH = "Push";
const string POP = "Pop";
vector<string> buildArray(vector<int>& target, int n) 
{
    vector<string> ans;
    for(int in = 1, i = 0, pops = 0; in <= n && i < target.size(); in++)
    {
        if(in == target[i])
        {
            while(pops--)
                ans.push_back(POP);
            ans.push_back(PUSH);
            i++;
            pops = 0;
        }
        else 
        {
            ans.push_back(PUSH);
            pops++;
        }
    }
    return ans;
}

// DAY 4 (1503. Last Moment Before All Ants Fall Out of a Plank)==========================================================================================

int getLastMoment(int n, vector<int>& left, vector<int>& right) 
{
    int ans = 0;
    for(int x : left)
        ans = max(ans, x);
    for(int x : right)
        ans = max(ans, n-x);
    return ans;
}

// DAY 5 (1535. Find the Winner of an Array Game)=========================================================================================

// APPROACH 2 (Using Deque) --> Time = O(n+k), Space = O(n)

int getWinner(vector<int>& arr, int k) 
{
    int n = arr.size();
    if(k >= n-1) 
        return *max_element(arr.begin(), arr.end());
    
    deque<int> que;
    for(int x : arr)
        que.push_back(x);
    
    int prev = -1, prevCnt = 0;
    while(true)
    {
        int top1 = que.front();
        que.pop_front();
        int top2 = que.front();
        que.pop_front();

        int topMax = max(top1, top2);
        int topMin = min(top1, top2);
        if(prev == topMax) prevCnt++;
        else
        {
            prevCnt = 1;
            prev = topMax;
        }
        
        if(prevCnt == k) return topMax;

        que.push_front(topMax);
        que.push_back(topMin);
    }

    return -1;
}

// APPROACH 2 (2 Pointer) --> Time = O(n), Space = O(1) [OPTIMIZED]

int getWinner(vector<int>& arr, int k) 
{
    int n = arr.size();
    int left = 0, right = 1;
    
    if(k == 1) return max(arr[left], arr[right]);

    int win_count = 0;
    while(right < n)
    {
        if(arr[left] > arr[right])
        {
            right++;
            if(++win_count == k) return arr[left];
        }
        else
        {
            left = right++;
            win_count = 1;
        }
    }
    return arr[left];
}

// DAY 6 (1845. Seat Reservation Manager)======================================================================================

class SeatManager {
public:

    int totSeats;
    vector<int> reserved;
    priority_queue<int, vector<int>, greater<int>> minSeat;
    SeatManager(int n) 
    {
        this->totSeats = n;
        reserved.assign(totSeats+1, 0);
        for(int seat = 1; seat <= n; seat++)
            minSeat.push(seat);
    }
    
    int reserve() 
    {
        if(minSeat.empty()) return -1; // No Seat Available

        int availSeat = minSeat.top();
        reserved[availSeat] = 1;
        minSeat.pop();

        return availSeat;
    }
    
    void unreserve(int seatNumber) 
    {
        if(!reserved[seatNumber]) return; // Seat Already Unreserved
        minSeat.push(seatNumber);
        reserved[seatNumber] = 0;
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */

// DAY 7 (1921. Eliminate Maximum Number of Monsters)================================================================================================

int eliminateMaximum(vector<int>& dist, vector<int>& speed) 
{
    int n = dist.size();
    vector<float> time(n);
    for(int i = 0; i < n; i++)
        time[i] = 1.0 * dist[i] / speed[i];
    
    sort(time.begin(), time.end());
    int currTime = 0, monstersKiller = 0;
    for(int i = 0; i < n && currTime < time[i]; i++)
    {
        currTime++;
        monstersKiller++;
    }

    return monstersKiller;
}

// DAY 8 (2849. Determine if a Cell Is Reachable at a Given Time)=========================================================================================

bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) 
{
    int diagTime = min(abs(sx - fx), abs(sy - fy));
    int linTime = abs(sx - fx) + abs(sy - fy);
    int minTime = linTime - diagTime;
    return minTime == 0? t != 1 : t >= minTime;
}

// DAY 9 (1759. Count Number of Homogenous Substrings)===================================================================================================

int MOD = 1e9 + 7;
int countHomogenous(string s) 
{
    int n = s.size();
    long i = 0;
    long ans = 0;
    while(i < n)
    {
        long j = i;
        while(j < n && s[i] == s[j]) 
            ans = (ans + (++j - i)) % MOD;
        i = j;
    }
    return ans;
}

// DAY 10 (1743. Restore the Array From Adjacent Pairs)=========================================================================================

vector<int> restoreArray(vector<vector<int>>& adjacentPairs) 
{
    unordered_map<int, vector<int>> adj;
    vector<int> ans;
    int start = INT_MIN;
    for(vector<int> &pair : adjacentPairs)
    {
        int u = pair[0];
        int v = pair[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(auto &pair : adj)
    {
        if(pair.second.size() == 1)
            start = pair.first;
        else if(pair.second.size() > 2)
            return {};
    }
    
    int curr = start, prev = -1;
    bool isLast = false;
    while(!isLast)
    {
        ans.push_back(curr);
        isLast = true;
        int currTemp = curr;
        for(int nxt : adj[curr])
        {
            if(nxt != prev)
            {
                isLast = false;
                curr = nxt;
            }
        }
        prev = currTemp;
    }
    return ans;
}

// DAY 11 (2642. Design Graph With Shortest Path Calculator)===========================================================================================

class Graph {
public:

    int n;
    vector<vector<vector<int>>> gp;
    Graph(int n, vector<vector<int>>& edges) 
    {
        this->n = n;
        this->gp.resize(n);
        for(vector<int> &e : edges)
            gp[e[0]].push_back({e[1], e[2]});
    }
    
    void addEdge(vector<int> edge) 
    {
        gp[edge[0]].push_back({edge[1], edge[2]});
    }
    
    int shortestPath(int node1, int node2) 
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        vector<int> minDist(this->n, INT_MAX);
        minDist[node1] = 0;
        pq.push({0, node1});
        while(!pq.empty())
        {
            int wsf = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if(u == node2) return wsf;

            for(auto v : gp[u])
            {
                if(wsf + v[1] < minDist[v[0]])
                {
                    pq.push({wsf + v[1], v[0]});
                    minDist[v[0]] = wsf + v[1];
                }
            }
        }

        return -1;
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */


// DAY 12 (815. Bus Routes)=======================================================================================================

int numBusesToDestination(vector<vector<int>>& routes, int source, int target) 
{
    unordered_map<int,vector<int>> gp;
    for(int i = 0; i < routes.size(); i++)
        for(int node : routes[i])
            gp[node].push_back(i);

    queue<int> que;
    unordered_set<int> nodeVis;
    vector<int> routeVis(routes.size(), 0);
    que.push(source);

    int buses = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int u = que.front();
            que.pop();

            if(u == target) return buses;

            for(int route : gp[u])
            {
                if(routeVis[route]) continue;
                routeVis[route] = 1;
                for(int node : routes[route])
                {
                    if(nodeVis.count(node)) continue;
                    if(node == target) return buses + 1;
                    nodeVis.insert(node);
                    que.push(node);
                }
            }
        }
        buses++;
    }

    return -1;
}

// DAY 13 (2785. Sort Vowels in a String)==============================================================================================

bool isVowel(char c)
{
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

string sortVowels(string s) 
{
    vector<int> freq(128, 0);
    for(char c : s)
        if(isVowel(c))
            freq[(int)c]++;
        
    int i = 0;
    for(char &c : s)
    {
        if(!isVowel(c)) continue;
        while(freq[i] == 0) i++;

        c = char(i);
        freq[i]--;
    }

    return s;
}

// DAY 14 (1930. Unique Length-3 Palindromic Subsequences)===========================================================

#define first first
#define last second
int countPalindromicSubsequence(string s) 
{
    int n = s.size();
    vector<pair<int,int>> occ(26, {-1, -1});
    vector<vector<int>> uniMap(n, vector<int>(26, 0));
    for(int i = 0; i < n; i++)
    {
        if(occ[s[i]-'a'].first == -1)
            occ[s[i]-'a'].first = i;
        occ[s[i]-'a'].last = i;
        
        if(i) uniMap[i] = uniMap[i-1];
        uniMap[i][s[i]-'a']++;
    }

    int ans = 0;
    for(int i = 0; i < 26; i++)
    {
        int start = occ[i].first, end = occ[i].last;
        if(start == end) continue;

        int totUni = 0;
        for(int j = 0; j < 26; j++)
            totUni += (uniMap[end-1][j] - uniMap[start][j]) > 0;
        ans += totUni;
    }

    return ans;
}

// DAY 15 (1846. Maximum Element After Decreasing and Rearranging)==========================================================================

int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) 
{
    int n = arr.size();
    sort(arr.begin(), arr.end());
    arr[0] = 1;
    for(int i = 1; i < n; i++)
        arr[i] = min(arr[i], arr[i-1] + 1);
    
    return arr[n-1];
}

// DAY 16 (1980. Find Unique Binary String)======================================================================================

// APPROACH 1 (Checking by converting binary to decimal) --> Time = O(2^n + n), Space = O(2*n)

string toBinary(int num)
{
    string ans = "";
    while(num)
    {
        ans += to_string(num & 1);
        num >>= 1;
    }
    reverse(ans.begin(), ans.end());

    return ans;
}

string findDifferentBinaryString(vector<string>& nums) 
{
    int n = nums.size();
    unordered_set<int> numsDeci;
    for(string bin : nums)
    {
        string temp = bin;
        int pow = 1;
        int num = 0;
        while(!temp.empty())
        {
            num += pow * (temp.back() - '0');
            temp.pop_back();
            pow *= 2;
        }
        numsDeci.insert(num);
    }
    int start = 0, end = (1 << n) - 1;
    int curr = start;
    string ans = "";
    while(curr <= end)
    {
        if(!numsDeci.count(curr))
        {
            ans = toBinary(curr);
            break;
        }
        curr++;
    }
    int m = ans.size();
    string prefix = "";
    while(prefix.size() + m < n)
        prefix += "0";
    ans = prefix + ans;

    return ans;
}

// APPROACH 2 (Considering every ith bit of every ith number, and taking its opposite in answer) --> Time = O(n), Space = O(n) [OPTIMIZED]

string findDifferentBinaryString(vector<string>& nums) 
{
    int n = nums.size();
    string ans = "";
    for(int i = 0; i < n; i++)
        ans += to_string((nums[i][i] - '0') ^ 1);
    
    return ans;
}

// DAY 17 (1877. Minimize Maximum Pair Sum in Array)==========================================================================

int minPairSum(vector<int>& nums) 
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int maxAns = INT_MIN;
    for(int i = 0, j = n-1; i < j; i++, j--)
        maxAns = max(maxAns, nums[i] + nums[j]);
    return maxAns;
}

// DAY 18 (1838. Frequency of the Most Frequent Element)===================================================================================

int maxFrequency(vector<int>& nums, int k) 
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    long last = nums[0], kUsed = 0;
    int maxFreq = 1;
    for(int i = 1, j = 0; i < n; i++)
    {
        long diff = nums[i] - nums[i-1];
        kUsed += diff * (i-j);
        while(j < i && kUsed > k)
            kUsed -= nums[i] - nums[j++];
        maxFreq = max(maxFreq, i-j+1);
    }
    return maxFreq;
}

// DAY 19 (1887. Reduction Operations to Make the Array Elements Equal)=======================================================================

// APPROACH 1 (Sorting the array) --> Time = O(n*logn + n), Space = O(1)

int reductionOperations(vector<int>& nums) 
{
    int n = nums.size();
    sort(nums.rbegin(), nums.rend());
    int i = 0, ans = 0, prevCnt = 0;
    while(i < n)
    {
        int j = i;
        while(j < n && nums[j] == nums[i]) j++;

        ans += (j < n)? (j - i + prevCnt) : 0;
        prevCnt += (j - i);

        i = j;
    }

    return ans;
}

// APPROACH 2 (Using Count Sort) --> Time = O(n + (MAX - MIN)), Space = O(MAX_NUMBER)

int reductionOperations(vector<int>& nums) 
{
    int n = nums.size();
    int mn = INT_MAX, mx = INT_MIN;
    vector<int> cnt(500005, 0);
    for(int x : nums)
    {
        cnt[x]++;
        mn = min(mn, x);
        mx = max(mx, x);
    }
    int ans = 0, prevCnt = 0;
    for(int i = mx; i > mn; i--)
    {
        if(!cnt[i]) continue;
        
        ans += cnt[i] + prevCnt;
        prevCnt += cnt[i];
    }

    return ans;
}

// DAY 20 (2391. Minimum Amount of Time to Collect Garbage)=========================================================================================

int garbageCollection(vector<string>& garbage, vector<int>& travel) 
{
    int n = garbage.size();
    unordered_map<char,int> travTime;
    int totTime = 0, travelledTime = 0;
    for(int i = 0; i < n; i++)
    {
        totTime += garbage[i].size();
        for(char garType : garbage[i])
            travTime[garType] = travelledTime;
        travelledTime += (i != n-1)? travel[i] : 0;
    }
    totTime += travTime['M'] + travTime['P'] + travTime['G'];

    return totTime;
}

// DAY 21 (1814. Count Nice Pairs in an Array)=========================================================================================

int MOD = 1e9 + 7;
long rev(int x)
{
    long res = 0;
    while(x)
    {
        res = res*10 + x%10;
        x /= 10;
    }
    return res;
}

int countNicePairs(vector<int>& nums) 
{
    unordered_map<long,long> mp;
    long ans = 0;
    for(int x : nums)
    {
        ans = (ans % MOD + (mp[x - rev(x)]++) % MOD) % MOD;
        mp[x - rev(x)] %= MOD;
    }

    return ans % MOD;
}
