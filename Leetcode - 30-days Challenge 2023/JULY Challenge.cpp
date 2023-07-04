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
