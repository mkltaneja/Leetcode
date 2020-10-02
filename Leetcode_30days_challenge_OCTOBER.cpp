// $ DAY 1 (Number of Recent Calls)==========================================================

// METHOD 1 (Using vector)

class RecentCounter {
public:
    
    vector<int> time;
    int i;
    
    RecentCounter() 
    {
        this->i = 0;
    }
    
    int ping(int t) 
    {
        time.push_back(t);
        while(time[i] < time.back() - 3000)
            i++;
        return time.size() - i;
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

////////////////////////////////////////////////////////OR//////////////////////////////////////////

// METHOD 2 (Using queue)
// Memory optimized
class RecentCounter {
public:
    
    queue<int> time;
    int qsize;
    
    RecentCounter() 
    {
        this->qsize = 0;
    }
    
    int ping(int t) 
    {
        time.push(t);
        qsize++;
        while(time.front() < t - 3000)
        {
            time.pop();
            qsize--;
        }
        return qsize;
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

// $ DAY 2 (Combination Sum)=============================================================================

// Method 1 (Normal Method)
void combisum_rec(int idx, vector<int> &arr, int tar, vector<int> coins, vector<vector<int>> &ans)
{
    if(tar == 0)
    {
        ans.push_back(coins);
        return;
    }
    for(int i = idx; i < arr.size(); i++)
    {
        if(tar - arr[i] >= 0)
        {
            coins.push_back(arr[i]);
            combisum_rec(i, arr, tar - arr[i], coins, ans);
            coins.pop_back();
        }
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
{
    vector<vector<int>> ans;
    combisum_rec(0, candidates, target, {}, ans);
    return ans;
}

// METHOD 2 (Subsequence)

void combisum_subseq(int idx, vector<int> &arr, int tar, vector<int> coins, vector<vector<int>> &ans)
{
    if(idx == arr.size())
    {
        if(tar == 0)
            ans.push_back(coins);
        return;
    }
    if(tar - arr[idx] >= 0)
    {
        coins.push_back(arr[idx]);
        combisum_subseq(idx, arr, tar - arr[idx], coins, ans);
        coins.pop_back();
    }
    
    combisum_subseq(idx+1, arr, tar, coins, ans);
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
{
    vector<vector<int>> ans;
    combisum_subseq(0, candidates, target, {}, ans);
    return ans;
}