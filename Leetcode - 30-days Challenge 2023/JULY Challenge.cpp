// DAY 1 (2305. Fair Distribution of Cookies)=================================================================================

// METHOD 1 (Memoized)

int ans = INT_MAX;
void dfs(int i, int k, vector<int> &cookies, vector<int> &child, int zeroCount)
{
	if(cookies.size() - i < zeroCount)
		return;
	if(i == cookies.size())
	{
		int maxCookies = 0;
		for(int j = 0; j < k; j++)
			maxCookies = max(maxCookies, child[j]);
		
		ans = min(ans, maxCookies);
		return;
	}
	for(int j = 0; j < k; j++)
	{
		zeroCount -= child[j] == 0;
		child[j] += cookies[i];

		dfs(i+1, k, cookies, child, zeroCount);

		child[j] -= cookies[i];
		zeroCount += child[j] == 0;
	}
}

int distributeCookies(vector<int>& cookies, int k) 
{
	vector<int> child(k, 0);
	dfs(0, k, cookies, child, k);
	return ans;
}

// DAY 2 (1601. Maximum Number of Achievable Transfer Requests)======================================================================================

int maximumRequests(int n, vector<vector<int>>& requests) 
{
	int m = requests.size();
	int ans = 0;
	for(int mask = 0; mask < (1 << m); mask++)
	{
		vector<int> in(n, 0), out(n, 0);
		int transfers = 0;
		for(int i = 0; i < m; i++)
		{
			if((mask >> i) & 1 ^ 1) continue;
			int from = requests[i][0];
			int to = requests[i][1];
			out[from]++;
			in[to]++;
			transfers++;
		}
		bool possibleTransfer = true;
		for(int i = 0; i < n; i++)
		{
			if(in[i] != out[i])
			{
				possibleTransfer = false;
				break;
			}
		}
		if(possibleTransfer) ans = max(ans, transfers);
	}

	return ans;
}

// DAY 3 (859. Buddy Strings)===================================================================================

bool buddyStrings(string s, string goal) 
{
	int n = s.size(), m = goal.size();
	if(n != m) return false;
	char a = '#', b = '#', c = '#', d = '#';
	int vis = 0;
	bool repeated = false;
	for(int i = 0; i < n; i++)
	{
		if(vis & (1 << s[i] - 'a')) repeated = true;
		vis |= (1 << (s[i] - 'a'));

		if(s[i] == goal[i]) continue;
		
		if(a == '#') a = s[i], b = goal[i];
		else if(c == '#') c = s[i], d = goal[i];
		else return false;
	}

	if(a == '#') return repeated;
	if(c == '#') return false;
	return a == d && b == c;
}

// DAY 4 (137. Single Number II)=============================================================================

int singleNumber(vector<int>& nums) 
{
	int ans = 0;
	for(int bit = 0; bit < 32; bit++)
	{
		int onBits = 0;
		for(int num : nums)
			onBits += (1 << bit) & num? 1 : 0;
		ans |= onBits % 3? (1 << bit) : 0;
	}

	return ans;
}

// DAY 5 (1493. Longest Subarray of 1's After Deleting One Element)============================================================

// APPROACH 1 (Using Array to store consecutive ones count)

int longestSubarray(vector<int>& nums) 
{
	int n = nums.size();
	vector<int> lconsec(n), rconsec(n);
	for(int i = 0; i < n; i++)
	{
		lconsec[i] = nums[i]? (i? lconsec[i-1] : 0) + 1 : 0;
		rconsec[n-i-1] = nums[n-i-1]? (i? rconsec[n-i] : 0) + 1 : 0;
	}
	int maxLen = 0;
	for(int i = 0; i < n; i++)
	{
		int leftConsec = i? lconsec[i-1] : 0;
		int rightConsec = i != n-1? rconsec[i+1] : 0;
		maxLen = max(maxLen, leftConsec + rightConsec);
	}

	return maxLen;
}

// APPROACH 2 (Space OPTIMIZED)

