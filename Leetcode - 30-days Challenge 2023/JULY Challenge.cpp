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
