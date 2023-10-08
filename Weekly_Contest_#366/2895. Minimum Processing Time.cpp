
// METHOD 1 (Comparing every element) --> Time = O(n)

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

// METHOD 2 (Comparing only necessary elements) --> Time = O(m) [OPTIMIZED]

class Solution {
public:
    int minProcessingTime(vector<int>& processorTime, vector<int>& tasks) 
    {
        int n = tasks.size();
        int m = processorTime.size();
        sort(tasks.rbegin(), tasks.rend());
        sort(processorTime.begin(), processorTime.end());
        
        int ans = 0;
        for(int i = 0, j = 0; i < m; i++, j += 4)
            ans = max(ans, processorTime[i] + tasks[j]);
        
        return ans;
    }
};
