
// APPROACH 1 (Using Fenwick Tree with Numbers)

// Time Complexity = O(n * log(mx) + n)
// Space Complexity = O(mx + 2*n)

class Solution {
public:

    int OFFSET = 1e9 + 7;
    class Ftree
    {
        int n;
        unordered_map<int,int> mp;
        public:
        Ftree(int n)
        {
            this->n = n;
        }
        
        int get(int x)
        {
            int ans = 0;
            while(x <= n)
            {
                ans += mp[x];
                x += x & -x;
            }
            return ans;
        }
        void add(int x)
        {
            x--;
            while(x)
            {
                mp[x]++;
                x -= x & -x;
            }
        }
    };
    
    vector<int> resultArray(vector<int>& nums) 
    {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end()) + 5;
        Ftree ft1(mx);
        Ftree ft2(mx);
        vector<int> arr1, arr2, res;
        arr1.push_back(nums[0]);
        arr2.push_back(nums[1]);
        ft1.add(nums[0]);
        ft2.add(nums[1]);
        
        for(int i = 2; i < n; i++)
        {
            int g1 = ft1.get(nums[i]);
            int g2 = ft2.get(nums[i]);
            
            if(g1 > g2)
            {
                arr1.push_back(nums[i]);
                ft1.add(nums[i]);
            }
            else if(g1 < g2)
            {
                arr2.push_back(nums[i]);
                ft2.add(nums[i]);
            }
            else if(arr2.size() < arr1.size())
            {
                arr2.push_back(nums[i]);
                ft2.add(nums[i]);
            }
            else 
            {
                arr1.push_back(nums[i]);
                ft1.add(nums[i]);
            }
        }
        
        res.insert(res.end(), arr1.begin(), arr1.end());
        res.insert(res.end(), arr2.begin(), arr2.end());
        
        return res;
    }
};


// APPROACH 2 (Using Fenwick Tree with Indices) **[EFFECIENT WAY TO USE FENWICK TREE WHEN WE WANT TO FIND BIGGER NUMBERS IN THE STREAM/ARRAY]**

// Time Complexity = O(3*n*logn + 3*n)
// Space Complexity = O(4*n)

class Solution {
public:

    class Ftree
    {
        int n;
        vector<int> fMap;
        public:
        Ftree(int n)
        {
            this->n = n;
            this->fMap.assign(n, 0);
        }
        
        int get(int x)
        {
            int ans = 0;
            while(x < n)
            {
                ans += fMap[x];
                x += x & -x;
            }
            return ans;
        }
        void add(int x)
        {
            while(x)
            {
                fMap[x]++;
                x -= x & -x;
            }
        }
    };
    
    vector<int> resultArray(vector<int>& nums) 
    {
        int n = nums.size();
        Ftree ft1(n+1);
        Ftree ft2(n+1);
        vector<pair<int,int>> sortPos(n);
        
        for(int i = 0; i < n; i++)
            sortPos[i] = {nums[i], i+1};
        sort(sortPos.begin(), sortPos.end());
        for(int i = 0; i < n; i++)
            sortPos[i] = {sortPos[i].second, i+1};
        sort(sortPos.begin(), sortPos.end());

        vector<int> arr1, arr2, res;
        arr1.push_back(nums[0]);
        arr2.push_back(nums[1]);
        ft1.add(sortPos[0].second);
        ft2.add(sortPos[1].second);
        
        for(int i = 2; i < n; i++)
        {
            int g1 = ft1.get(sortPos[i].second);
            int g2 = ft2.get(sortPos[i].second);
            
            if(g1 > g2)
            {
                arr1.push_back(nums[i]);
                ft1.add(sortPos[i].second);
            }
            else if(g1 < g2)
            {
                arr2.push_back(nums[i]);
                ft2.add(sortPos[i].second);
            }
            else if(arr2.size() < arr1.size())
            {
                arr2.push_back(nums[i]);
                ft2.add(sortPos[i].second);
            }
            else 
            {
                arr1.push_back(nums[i]);
                ft1.add(sortPos[i].second);
            }
        }
        
        res.insert(res.end(), arr1.begin(), arr1.end());
        res.insert(res.end(), arr2.begin(), arr2.end());
        
        return res;
    }
};
