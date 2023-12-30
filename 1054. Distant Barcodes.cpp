
// Time = O(n*logn), Space = O(n)

class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) 
    {
        int size = barcodes.size();
        priority_queue<pair<int,int>> maxFreqPq;
        unordered_map<int,int> freqMap;
        for(int barcode : barcodes)
            freqMap[barcode]++;
        for(auto pair : freqMap)
            maxFreqPq.push({pair.second, pair.first});

        vector<int> ans(size);
        int index = 0;
        while(!maxFreqPq.empty())
        {
            int maxFreq = maxFreqPq.top().first;
            int maxFreqNum = maxFreqPq.top().second;
            maxFreqPq.pop();
            if(maxFreqPq.empty())
            {
                if(maxFreq > 1) return vector<int>();
                ans[index++] = maxFreqNum;
                break;
            }
            int secondMaxFreq = maxFreqPq.top().first;
            int secondMaxFreqNum = maxFreqPq.top().second;
            maxFreqPq.pop();

            ans[index++] = maxFreqNum;
            ans[index++] = secondMaxFreqNum;
            
            if(--maxFreq)
                maxFreqPq.push({maxFreq, maxFreqNum});
            if(--secondMaxFreq)
                maxFreqPq.push({secondMaxFreq, secondMaxFreqNum});
        }

        return ans;
    }
};
