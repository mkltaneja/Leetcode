class Solution {
public:
    int minProcessingTime(vector<int>& processorTime, vector<int>& tasks) 
    {
        int n = tasks.size();
        int m = processorTime.size();
        sort(tasks.rbegin(), tasks.rend());
        sort(processorTime.begin(), processorTime.end());
        
        int ans = 0;
        for(int i = 0; i < m; i++)
        {
            for(int j = i*4; j < i*4+4; j++)
                ans = max(ans, processorTime[i] + tasks[j]);
        }
        
        return ans;
    }
};