int longestSubarray(vector<int>& nums) 
{
	int n = nums.size();
	int l = 0, r = 0, flips = 1;
	int maxLen = 0;
	while(r < n)
	{
		if(nums[r] == 0) flips--;
		if(flips < 0)
		{
			while(nums[l++]);
			flips++;
		}
		maxLen = max(maxLen, r++ - l);
	}

	return maxLen;
}

// DAY 6 (209. Minimum Size Subarray Sum)===================================================================

int minSubArrayLen(int target, vector<int>& nums) 
{
	int n = nums.size();
	int curr = 0, prev = 0, minLen = n + 1;
	long sum = 0;
	while(curr < n)
	{
		sum += nums[curr++];
		while(sum >= target)
		{
			minLen = min(minLen, curr - prev);
			sum -= nums[prev++];
		}
	}

	return minLen == n+1? 0 : minLen;
}

// DAY 7 (2024. Maximize the Confusion of an Exam)===============================================================

int convertTo(string &answerKey, int k, char x)
{
	int curr = 0, prev = 0, maxLen = 0;
	while(curr < answerKey.size())
	{
		k -= answerKey[curr++] != x;
		while(k < 0)
			k += answerKey[prev++] != x;
		maxLen = max(maxLen, curr - prev);
	}

	return maxLen;
}

int maxConsecutiveAnswers(string answerKey, int k) 
{
	return max(convertTo(answerKey, k, 'T'), convertTo(answerKey, k, 'F'));
}

// DAY 8 (2551. Put Marbles in Bags)==================================================================================

#define ll long long
long long putMarbles(vector<int>& weights, int k) 
{
	if(k == 0) return 0;

	int n = weights.size();
	vector<ll> consecSums;
	for(int i = 0; i < n-1; i++)
		consecSums.push_back(weights[i] + weights[i+1]);
	
	sort(consecSums.begin(), consecSums.end());
	ll minSum = 0, maxSum = 0;
	for(int i = 0; i < k-1; i++)
	{
		minSum += consecSums[i];
		maxSum += consecSums[consecSums.size() - 1 - i];
	}

	return maxSum - minSum;
}

// DAY 9 (2272. Substring With Largest Variance)==============================================================

int largestVariance(string s) 
{
	int n = s.size();
	vector<int> cntMap(26,0);
	for(char c : s)
		cntMap[c-'a']++;
	
	int variance = 0;
	for(int i = 0; i < 26; i++)
	{
		if(!cntMap[i]) continue;
		char major = 'a' + i;
		for(int j = 0; j < 26; j++)
		{
			if(j == i || !cntMap[j]) continue;
			char minor = 'a' + j;

			int majorCnt = 0, minorCnt = 0, remMinorCnt = cntMap[j];
			for(char c : s)
			{
				if(c == major)
					majorCnt++;
				else if(c == minor)
				{
					minorCnt++;
					remMinorCnt--;
				}

				if(minorCnt)
					variance = max(variance, majorCnt - minorCnt);

				if(majorCnt < minorCnt && remMinorCnt)
					majorCnt = 0, minorCnt = 0;
			}
		}
	}

	return variance;
}

// DAY 10 (111. Minimum Depth of Binary Tree)=======================================================================

int minDepth(TreeNode* root) 
{
	if(!root) return 0;

	queue<TreeNode*> que;
	que.push(root);
	int lvl = 0;
	while(!que.empty())
	{
		int sz = que.size();
		while(sz--)
		{
			TreeNode* curr = que.front();
			que.pop();
			if(!curr->left && !curr->right)
				return lvl + 1;

			if(curr->left)
				que.push(curr->left);
			if(curr->right)
				que.push(curr->right);
		}
		lvl++;
	}

	return -1;
}

// DAY 11 (863. All Nodes Distance K in Binary Tree)========================================================================

vector<TreeNode*> findRootToNodePath(TreeNode* node, int target)
{
	if(!node) return {};
	if(node->val == target) return {node};

	vector<TreeNode*> lAns = findRootToNodePath(node->left, target);
	if(!lAns.empty())
	{
		lAns.push_back(node);
		return lAns;
	}

	vector<TreeNode*> rAns = findRootToNodePath(node->right, target);
	if(!rAns.empty())
	{
		rAns.push_back(node);
		return rAns;
	}

	return {};
}

