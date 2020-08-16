
    bool threeConsecutiveOdds(vector<int>& arr) 
    {
        int n = arr.size();
        for(int i=0;i<n;i++)
        {
            if((arr[i] & 1) && (i+1 < n && (arr[i+1] & 1)) && (i+2 < n && (arr[i+2] & 1)))
                return true;
        }
        return false;
    }