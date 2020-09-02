// DAY 1 (Largest Time For Given Digits)===================================================

string largestTimeFromDigits(vector<int>& A) 
{
    string res = "";
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
            {
                if(i == j || j == k || k == i)
                    continue;
                string hh = to_string(A[i]) + to_string(A[j]);
                string mm = to_string(A[k]) + to_string(A[6 - (i+j+k)]);
                string time = hh + ":" + mm;
                if(hh < "24" && mm < "60" && time > res)
                    res = time;
            }
        }
    }
    return res;
}

// DAY 2 ()======================================

// MEHTOD 1 
// TLE
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
{
    int n = nums.size();
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<=(i+k) && j<n; j++)
        {
            long diff = abs((long)nums[i] - (long)nums[j]);
            if(diff <= t)
                return true;
        }
    }
    return false;
}

//////////////////////////////////////////OR///////////////////////////

// METHOD 2 (Using multimap)
// AC

bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    multimap <int,int> mp;
    for(int i=0;i<nums.size();i++) mp.insert(pair< int, int >(nums[i], i));
    
    multimap <int,int>::iterator it;
    multimap <int,int>::iterator itnext;
    
    for(it=mp.begin();it!=mp.end();it++){
        itnext = it;
        while(true){
            itnext++;
            if(itnext == mp.end()) break;
            long long a = (*it).first;
            long long b = (*itnext).first;
            if(abs(a-b) <= t)  
            {
                if(abs((*it).second - (*itnext).second) <= k) 
                    return true;
            }
            else break;
        }
    }            
    return false;
}