void findNodesWithDistD(int k, TreeNode* node, TreeNode* prev, vector<int> &ans)
{
	if(!node || node == prev) return;
	if(k == 0)
	{
		ans.push_back(node->val);
		return;
	}
	findNodesWithDistD(k-1, node->left, prev, ans);
	findNodesWithDistD(k-1, node->right, prev, ans);
}

vector<int> distanceK(TreeNode* root, TreeNode* target, int k) 
{
	vector<TreeNode*> rootToNodePath = findRootToNodePath(root, target->val);

	vector<int> ans;
	TreeNode* prev;
	for(int i = 0; i < rootToNodePath.size() && k >= 0; i++)
	{
		findNodesWithDistD(k--, rootToNodePath[i], prev, ans);
		prev = rootToNodePath[i];
	}

	return ans;
}

// DAY 12 (802. Find Eventual Safe States)==================================================================================

int dfs(int u, vector<int> &isSafe, vector<vector<int>> &graph)
{
	if(isSafe[u] != -1) return isSafe[u];
	
	isSafe[u] = 0;

	int safe = 1;
	for(int v : graph[u])
		safe &= dfs(v, isSafe, graph);

	isSafe[u] = safe;

	return safe;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) 
{
	int n = graph.size();
	vector<int> isSafe(n, -1);
	for(int i = 0; i < n; i++)
		if(isSafe[i] == -1)
			dfs(i, isSafe, graph);
	
	vector<int> safeNodes;
	for(int i = 0; i < n; i++)
		if(isSafe[i])
			safeNodes.push_back(i);
	
	return safeNodes;
}

// DAY 13 (207. Course Schedule)====================================================================

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
{
	vector<vector<int>> gp(numCourses);
	vector<int> inDegree(numCourses);
	for(vector<int> prereq : prerequisites)
	{
		gp[prereq[0]].push_back(prereq[1]);
		inDegree[prereq[1]]++;
	}

	queue<int> que;
	vector<int> vis(numCourses,0);
	int coursesFinished = 0;
	for(int i = 0; i < numCourses; i++)
	{
		if(inDegree[i] == 0)
		{
			que.push(i);
			vis[i] = 1;
			if(++coursesFinished == numCourses) return true;
		}
	}
	
	while(!que.empty())
	{
		int u = que.front();
		que.pop();

		for(int v : gp[u])
		{
			if(!vis[v] && --inDegree[v] == 0)
			{
				vis[v] = 1;
				que.push(v);
				if(++coursesFinished == numCourses) return true;
			}
		}
	}

	return false;
}

// DAY 14 (1218. Longest Arithmetic Subsequence of Given Difference)=========================================================

#define offset (1e5 + 1)

int longestSubsequence(vector<int>& arr, int difference) 
{
	vector<int> maxSeqLen(2*offset);
	int ans = 0;
	for(int x : arr)
	{
		int curr = x + offset;
		int prev = curr - difference;

		maxSeqLen[curr] = max(maxSeqLen[curr], maxSeqLen[prev] + 1);
		ans = max(ans, maxSeqLen[curr]);
	}

	return ans;
}

// DAY 15 (1751. Maximum Number of Events That Can Be Attended II)=======================================================================

int dfs(int i, int k, vector<vector<int>> &events, vector<int> &eventStarts, vector<int> &upperBound, vector<vector<int>> &dp)
{
	if(i == events.size() || k == 0) return 0;
	if(dp[i][k] != -1) return dp[i][k];

	int ans = 0;
	for(int j = i; j < events.size(); j++)
	{
		int ub = upperBound[j];
		ans = max(ans, dfs(ub, k-1, events, eventStarts, upperBound, dp) + events[j][2]);
	}

	return dp[i][k] = ans;
}

