
int partitionDisjoint(vector<int>& A) 
{
    int n = A.size();
    vector<int> smin(n);
    smin[n-1] = A[n-1];
    for(int i = n-2; i >= 0; i--)
        smin[i] = min(smin[i+1], A[i]);
    
    int l = 0, mx = A[0];
    while(l+1 < n && mx > smin[l+1]) 
        mx = max(mx, A[l++]);
    
    return l+1;
}