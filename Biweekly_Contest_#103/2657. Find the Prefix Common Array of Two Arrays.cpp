class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) 
    {
        int cnt = 0;
        unordered_set<int> s1, s2;
        vector<int> ans;
        for(int i = 0; i < A.size(); i++)
        {
            s1.insert(A[i]);
            s2.insert(B[i]);
            if(A[i] == B[i]) cnt++;
            else
            {
                cnt += s1.count(B[i]);
                cnt += s2.count(A[i]);
            }
            ans.push_back(cnt);
        }
        
        return ans;
    }
};