int maxValue(vector<vector<int>>& events, int k) 
{
	int n = events.size();
	vector<int> eventStarts(n);
	vector<int> upperBound(n);
	vector<vector<int>> dp(n, vector<int>(k+1, -1));
	sort(events.begin(), events.end());
	for(int i = 0; i < n; i++)
		eventStarts[i] = events[i][0];
	for(int i = 0; i < n; i++)
		upperBound[i] = upper_bound(eventStarts.begin() + i, eventStarts.end(), events[i][1]) - eventStarts.begin();

	return dfs(0, k, events, eventStarts, upperBound, dp);
}

// DAY 17 (1125. Smallest Sufficient Team)==========================================================================

#define ll long long
ll findMinPeople(int skillMask, vector<int> &bitSkills, vector<ll> &dp)
{
	if(skillMask == 0) return 0;
	if(dp[skillMask] != -1) return dp[skillMask];

	ll minPeopleMask = LLONG_MAX;
	for(int i = 0; i < bitSkills.size(); i++)
	{
		int restMask = skillMask & ~bitSkills[i];
		if(restMask == skillMask) continue;
		ll currPeopleMask = findMinPeople(restMask, bitSkills, dp) | (1ll << i);

		if(__builtin_popcountll(currPeopleMask) < __builtin_popcountll(minPeopleMask))
			minPeopleMask = currPeopleMask;
	}

	return dp[skillMask] = minPeopleMask;
}

vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) 
{
	int n = people.size();
	unordered_map<string,int> skillMap;
	int mapVal = 0, reqSkillsMask;
	for(string &skill : req_skills)
	{
		reqSkillsMask |= (1 << mapVal);
		skillMap[skill] = mapVal++;
	}
	
	vector<int> bitSkills(n, 0);
	for(int i = 0; i < n; i++)
	{
		int mask = 0;
		for(string &skill : people[i])
			mask |= (1 << skillMap[skill]);
		bitSkills[i] = mask;
	}

	vector<ll> dp(reqSkillsMask + 1, -1);
	ll minMask = findMinPeople(reqSkillsMask, bitSkills, dp);
	
	vector<int> ans;
	for(int i = 0; i < n; i++)
		if((minMask >> i) & 1)
			ans.push_back(i);
	return ans;
}

// DAY 17 (445. Add Two Numbers II)===========================================================================

// APPROACH 1 (By Reversing the list) --> Time = O(n + m + 2*max(n, m)), Space = O(n + m + max(n, m))

ListNode* reverseList(ListNode* list)
{
	ListNode* curr = list, *prev = nullptr, *forw = list;
	while(curr)
	{
		forw = curr->next;
		curr->next = prev;
		prev = curr;
		curr = forw;
	}

	return prev;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
	ListNode* l1rev = reverseList(l1);
	ListNode* l2rev = reverseList(l2);

	ListNode* lSum = new ListNode(-1), *itr = lSum;
	int carry = 0;
	while(l1rev || l2rev)
	{
		int l1val = 0, l2val = 0;
		if(l1rev)
		{
			l1val = l1rev->val;
			l1rev = l1rev->next;
		}
		if(l2rev)
		{
			l2val = l2rev->val;
			l2rev = l2rev->next;
		}
		int sum = l1val + l2val + carry;
		itr->next = new ListNode(sum % 10);
		itr = itr->next;
		carry = sum / 10;
	}
	if(carry)
		itr->next = new ListNode(carry);

	return reverseList(lSum->next);
}

// APPROACH 2 (Without Reversing the list) --> Using Recursion --> Time = O(3*max(n, m)), Space = O(2*max(n, m))

int getListSize(ListNode* list)
{
	int n = 0;
	ListNode* itr = list;
	while(itr)
	{
		itr = itr->next;
		n++;
	}
	return n;
}

ListNode* listSum(ListNode* l1, ListNode* l2, int &carry)
{
	if(!l1) return nullptr;

	ListNode* nxtSumList = listSum(l1->next, l2->next, carry);

	int sum = l1->val + l2->val + carry;
	carry = sum / 10;
	ListNode* currSum = new ListNode(sum % 10);
	currSum->next = nxtSumList;

	return currSum;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
	int n = getListSize(l1);
	int m = getListSize(l2);

	int diff = abs(n - m);
	ListNode* prefix = new ListNode(-1), *itr = prefix;
	while(diff--)
	{
		itr->next = new ListNode(0);
		itr = itr->next;
	}

	if(n < m)
	{
		itr->next = l1;
		l1 = prefix->next;
	}
	else if(m < n)
	{
		itr->next = l2;
		l2 = prefix->next;
	}

	int carry = 0;
	ListNode* sumlist = listSum(l1, l2, carry);
	if(carry) 
	{
		ListNode* carryNode = new ListNode(carry);
		carryNode->next = sumlist;
		sumlist = carryNode;
	}

	return sumlist;
}

