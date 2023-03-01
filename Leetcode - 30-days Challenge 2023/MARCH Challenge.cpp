// DAY 1 (912. Sort an Array)=====================================================================================================

vector<int> merge(vector<int> &l, vector<int> &r)
{
    int n = l.size(), m = r.size();
    vector<int> merged(n+m);
    int i = 0, j = 0, k = 0;
    while(i < n || j < m)
    {
        int x = i < n? l[i] : 1e5;
        int y = j < m? r[j] : 1e5;

        merged[k++] = x < y? l[i++] : r[j++];
    }

    return merged;
}

vector<int> mergeSort(int lo, int hi, vector<int> &nums)
{
    if(lo > hi) return {};
    if(lo == hi) return {nums[lo]};

    int mid = lo + ((hi - lo) >> 1);

    vector<int> lans = mergeSort(lo, mid, nums);
    vector<int> rans = mergeSort(mid+1, hi, nums);

    return merge(lans, rans);
}

vector<int> sortArray(vector<int>& nums) 
{
    return mergeSort(0, nums.size()-1, nums);
}
