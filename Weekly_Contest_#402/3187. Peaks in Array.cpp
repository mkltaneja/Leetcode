
// Time Complexity = O(n)
// Space Complexity = O(n*logn)

class Solution {
public:
    
    vector<int> numss;
    int n, m;
    class Ftree
    {
        public:
        vector<int> ft;
        int sz;
        Ftree(int sz)
        {
            this->sz = sz;
            this->ft.assign(sz, 0);
        }

        void add(int x, int v)
        {
            while (x < sz)
            {
                ft[x] += v;
                x += x & -x;
            }
        }

        int get(int x)
        {
            int ans = 0;
            while (x)
            {
                ans += ft[x];
                x -= x & -x;
            }

            return ans;
        }
    };

    bool isPeak(int i)
    {
        if(i > 0 && i < n-1 && numss[i] > numss[i-1] && numss[i] > numss[i+1])
            return true;
        return false;
    }
    
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) 
    {
        n = nums.size(), m = queries.size();
        Ftree ft(n+1);
        vector<int> ans;
        vector<int> peaks(n, 0);
        
        numss = nums;
        for(int i = 1; i < n-1; i++)
        {
            if(isPeak(i))
            {
                ft.add(i+1, 1);
                peaks[i] = 1;
            }
        }
        
        for(vector<int> &q : queries)
        {
            int t = q[0];
            if(t == 1)
            {
                int l = q[1] + 2, r = q[2];
                int cnt = 0;
                if(l <= r)
                {
                    int cnt1 = ft.get(r);
                    int cnt2 = ft.get(l-1);
                    cnt = cnt1 - cnt2;
                }
                ans.push_back(cnt);
            }
            else
            {
                int i = q[1], v = q[2];
                numss[i] = v;
                if(peaks[i]) // already a peak
                {
                    if(!isPeak(i))
                    {
                        peaks[i] = 0;
                        ft.add(i+1, -1);
                    }
                    if(isPeak(i-1))
                    {
                        peaks[i-1] = 1;
                        ft.add(i, 1);
                    }
                    if(isPeak(i+1))
                    {
                        peaks[i+1] = 1;
                        ft.add(i+2, 1);
                    }
                }
                else // not already a peak
                {
                    if(isPeak(i)) // now a peak
                    {
                        peaks[i] = 1;
                        ft.add(i+1, 1);
                        if(i && peaks[i-1])
                        {
                            peaks[i-1] = 0;
                            ft.add(i, -1);
                        }
                        if(i+1 < n && peaks[i+1])
                        {
                            peaks[i+1] = 0;
                            ft.add(i+2, -1);
                        }
                    }
                    else // still not a peak
                    {
                        if(i && peaks[i-1])
                        {
                            if(!isPeak(i-1))
                            {
                                peaks[i-1] = 0;
                                ft.add(i, -1);
                            }
                        }
                        else if(i && !peaks[i-1])
                        {
                            if(isPeak(i-1))
                            {
                                peaks[i-1] = 1;
                                ft.add(i, 1);
                            }
                        }
                        if(i+1 < n && peaks[i+1])
                        {
                            if(!isPeak(i+1))
                            {
                                peaks[i+1] = 0;
                                ft.add(i+2, -1);
                            }
                        }
                        if(i+1 < n && !peaks[i+1])
                        {
                            if(isPeak(i+1))
                            {
                                peaks[i+1] = 1;
                                ft.add(i+2, 1);
                            }
                        }
                    }
                }
            }
            
        }
        return ans;
    }
};