// APPROACH 3 (Without reversing the list) --> Using Stack  --> Time = O(n + m + max(n, m)), Space = O(n + m + max(n, m)) [SPACE AND TIME OPTIMIZED]

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
	stack<int> st1, st2;
	while(l1)
	{
		st1.push(l1->val);
		l1 = l1->next;
	}
	while(l2)
	{
		st2.push(l2->val);
		l2 = l2->next;
	}

	ListNode* sumList = nullptr;
	int carry = 0;
	while(!st1.empty() || !st2.empty())
	{
		int l1val = 0, l2val = 0;
		if(!st1.empty())
		{
			l1val = st1.top();
			st1.pop();
		}
		if(!st2.empty())
		{
			l2val = st2.top();
			st2.pop();
		}
		int sum = l1val + l2val + carry;
		carry = sum / 10;
		ListNode* currSumList = new ListNode(sum % 10);
		currSumList->next = sumList;
		sumList = currSumList;
	}
	if(carry)
	{
		ListNode* carryNode = new ListNode(carry);
		carryNode->next = sumList;
		sumList = carryNode;
	}

	return sumList;
}

// DAY 18 (146. LRU Cache)====================================================================================================

class LRUCache {
public:

    unordered_map<int,int> keyTime;
    unordered_map<int,int> keyVal;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pqTime;
    int time, capacity, size;
    LRUCache(int capacity) 
    {
        this->time = 0;
        this->size = 0;
        this->capacity = capacity;
    }
    
    int get(int key) 
    {
        if(!keyVal.count(key)) return -1;
        
        keyTime[key] = time;
        pqTime.push({time++, key});

        return keyVal[key];
    }
    
