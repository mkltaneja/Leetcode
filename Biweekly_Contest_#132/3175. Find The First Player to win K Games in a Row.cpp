
// APPROACH 1 (Using Deque)

// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k)
    {
        int n = skills.size();
        deque<pair<int,int>> dq;
        vector<int> vc(n,0);
        int mxi = -1;
        for(int i = 0; i < n; i++)
        {
            dq.push_back({skills[i], i});
            if(mxi == -1 || skills[i] > skills[mxi])
                mxi = i;
        }
        if(k >= 2*n)
            return mxi;
        while(true)
        {
            int x = dq.front().first;
            int i = dq.front().second;
            dq.pop_front();
            int y = dq.front().first;
            int j = dq.front().second;
            dq.pop_front();
            
            
            if(x > y)
            {
                if(++vc[i] == k)
                    return i;
                dq.push_front({x, i});
                dq.push_back({y, j});
            }
            else
            {
                if(++vc[j] == k)
                    return j;
                dq.push_front({y, j});
                dq.push_back({x, i});
            }
        }
        
        return -1;
    }
};


// APPROACH 2 (Finding winner through win count)

// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k)
    {
        int n = skills.size();
        int winnerIdx = 0, winCount = 0;
        for(int idx = 1; idx < n; idx++)
        {
            if(skills[winnerIdx] > skills[idx])
                winCount++;
            else winnerIdx = idx, winCount = 1;
            
            if(winCount == k)
                return winnerIdx;
        }
        return winnerIdx;
    }
};
