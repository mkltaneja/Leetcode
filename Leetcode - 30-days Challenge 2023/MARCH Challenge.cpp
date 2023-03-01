// DAY 1 (912. Sort an Array)=====================================================================================================

// APPROACH 2 (Merge Sort) --> Time = O(nlogn), Space = O(n)

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

// APPROACH 2 (Heap Sort) --> Time = O(nlogn), Space = O(1)

void maxHeapify(int i, int n, vector<int> &nums)
{
    int l = 2*i + 1, r = 2*i + 2;
    int largest = i;
    if(l < n && nums[l] > nums[largest])
        largest = l;
    if(r < n && nums[r] > nums[largest])
        largest = r;

    if(i != largest)
    {
        swap(nums[i], nums[largest]);
        maxHeapify(largest, n, nums);
    }
}

void heapSort(vector<int> &nums)
{
    int n = nums.size();
    for(int i = n/2-1; i >= 0; i--)
        maxHeapify(i, n, nums);

    for(int i = n-1; i > 0; i--)
    {
        swap(nums[0], nums[i]);
        maxHeapify(0, i, nums);
    }
}

vector<int> sortArray(vector<int>& nums) 
{
    heapSort(nums);
    return nums;
}