    void put(int key, int value) 
    {
        if(!keyVal.count(key))
        {
            if(++size > capacity)
            {
                while(!pqTime.empty())
                {
                    int topTime = pqTime.top().first;
                    int topKey = pqTime.top().second;
                    pqTime.pop();
                    if(topTime == keyTime[topKey])
                    {
                        keyVal.erase(topKey);
                        keyTime.erase(topKey);
                        size--;
                        break;
                    }
                }
            }
        }

        keyVal[key] = value;
        keyTime[key] = time;
        pqTime.push({time++, key});
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// DAY 19 (435. Non-overlapping Intervals)=================================================================================================

// APPROACH 1 (By finding lower_bound for every interval) --> time = O(2*n*logn), space = O(n)

int lowerBound(int end, vector<vector<int>> &intervals)
{
	int lo = 0, hi = intervals.size();
	while(lo < hi)
	{
		int mid = lo + ((hi - lo) >> 1);
		int start = intervals[mid][0];
		if(start < end)
			lo = mid + 1;
		else hi = mid;
	}

	return lo;
}

int eraseOverlapIntervals(vector<vector<int>>& intervals) 
{
	int n = intervals.size();
	vector<int> maxLenDP(n, 1);
	sort(intervals.begin(), intervals.end());

	int maxLen = 1;
	for(int i = n-1; i >= 0; i--)
	{
		int nextIntervalIndex = lowerBound(intervals[i][1], intervals);
		maxLenDP[i] = maxLen;

		if(nextIntervalIndex == n) continue;

		maxLenDP[i] = max(maxLenDP[i], maxLenDP[nextIntervalIndex] + 1);
		maxLen = max(maxLen, maxLenDP[i]);
	}

	return n - maxLen;
}

// APPROACH 2 (By updating lastEnd variable on every interval) --> time = O(n*logn + n), space = O(1) [OPTIMIZED]

int eraseOverlapIntervals(vector<vector<int>>& intervals) 
{
	int n = intervals.size();
	if(n == 0) return 0;

	sort(intervals.begin(), intervals.end());

	int lastEnd = intervals[0][1], removalCount = 0;
	for(int i = 1; i < n; i++)
	{
		int start = intervals[i][0];
		int end = intervals[i][1];
		if(start < lastEnd)
		{
			removalCount++;
			lastEnd = min(lastEnd, end);
		}
		else 
			lastEnd = end;
	}

	return removalCount;
}

// DAY 20 (735. Asteroid Collision)===============================================================================

vector<int> asteroidCollision(vector<int>& asteroids) 
{
	vector<int> currAsteroids;
	for(int asteroid : asteroids)
	{
		if(asteroid > 0) 
		{
			currAsteroids.push_back(asteroid);
			continue;
		}
		
		while(!currAsteroids.empty() && currAsteroids.back() > 0 && currAsteroids.back() < -asteroid)
			currAsteroids.pop_back();
		
		if(currAsteroids.empty() || currAsteroids.back() < 0)
			currAsteroids.push_back(asteroid);
		else if(currAsteroids.back() == -asteroid)
			currAsteroids.pop_back();
	}

	return currAsteroids;
}

// DAY 21 (673. Number of Longest Increasing Subsequence)================================================================

// APPROACH 1 (Using DP) --> Time = O(n*n), Space = O(2*n)

int findNumberOfLIS(vector<int>& nums) 
{
	int n = nums.size();
	vector<int> maxLen(n, 1), seqCount(n, 1);
	int maxCount = 0, currMax = INT_MIN;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < i; j++)
		{
			if(nums[j] < nums[i])
			{
				if(maxLen[i] < maxLen[j] + 1)
				{
					maxLen[i] = maxLen[j] + 1;
					seqCount[i] = seqCount[j];
				}
				else if(maxLen[i] == maxLen[j] + 1)
					seqCount[i] += seqCount[j];
			}
		}
		if(maxLen[i] > currMax)
		{
			currMax = maxLen[i];
			maxCount = seqCount[i];
		}
		else if(maxLen[i] == currMax)
			maxCount += seqCount[i];
	}

	return maxCount;
}

// APPROACH 2 (Using binary search and DP) --> Time = O(n*(logn)), Space = O(2*n)

int findNumberOfLIS(vector<int>& nums) 
{
	int n = nums.size();
	vector<int> dp;
	dp.push_back(INT_MIN);
	vector<vector<pair<int,int>>> LIS(n+1);
	LIS[0].push_back({INT_MIN, 1});

	int maxLen = 0;
	
	for(int x : nums)
	{
		int len = lower_bound(dp.begin(), dp.end(), x) - dp.begin();
		if(len == dp.size())
		{
			dp.push_back(x);
			maxLen++;
		}
		else dp[len] = x;

		int seqCount = 0;
		for(auto [num, cnt] : LIS[len - 1])
			seqCount += num < x? cnt : 0;
		LIS[len].push_back({x, seqCount});
	}

	int maxSeqCount = 0;
	for(auto [num, cnt] : LIS[maxLen])
		maxSeqCount += cnt;

	return maxSeqCount;
}

// DAY 22 (688. Knight Probability in Chessboard)======================================================================================

double knightProbability(int n, int k, int row, int column) 
{
	vector<vector<double>> prob(n, vector<double>(n, 0));
	prob[row][column] = 1;

	for(int i = 0; i < k; i++)
	{
		vector<vector<double>> newProb(n, vector<double>(n, 0));
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				for(int x : {1, -1, 2, -2})
				{
					for(int y : {1, -1, 2, -2})
					{
						if(abs(x) == abs(y)) continue;
						int r = i + x, c = j + y;
						if(r < 0 || c < 0 || r >= n || c >= n)
							continue;
						newProb[r][c] += prob[i][j] / 8.0;
					}
				}
			}
		}
		prob = newProb;
	}

	double totProb = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			totProb += prob[i][j];
	return totProb;
}

// DAY 23 (894. All Possible Full Binary Trees)=================================================================================

