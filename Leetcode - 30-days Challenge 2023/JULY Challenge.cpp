// DAY 1 (2305. Fair Distribution of Cookies)=================================================================================

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
