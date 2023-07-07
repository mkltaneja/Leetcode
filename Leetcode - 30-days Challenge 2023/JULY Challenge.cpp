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