unordered_map<int, vector<TreeNode*>> dp;
vector<TreeNode*> allPossibleFBT(int n) 
{
	if(n & 1 ^ 1) return {};
	if(n == 1) return {new TreeNode(0)};
	if(dp.count(n)) return dp[n];

	vector<TreeNode*> ans;
	for(int i = 1; i < n; i += 2)
	{
		vector<TreeNode*> lTree = allPossibleFBT(i);
		vector<TreeNode*> rTree = allPossibleFBT(n - i - 1);

		for(auto l : lTree)
			for(auto r : rTree)
				ans.push_back(new TreeNode(0, l, r));
	}

	return dp[n] = ans;
}

// DAY 24 (50. Pow(x, n))====================================================================================================

double myPow(double x, int n) 
{
	long nn = n;
	double ans = 1.0;
	while(nn)
	{
		if(nn & 1)
			ans *= x;
		x *= x;
		nn /= 2;
	}

	return n > 0? ans : 1.0/ans;
}

// DAY 25 (852. Peak Index in a Mountain Array)============================================================================

int peakIndexInMountainArray(vector<int>& arr) 
{
	int n = arr.size();
	int lo = 0, hi = n - 1;
	while(lo <= hi)
	{
		int mid = lo + ((hi - lo) >> 1);

		if(mid > 0 && mid < n-1 && arr[mid] > arr[mid-1] && arr[mid] > arr[mid+1])
			return mid;
		if(mid == 0 || arr[mid] > arr[mid-1])
			lo = mid + 1;
		else if(mid == n-1 || arr[mid] > arr[mid+1])
			hi = mid - 1;
	}

	return -1;
}

// DAY 26 (1870. Minimum Speed to Arrive on Time)===================================================================

double checkTime(int speed, vector<int> &dist)
{
	double time = 0, n = dist.size();
	for(int i = 0; i < n-1; i++)
		time += ceil(1.0 * dist[i] / speed);
	time += 1.0 * dist[n-1] / speed;

	return time;
}

int minSpeedOnTime(vector<int>& dist, double hour) 
{
	int lo = 1, hi = INT_MAX;
	while(lo < hi)
	{
		int mid = lo + ((hi - lo) >> 1);
		double time = checkTime(mid, dist);
		if(time <= hour)
			hi = mid;
		else lo = mid + 1;
	}

	return hi == INT_MAX? -1 : lo;
}

// DAY 27 (2141. Maximum Running Time of N Computers)============================================================================

// APPROACH 1 (Binary Search of times) --> time = O(m * log(sum)), space = O(1)

#define ll long long

bool isPossibleTime(int n, int m, ll time, vector<int> &batteries)
{
	ll totTime = 0;
	for(int i = 0; i < m; i++)
		totTime += min((ll)batteries[i], time);
	
	return totTime / time >= n;
}

long long maxRunTime(int n, vector<int>& batteries) 
{
	int m = batteries.size();
	
	ll lo = 1, hi = 0;
	for(int x : batteries)
		hi += (ll)x;
	ll ansTime = 0;
	while(lo <= hi)
	{
		ll mid = lo + ((hi - lo) >> 1);
		if(isPossibleTime(n, m, mid, batteries))
		{
			ansTime = mid;
			lo = mid + 1;
		}
		else hi = mid - 1;
	}

	return ansTime;
}

// APPROACH 2 (Mathematically) --> time = O(n), space = O(1)

#define ll long long
long long maxRunTime(int n, vector<int>& batteries) 
{
	sort(batteries.rbegin(), batteries.rend());
	ll totTime = 0;
	for(ll battery : batteries)
		totTime += battery;
	
	for(int battery : batteries)
	{
		if(battery <= totTime / n)
			return totTime / n;
		totTime -= battery;
		n--;
	}

	return 0;
}

// DAY 28 (486. Predict the Winner)===============================================================================================

int maxDiff(int l, int r, vector<int> &nums, vector<vector<int>> &dp)
{
	if(l > r) return 0;
	if(dp[l][r] != -1) return dp[l][r];

	return dp[l][r] = max(nums[l] - maxDiff(l+1, r, nums, dp),
				nums[r] - maxDiff(l, r-1, nums, dp));
}

bool PredictTheWinner(vector<int>& nums) 
{
	int n = nums.size();
	vector<vector<int>> dp(n, vector<int> (n, -1));
	return maxDiff(0, n-1, nums, dp) >= 0;
}

// DAY 29 (808. Soup Servings)============================================================================

unordered_map<int,unordered_map<int,double>> dp;
double calculateDP(int i, int j)
{
	return (dp[max(0, i - 4)][j] + dp[max(0, i - 3)][max(0, j - 1)] + 
		dp[max(0, i - 2)][max(0, j - 2)] + dp[max(0, i - 1)][max(0, j - 3)]) / 4.0;
}

double soupServings(int n) 
{
	int m = ceil(n / 25.0);

	dp[0][0] = 0.5;
	for(int i = 1; i <= m; i++)
	{
		dp[0][i] = 1;
		dp[i][0] = 0;
		for(int j = 1; j <= i; j++)
		{
			dp[i][j] = calculateDP(i, j);
			dp[j][i] = calculateDP(j, i);
		}
		if(dp[i][i] > 1 - 1e-5)
			return 1;
	}

	return dp[m][m];
}

// DAY 30 (664. Strange Printer)=====================================================================================================

int dfs(int l, int r, string &s, vector<vector<int>> &dp)
{
	if(l == r) return 1;
	if(dp[l][r] != -1) return dp[l][r];

	int minPrints = r - l + 1;
	for(int i = l; i < r; i++)
		minPrints = min(minPrints, dfs(l, i, s, dp) + dfs(i+1, r, s, dp));
	return dp[l][r] = minPrints - (s[l] == s[r]);
}

int strangePrinter(string s) 
{
	int n = s.size();
	vector<vector<int>> dp(n, vector<int> (n, -1));
	return dfs(0, n-1, s, dp);
}

// DAY 31 (712. Minimum ASCII Delete Sum for Two Strings)===========================================================================

vector<int> remSum1, remSum2;
int dfs(int i, int j, int n, int m, string &s1, string &s2, vector<vector<int>> &dp)
{
	if(i == n && j == m)
		return 0;
	if(i == n || j == m)
		return remSum1[i] + remSum2[j];
	
	if(dp[i][j] != -1) return dp[i][j];

	return dp[i][j] = s1[i] == s2[j]? dfs(i+1, j+1, n, m, s1, s2, dp) : 
		min(dfs(i+1, j, n, m, s1, s2, dp) + s1[i], dfs(i, j+1, n, m, s1, s2, dp) + s2[j]);
}

int minimumDeleteSum(string s1, string s2)
{
	int n = s1.size(), m = s2.size();

	remSum1.resize(n+1);
	remSum2.resize(m+1);
	remSum1[n-1] = s1[n-1];
	remSum2[m-1] = s2[m-1];
	for(int i = n-2; i >= 0; i--)
		remSum1[i] += s1[i] + remSum1[i+1];
	for(int i = m-2; i >= 0; i--)
		remSum2[i] += s2[i] + remSum2[i+1];
	
	vector<vector<int>> dp(n, vector<int> (m, -1));
	return dfs(0, 0, n, m, s1, s2, dp);
}

// METHOD 2 (Tabulated)

int minimumDeleteSum(string s1, string s2) 
{
	int n = s1.size(), m = s2.size();
	vector<vector<int>> dp(n+1, vector<int> (m+1, 0));

	dp[n][m] = 0;
	for(int i = n-1; i >= 0; i--)
		dp[i][m] = s1[i] + dp[i+1][m];
	for(int i = m-1; i >= 0; i--)
		dp[n][i] = s2[i] + dp[n][i+1];

	for(int i = n-1; i >= 0; i--)
		for(int j = m-1; j >= 0; j--)
			dp[i][j] = s1[i] == s2[j]? dp[i+1][j+1] : 
				min(dp[i+1][j] + s1[i], dp[i][j+1] + s2[j]);
	return dp[0][0];
}
